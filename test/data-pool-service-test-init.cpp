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
#define DATA_POOL_STATIC_CONFIG_DATA_DISABLE
#include "../src/data-pool-service.c"
/** data pool service static configurator. It shall be set statically bosth service and client library.*/
struct s_data_pool_service_configure {
	uint64_t notification_interval; /**< Parametor for data pool notification interval */

	int32_t data_pool_service_session_limit; /**< Parametor for internal limitation for datapool service
						    sessions. It use link list search limit. */

	char socket_name[92]; /**< data pool socket name */
};
typedef struct s_data_pool_service_configure data_pool_service_staticconfig;

struct s_data_pool_service_configure g_config;

const struct s_data_pool_service_configure g_config_a = {
	(16 * 1000),	  // usec
	(100), // counts
	"\0/agl/agl-cluster-service",
};

const struct s_data_pool_service_configure g_config_b = {
	(256 * 1000),	  // usec
	(1), // counts
	"/tmp/agl/agl-cluster-service",
};

/**
 * Getter for the data pool notification interval.
 *
 * @return uint64_t	 Interval time for the data pool notification.
 */
uint64_t get_data_pool_notification_interval(void)
{
	return g_config.notification_interval;
}

/**
 * Getter for the data pool service session limit.
 *
 * @return int	 Session limit for the data pool server.
 */
int get_data_pool_service_session_limit(void)
{
	return (int) g_config.data_pool_service_session_limit;
}

/**
 * Getter for the data pool service socket name.
 *
 * @param [in]	str		Pointer to the socket name string buffer
 * @param [in]	len		Buffer bytes for the socket name string buffer
 * @return int	>0	Socket name bytes.
 *				0<	Param len is smaller than required size. - required size.
 */
int get_data_pool_service_socket_name(char *str, int len)
{
	if (len >= sizeof(g_config.socket_name)) {
		(void) memcpy(str, g_config.socket_name, sizeof(g_config.socket_name));

		if (g_config.socket_name[0] == '\0') {
			// abstract socket
			int bytes = 1;
			for (bytes = 1; bytes < sizeof(g_config.socket_name); bytes++) {
				if (g_config.socket_name[bytes] == '\0')
					break;
			}
			return bytes;
		} else {
			// socket file
			return sizeof(g_config.socket_name);
		}
	}
	return -1;
}

/**
 * Getter for the data pool service socket name type.
 *
 * @return int	 0	Socket file
 * @return int	 1	Abstract socket
 */
int get_data_pool_service_socket_name_type(void)
{
	int ret = 0;

	if (g_config.socket_name[0] == '\0')
		ret = 1;

	return ret;
}


}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_service_test_init : Test, LibsystemdMockBase, SyscallIOMockBase {};


//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__arg_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	ret = data_pool_service_setup(NULL, NULL);
	ASSERT_EQ(-2, ret);
	
	ret = data_pool_service_setup(NULL, &dp);
	ASSERT_EQ(-2, ret);

	ret = data_pool_service_setup(event, NULL);
	ASSERT_EQ(-2, ret);
}

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__socket_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_b,sizeof(g_config_b));

	// socket error
	EXPECT_CALL(sysiom, unlink(_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__bind_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	EXPECT_CALL(sysiom, close(101))
			.WillOnce(Return(0));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__listen_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	EXPECT_CALL(sysiom, close(101))
			.WillOnce(Return(0));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__sd_event_add_io_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	EXPECT_CALL(sysiom, close(101))
			.WillOnce(Return(0));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__sd_event_source_set_io_fd_own_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own(_,1))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));
	EXPECT_CALL(sysiom, close(101))
			.WillOnce(Return(0));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__sd_event_now_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own(_,1))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_now((sd_event *)(0xaaff),CLOCK_MONOTONIC,_))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__sd_event_add_time_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own(_,1))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_now((sd_event *)(0xaaff),CLOCK_MONOTONIC,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_time((sd_event *)(0xaaff),_,CLOCK_MONOTONIC,_,_,timer_handler,_))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__sd_event_source_set_enabled_error)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own(_,1))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_now((sd_event *)(0xaaff),CLOCK_MONOTONIC,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_time((sd_event *)(0xaaff),_,CLOCK_MONOTONIC,_,_,timer_handler,_))
			.WillOnce(Invoke([](sd_event *event, sd_event_source **source, clockid_t clock, uint64_t usec,
				uint64_t accuracy, sd_event_time_handler_t handler, void *userdata) {
						(*source) = (sd_event_source *)0x7777;
						return 0;
					}));
	EXPECT_CALL(lsm, sd_event_source_set_enabled((sd_event_source *)(0x7777),SD_EVENT_ON))
			.WillOnce(Return(-1));
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(-1, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_setup__success)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;
	sd_event *event = (sd_event *)(0xaaff);

	// clean global
	memset(&g_packet,0,sizeof(g_packet));
	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	// socket error
	EXPECT_CALL(sysiom, socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX))
			.WillOnce(Return(101));
	EXPECT_CALL(sysiom, bind(101,_,_))
			.WillOnce(Return(0));
	EXPECT_CALL(sysiom, listen(101,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_io((sd_event *)(0xaaff), _, 101, EPOLLIN, _, _))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_source_set_io_fd_own(_,1))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_now((sd_event *)(0xaaff),CLOCK_MONOTONIC,_))
			.WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_time((sd_event *)(0xaaff),_,CLOCK_MONOTONIC,_,_,timer_handler,_))
			.WillOnce(Invoke([](sd_event *event, sd_event_source **source, clockid_t clock, uint64_t usec,
				uint64_t accuracy, sd_event_time_handler_t handler, void *userdata) {
						(*source) = (sd_event_source *)0x7777;
						return 0;
					}));
	EXPECT_CALL(lsm, sd_event_source_set_enabled((sd_event_source *)(0x7777),SD_EVENT_ON))
			.WillOnce(Return(0));

	ret = data_pool_service_setup(event, &dp);
	ASSERT_EQ(0, ret);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKETHEADER_MAGIC, g_packet.header.magic);
	ASSERT_EQ(AGLCLUSTER_SERVICE_PACKET_VERSION_V1, g_packet.header.version);
	

	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_cleanup__success_1)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;

	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	//dummy data alloc
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	dp->notification_timer = (struct s_data_pool_notification_timer*)calloc(1,sizeof(struct s_data_pool_notification_timer));

	//create top session
	struct s_data_pool_session *dps = NULL;
	dps = (struct s_data_pool_session*)malloc(sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = NULL;
	dp->session_list = dps;

	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2+1)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_cleanup__success_2)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;

	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));
	g_config.data_pool_service_session_limit = 0;

	//dummy data alloc
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	dp->notification_timer = (struct s_data_pool_notification_timer*)calloc(1,sizeof(struct s_data_pool_notification_timer));

	//create top session
	struct s_data_pool_session *dps = NULL;
	dps = (struct s_data_pool_session*)malloc(sizeof(struct s_data_pool_session));
	dps->socket_evsource = (sd_event_source *)(0x8a8a);	//set dummy value
	dps->next = NULL;	//list loop;
	dp->session_list = dps;

	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
	free(dps);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_init, test_data_pool_service_cleanup__success_3)
{
	int ret = -1;
	data_pool_service_handle dp = NULL;

	// test static config set
	memcpy(&g_config,&g_config_a,sizeof(g_config_a));

	//dummy data alloc
	dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));

	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(1)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}
