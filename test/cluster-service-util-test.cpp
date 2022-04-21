/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.c
 * @brief	main source file for cluster-service
 */
#include <gtest/gtest.h>
#include "mock/libsystemd_mock.hpp"

// Test Terget files ---------------------------------------
extern "C" {
#include "../src/cluster-service-util.c"


}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct cluster_service_util_test : Test, LibsystemdMockBase {};

TEST_F(cluster_service_util_test, test_signal_setup)
{
	int ret = -1;

	// Argument error
	ret = signal_setup(NULL);
	ASSERT_EQ(-2, ret);

	//dummy data
	sd_event *ev = NULL;
	ev = (sd_event *)calloc(128,1);
	
	EXPECT_CALL(lsm, sd_event_add_signal(ev, nullptr, SIGTERM, nullptr, nullptr)).WillOnce(Return(0));
	ret = signal_setup(ev);
	ASSERT_EQ(0, ret);

	EXPECT_CALL(lsm, sd_event_add_signal(ev, nullptr, SIGTERM, nullptr, nullptr)).WillOnce(Return(-1));
	ret = signal_setup(ev);
	ASSERT_EQ(-1, ret);
	
	free(ev);
}

