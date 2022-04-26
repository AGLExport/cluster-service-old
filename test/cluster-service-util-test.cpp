/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service-util-test.c
 * @brief	Unit test fot cluster-service-util.c
 */
#include <gtest/gtest.h>
#include "mock/libsystemd_mock.hpp"
#include "mock/libpthread_mock.hpp"

// Test Terget files ---------------------------------------
extern "C" {
#include "../lib/cluster-service-util.c"


}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct cluster_service_util_test : Test, LibsystemdMockBase, LibpthreadMockBase {};

TEST_F(cluster_service_util_test, test_signal_setup)
{
	int ret = -1;

	// Argument error
	ret = signal_setup(NULL);
	ASSERT_EQ(-2, ret);

	//dummy data alloc
	sd_event *ev = NULL;
	ev = (sd_event *)calloc(128,1);

	// Success 
	EXPECT_CALL(lpm, pthread_sigmask(SIG_BLOCK, _, _)).WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_signal(ev, nullptr, SIGTERM, nullptr, nullptr)).WillOnce(Return(0));
	ret = signal_setup(ev);
	ASSERT_EQ(0, ret);

	// add signal failed
	EXPECT_CALL(lpm, pthread_sigmask(SIG_BLOCK, _, _)).WillOnce(Return(0));
	EXPECT_CALL(lpm, pthread_sigmask(SIG_UNBLOCK, _, _)).WillOnce(Return(0));
	EXPECT_CALL(lsm, sd_event_add_signal(ev, nullptr, SIGTERM, nullptr, nullptr)).WillOnce(Return(-1));
	ret = signal_setup(ev);
	ASSERT_EQ(-1, ret);

	// Sigmask failed
	EXPECT_CALL(lpm, pthread_sigmask(SIG_BLOCK, _, _)).WillOnce(Return(-1));
	ret = signal_setup(ev);
	ASSERT_EQ(-1, ret);

	// clean
	free(ev);
}

