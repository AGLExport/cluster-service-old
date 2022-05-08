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

struct data_pool_service_test_timer : Test, LibsystemdMockBase, SyscallIOMockBase {};

//--------------------------------------------------------------------------------------------------------
//  data_pool_service_cleanup test
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_service_test_timer, test_timer_handler__timer_handler_call)
{
	int ret = -1;
	uint64_t refval = 0;

	//dummy data alloc
	data_pool_service_handle dp = (data_pool_service_handle)calloc(1,sizeof(struct s_data_pool_service));
	dp->notification_timer = (struct s_data_pool_notification_timer*)calloc(1,sizeof(struct s_data_pool_notification_timer));

	// sd_event_source_set_time fail
	EXPECT_CALL(lsm, sd_event_source_set_time(_,_))
				.Times(1).WillOnce(Return(-1));
	
	ret = timer_handler(dp->notification_timer->timer_evsource, 0, (void *)dp);
	ASSERT_EQ(-1, ret);
	
	// success and timer interval
	dp->notification_timer->timerval = 976000;
	refval = dp->notification_timer->timerval + get_data_pool_notification_interval();
	EXPECT_CALL(lsm, sd_event_source_set_time(_,_))
				.Times(1).WillOnce(Return(0));
	
	ret = timer_handler(dp->notification_timer->timer_evsource, 0, (void *)dp);
	ASSERT_EQ(0, ret);
	ASSERT_EQ(refval, dp->notification_timer->timerval);

	//clean dummy data
	EXPECT_CALL(lsm, sd_event_source_disable_unref(_))
				.Times(2)
				.WillRepeatedly(Return(nullptr));

	ret = data_pool_service_cleanup(dp);
	ASSERT_EQ(0, ret);
}

