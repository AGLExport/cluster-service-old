/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.c
 * @brief	main source file for cluster-service
 */
#include <gtest/gtest.h>

// Test Terget files ---------------------------------------
extern "C" {
#include "../src/data-pool-service.c"


}
// Test Terget files ---------------------------------------


TEST(data_pool_service_test, test_data_pool_message_passanger)
{
	struct s_data_pool_service dp;
	EXPECT_EQ(1, data_pool_message_passanger(NULL));

	memset(&dp,0,sizeof(dp));
	EXPECT_EQ(1, data_pool_message_passanger(&dp));
}

