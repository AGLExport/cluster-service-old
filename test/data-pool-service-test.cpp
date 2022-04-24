/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service-test.c
 * @brief	Unit test fot data-pool-service-test.c
 */
#include <gtest/gtest.h>
#include "mock/libsystemd_mock.hpp"
#include "mock/syscall_io_mock.hpp"

// Test Terget files ---------------------------------------
extern "C" {
#define UNIT_TEST
#include "../src/data-pool-service.c"


}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_service_test : Test, LibsystemdMockBase, SyscallIOMockBase {};


//--------------------------------------------------------------------------------------------------------
//  data_pool_service_cleanup test
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_service_cleanup__argument_error)
{
	int ret = -1;

	// Argument error (this function is implimanted NULL through, it success.
	ret = data_pool_service_cleanup(NULL);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
//  data_pool_incoming_handler test
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__argument_error)
{
	int ret = -1;
	
	// This function is callback from event loop. Argument error is only a userdata = NULL
	
	// No revents
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, 0, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLHUP
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLHUP, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLERR
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLERR, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLHUP | EPOLLERR
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, (EPOLLHUP | EPOLLERR), NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLIN
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(sysiom, close(101))
				.WillOnce(Return(0));

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLHUP | EPOLLERR | EPOLLIN
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, (EPOLLHUP | EPOLLERR | EPOLLIN), NULL);
	ASSERT_EQ(-1, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__server_socket_error)
{
	int ret = -1;
	
	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	// No revents
	dp->socket_evsource = (sd_event_source *)(0xa8a8);
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, 0, dp);
	ASSERT_EQ(-1, ret);

	// EPOLLHUP
	dp->socket_evsource = (sd_event_source *)(0xa8a8);
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0xa8a8)))
				.Times(1).WillRepeatedly(Return(nullptr));
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLHUP, dp);
	ASSERT_EQ(-1, ret);

	// EPOLLERR
	dp->socket_evsource = (sd_event_source *)(0xa8a8);
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0xa8a8)))
				.Times(1).WillRepeatedly(Return(nullptr));
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLERR, dp);
	ASSERT_EQ(-1, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__server_socket_incoming_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;

	//dummy data alloc
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	// accept INTR and error
	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(SetErrnoAndReturn(EINTR, -1))
				.WillOnce(SetErrnoAndReturn(EBADF, -1));
	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(-1, ret);


	// sd_event_add_io error
	dp->parent_eventloop = (sd_event*)(0xa5a5);

	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xa5a5), _, 101, (EPOLLIN | EPOLLHUP | EPOLLERR), data_pool_sessions_handler, dp))
				.WillOnce(Return(-1));
	EXPECT_CALL(sysiom, close(101))
				.WillOnce(Return(0));

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(-1, ret);


	// sd_event_source_set_io_fd_own error
	dp->parent_eventloop = (sd_event *)(0xa5a5);

	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xa5a5), _, 101, (EPOLLIN | EPOLLHUP | EPOLLERR), data_pool_sessions_handler, dp))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own( _, 1))
				.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(1).WillRepeatedly(Return(nullptr));
	EXPECT_CALL(sysiom, close(101))
				.WillOnce(Return(0));

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(-1, ret);
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__server_socket_incoming_1st_session_in)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	struct s_data_pool_session *dps = NULL;
	// 1st session in
	//create dummy top session
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	dp->parent_eventloop = (sd_event *)(0xa5a5);

	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xa5a5), _, 101, (EPOLLIN | EPOLLHUP | EPOLLERR), data_pool_sessions_handler, dp))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own( _, 1))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(0, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2+1)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__server_socket_incoming_2nd_session_in)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	struct s_data_pool_session *dps = NULL;

	// 2nd session in
	//create dummy top session
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0x8888);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;
	dp->parent_eventloop = (sd_event *)(0xa5a5);

	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xa5a5), _, 101, (EPOLLIN | EPOLLHUP | EPOLLERR), data_pool_sessions_handler, dp))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own( _, 1))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(0, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2+2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_incoming_handler__server_socket_incoming_loop_out_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	struct s_data_pool_session *dps = NULL;

	// loop out error
	//create dummy top session
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0x8888);	//set dummy value
	dps->next = dps;
	dp->session_list = dps;
	dp->parent_eventloop = (sd_event *)(0xa5a5);

	EXPECT_CALL(sysiom, accept4(100, nullptr, nullptr, (SOCK_NONBLOCK | SOCK_CLOEXEC)))
				.WillOnce(Return(101));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xa5a5), _, 101, (EPOLLIN | EPOLLHUP | EPOLLERR), data_pool_sessions_handler, dp))
				.WillOnce(Invoke([](sd_event *event, sd_event_source **source, int fd,
						uint32_t events, sd_event_io_handler_t handler, void *userdata) {
						(*source) = (sd_event_source *)0x7777;
						return 0;
					}));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own( _, 1))
				.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x7777)))
				.WillOnce(Return(nullptr));

	ret = data_pool_incoming_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(-1, ret);

	// Repair loop list
	dps->next = NULL;

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2+1)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
//  data_pool_sessions_handler test
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__argument_error)
{
	int ret = -1;
	
	// This function is callback from event loop. Argument error is only a userdata = NULL
	
	// No revents
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, 0, NULL);
	ASSERT_EQ(-1, ret);
	
	// EPOLLHUP
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLHUP, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLERR
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLERR, NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLHUP | EPOLLERR
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, (EPOLLHUP | EPOLLERR), NULL);
	ASSERT_EQ(-1, ret);

	// EPOLLIN
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(0);
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, NULL);
	ASSERT_EQ(-1, ret);
	
	// EPOLLHUP | EPOLLERR | EPOLLIN
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, (EPOLLHUP | EPOLLERR | EPOLLIN), NULL);
	ASSERT_EQ(-1, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__no_session)
{
	int ret = -1;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1, sizeof(struct s_data_pool_service));

	// No revents
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(0);
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, 0, dp);
	ASSERT_EQ(-1, ret);
	
	// EPOLLHUP
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLHUP, dp);
	ASSERT_EQ(-1, ret);

	// EPOLLERR
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(1)
				.WillRepeatedly(Return(nullptr));
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLERR, dp);
	ASSERT_EQ(-1, ret);

	// EPOLLIN
	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0x8a8a)))
				.Times(0);
	ret = data_pool_sessions_handler((sd_event_source *)(0x8a8a), 100, EPOLLIN, dp);
	ASSERT_EQ(-1, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__session_list_4_1)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1, sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (long i = 1; i < num_of_sessions; i++) {
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(i);	//set dummy value
		dps->next = NULL;
	}
	
	for (long i = 0; i < num_of_sessions; i++) {
		EXPECT_CALL(lsm, sd_event_source_disable_unref(((sd_event_source *)i)))
					.Times(1)
					.WillOnce(Return(nullptr));
		ret = data_pool_sessions_handler(((sd_event_source *)i), 100, (EPOLLHUP | EPOLLERR), dp);
		ASSERT_EQ(0, ret);
	}
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__session_list_4_2)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (long i = 1; i < num_of_sessions; i++) {
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(i);	//set dummy value
		dps->next = NULL;
	}
	
	for (long i = num_of_sessions-1; i >= 0; i--) {
		EXPECT_CALL(lsm, sd_event_source_disable_unref(((sd_event_source *)i)))
					.Times(1)
					.WillOnce(Return(nullptr));
		ret = data_pool_sessions_handler(((sd_event_source *)i), 100, (EPOLLHUP | EPOLLERR), dp);
		ASSERT_EQ(0, ret);
	}
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__session_list_4_3)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (long i = 1; i < num_of_sessions; i++) {
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(i);	//set dummy value
		dps->next = NULL;
	}
	
	long table[] = {1,2,0,3};
	for (long i = 0; i < num_of_sessions; i++) {
		EXPECT_CALL(lsm, sd_event_source_disable_unref(((sd_event_source *)table[i])))
					.Times(1)
					.WillOnce(Return(nullptr));
		ret = data_pool_sessions_handler(((sd_event_source *)table[i]), 100, (EPOLLHUP | EPOLLERR), dp);
		ASSERT_EQ(0, ret);
	}
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__session_list_4_4)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)long(0);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (long i = 1; i < num_of_sessions; i++) {
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(i);	//set dummy value
		dps->next = NULL;
	}
	
	long table[] = {8,1,2,10,0,3};
	int result_table[] = {-1,0,0,-1,0,0};
	
	for (long i = 0; i < (sizeof(table)/sizeof(long)); i++) {
		EXPECT_CALL(lsm, sd_event_source_disable_unref(((sd_event_source *)table[i])))
					.Times(1)
					.WillOnce(Return(nullptr));
		ret = data_pool_sessions_handler(((sd_event_source *)table[i]), 100, (EPOLLHUP | EPOLLERR), dp);
		ASSERT_EQ(result_table[i], ret);
	}
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_sessions_handler__session_list_loop)
{
	int ret = -1;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1, sizeof(struct s_data_pool_service));

	//Force loop out
	struct s_data_pool_session *dps = NULL;
	dps = (struct s_data_pool_session*)malloc(sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = dps;	//list loop;
	dp->session_list = dps;

	EXPECT_CALL(lsm, sd_event_source_disable_unref((sd_event_source *)(0xa8a8)))
				.Times(1)
				.WillOnce(Return(nullptr));

	ret = data_pool_sessions_handler((sd_event_source *)(0xa8a8), 100, (EPOLLHUP | EPOLLERR), dp);
	ASSERT_EQ(-1, ret);

	// Repair loop list
	dps->next = NULL;
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(3)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}



//--------------------------------------------------------------------------------------------------------
//  data_pool_message_passanger test
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__argument_error)
{
	int ret = -1;

	// Argument error
	ret = data_pool_message_passanger(NULL);
	ASSERT_EQ(-2, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__no_session)
{
	int ret = -1;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1, sizeof(struct s_data_pool_service));

	// No session list
	ret = data_pool_message_passanger(dp);
	ASSERT_EQ(0, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__session_list_8)
{
	int ret = -1;
	const int num_of_sessions = 8;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (int i = 1; i < num_of_sessions; i++)
	{
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
		dps->next = NULL;
	}
	
	EXPECT_CALL(lsm, sd_event_source_get_io_fd((sd_event_source *)(0x8a8a)))
				.Times(num_of_sessions)
				.WillRepeatedly(Return(0xa8a8));
	EXPECT_CALL(sysiom, write(0xa8a8, _, _))
				.Times(num_of_sessions)
				.WillRepeatedly(Return(256));

	ret = data_pool_message_passanger(dp);
	ASSERT_EQ(-1, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(num_of_sessions + 2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__session_list_4)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (int i = 1; i < num_of_sessions; i++)
	{
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
		dps->next = NULL;
	}
	
	EXPECT_CALL(lsm, sd_event_source_get_io_fd((sd_event_source *)(0x8a8a)))
				.WillOnce(Return(100))
				.WillOnce(Return(101))
				.WillOnce(Return(102))
				.WillOnce(Return(103));

	EXPECT_CALL(sysiom, write(100, _, _))
				.WillRepeatedly(Return(256));
	EXPECT_CALL(sysiom, write(101, _, _))
				.WillRepeatedly(Return(256));
	EXPECT_CALL(sysiom, write(102, _, _))
				.WillRepeatedly(Return(256));
	EXPECT_CALL(sysiom, write(103, _, _))
				.WillRepeatedly(Return(256));

	ret = data_pool_message_passanger(dp);
	ASSERT_EQ(-1, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(num_of_sessions + 2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__session_list_4_errorno)
{
	int ret = -1;
	const int num_of_sessions = 4;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//8 session test
	struct s_data_pool_session *dps = NULL;
	//create top session
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	//create sessions
	for (int i = 1; i < num_of_sessions; i++)
	{
		dps->next = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
		dps = dps->next;
		dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
		dps->next = NULL;
	}
	
	EXPECT_CALL(lsm, sd_event_source_get_io_fd((sd_event_source *)(0x8a8a)))
				.WillOnce(Return(100))
				.WillOnce(Return(101))
				.WillOnce(Return(101))
				.WillOnce(Return(102))
				.WillOnce(Return(103));

	EXPECT_CALL(sysiom, write(100, _, _))
				.WillOnce(Return(256));
	EXPECT_CALL(sysiom, write(101, _, _))
				.WillOnce(SetErrnoAndReturn(EINTR, -1))
				.WillOnce(Return(256));
	EXPECT_CALL(sysiom, write(102, _, _))
				.WillOnce(SetErrnoAndReturn(EAGAIN, -1));
	EXPECT_CALL(sysiom, write(103, _, _))
				.WillOnce(Return(256));

	ret = data_pool_message_passanger(dp);
	ASSERT_EQ(-1, ret);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(num_of_sessions + 2)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test, test_data_pool_message_passanger__session_list_loop)
{
	int ret = -1;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	//Force loop out
	struct s_data_pool_session *dps = NULL;
	dps = (struct s_data_pool_session*)calloc(1, sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = dps;	//list loop;
	dp->session_list = dps;

	EXPECT_CALL(lsm, sd_event_source_get_io_fd((sd_event_source *)(0x8a8a)))
				.Times(DATA_POOL_SERVICE_SESSION_LIMIT)
				.WillRepeatedly(Return(0xa8a8));
	EXPECT_CALL(sysiom, write(0xa8a8, _, _))
				.Times(DATA_POOL_SERVICE_SESSION_LIMIT)
				.WillRepeatedly(Return(256));

	ret = data_pool_message_passanger(dp);
	ASSERT_EQ(-1, ret);

	// Repair loop list
	dps->next = NULL;
	
	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(3)
				.WillRepeatedly(Return(nullptr));
	
	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}


