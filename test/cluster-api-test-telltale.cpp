/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service-test.c
 * @brief	Unit test fot data-pool-service-test.c
 */
#include <gtest/gtest.h>

// Test Terget files ---------------------------------------
extern "C" {
#include "../lib/cluster-api-core.c"
#include "../lib/data-pool.c"

struct S_AGLCLUSTER_SERVICE_DATA_V1 zerodata;

static void ic_notify(uint64_t signal, IC_HMI_ON_OFF val)
{
	return;
}
}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_test_set_get_telltale : Test {};

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__turn_r)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_turn_r();
	ASSERT_EQ(0, val);
	
	data_pool_set_turn_r(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.turnR);

	val = data_pool_get_turn_r();
	ASSERT_EQ(1, val);
	
	onoffval = getTurnR();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.turnR = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.turnR = 1;
	val = data_pool_get_turn_r();
	ASSERT_EQ(1, val);

	data_pool_set_turn_r(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.turnR);

	val = data_pool_get_turn_r();
	ASSERT_EQ(0, val);

	onoffval = getTurnR();
	ASSERT_EQ(0, onoffval);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__turn_l)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_turn_l();
	ASSERT_EQ(0, val);
	
	data_pool_set_turn_l(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.turnL);

	val = data_pool_get_turn_l();
	ASSERT_EQ(1, val);

	onoffval = getTurnL();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.turnL = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.turnL = 1;
	val = data_pool_get_turn_l();
	ASSERT_EQ(1, val);

	data_pool_set_turn_l(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.turnL);

	val = data_pool_get_turn_l();
	ASSERT_EQ(0, val);

	onoffval = getTurnL();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__brake)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_brake();
	ASSERT_EQ(0, val);
	
	data_pool_set_brake(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.brake);

	val = data_pool_get_brake();
	ASSERT_EQ(1, val);

	onoffval = getBrake();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.brake = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.brake = 1;
	val = data_pool_get_brake();
	ASSERT_EQ(1, val);

	data_pool_set_brake(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.brake);

	val = data_pool_get_brake();
	ASSERT_EQ(0, val);

	onoffval = getBrake();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.seatbelt);

	val = data_pool_get_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.seatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.seatbelt = 1;
	val = data_pool_get_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.seatbelt);

	val = data_pool_get_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_right_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_right_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_right_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontRightSeatbelt);

	val = data_pool_get_front_right_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getFrontRightSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.frontRightSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontRightSeatbelt = 1;
	val = data_pool_get_front_right_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_front_right_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontRightSeatbelt);

	val = data_pool_get_front_right_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getFrontRightSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_center_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_center_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_center_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontCenterSeatbelt);

	val = data_pool_get_front_center_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getFrontCenterSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.frontCenterSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontCenterSeatbelt = 1;
	val = data_pool_get_front_center_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_front_center_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontCenterSeatbelt);

	val = data_pool_get_front_center_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getFrontCenterSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_left_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_left_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_left_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontLeftSeatbelt);

	val = data_pool_get_front_left_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getFrontLeftSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.frontLeftSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontLeftSeatbelt = 1;
	val = data_pool_get_front_left_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_front_left_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontLeftSeatbelt);

	val = data_pool_get_front_left_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getFrontLeftSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid1_right_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid1_right_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid1_right_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid1RightSeatbelt);

	val = data_pool_get_mid1_right_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getMid1RightSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.mid1RightSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid1RightSeatbelt = 1;
	val = data_pool_get_mid1_right_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid1_right_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid1RightSeatbelt);

	val = data_pool_get_mid1_right_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid1RightSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid1_center_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid1_center_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid1_center_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid1CenterSeatbelt);

	val = data_pool_get_mid1_center_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getMid1CenterSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.mid1CenterSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid1CenterSeatbelt = 1;
	val = data_pool_get_mid1_center_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid1_center_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid1CenterSeatbelt);

	val = data_pool_get_mid1_center_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid1CenterSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid1_left_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid1_left_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid1_left_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid1LeftSeatbelt);

	val = data_pool_get_mid1_left_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getMid1LeftSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.mid1LeftSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid1LeftSeatbelt = 1;
	val = data_pool_get_mid1_left_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid1_left_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid1LeftSeatbelt);

	val = data_pool_get_mid1_left_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid1LeftSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid2_right_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid2_right_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid2_right_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid2RightSeatbelt);

	val = data_pool_get_mid2_right_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getMid2RightSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.mid2RightSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid2RightSeatbelt = 1;
	val = data_pool_get_mid2_right_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid2_right_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid2RightSeatbelt);

	val = data_pool_get_mid2_right_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid2RightSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid2_center_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid2_center_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid2_center_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid2CenterSeatbelt);

	val = data_pool_get_mid2_center_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getMid2CenterSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.mid2CenterSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid2CenterSeatbelt = 1;
	val = data_pool_get_mid2_center_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid2_center_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid2CenterSeatbelt);

	val = data_pool_get_mid2_center_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid2CenterSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__mid2_left_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_mid2_left_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_mid2_left_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.mid2LeftSeatbelt);

	onoffval = getMid2LeftSeatbelt();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_mid2_left_seatbelt();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.mid2LeftSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.mid2LeftSeatbelt = 1;
	val = data_pool_get_mid2_left_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_mid2_left_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.mid2LeftSeatbelt);

	val = data_pool_get_mid2_left_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getMid2LeftSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__rear_right_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_rear_right_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_rear_right_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.rearRightSeatbelt);

	val = data_pool_get_rear_right_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getRearRightSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.rearRightSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.rearRightSeatbelt = 1;
	val = data_pool_get_rear_right_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_rear_right_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.rearRightSeatbelt);

	val = data_pool_get_rear_right_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getRearRightSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__rear_center_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_rear_center_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_rear_center_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.rearCenterSeatbelt);

	val = data_pool_get_rear_center_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getRearCenterSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.rearCenterSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.rearCenterSeatbelt = 1;
	val = data_pool_get_rear_center_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_rear_center_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.rearCenterSeatbelt);

	val = data_pool_get_rear_center_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getRearCenterSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__rear_left_seatbelt)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_rear_left_seatbelt();
	ASSERT_EQ(0, val);
	
	data_pool_set_rear_left_seatbelt(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.rearLeftSeatbelt);

	val = data_pool_get_rear_left_seatbelt();
	ASSERT_EQ(1, val);

	onoffval = getRearLeftSeatbelt();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.rearLeftSeatbelt = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.rearLeftSeatbelt = 1;
	val = data_pool_get_rear_left_seatbelt();
	ASSERT_EQ(1, val);

	data_pool_set_rear_left_seatbelt(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.rearLeftSeatbelt);

	val = data_pool_get_rear_left_seatbelt();
	ASSERT_EQ(0, val);

	onoffval = getRearLeftSeatbelt();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__high_beam)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_high_beam();
	ASSERT_EQ(0, val);
	
	data_pool_set_high_beam(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.highbeam);

	val = data_pool_get_high_beam();
	ASSERT_EQ(1, val);

	onoffval = getHighbeam();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.highbeam = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.highbeam = 1;
	val = data_pool_get_high_beam();
	ASSERT_EQ(1, val);

	data_pool_set_high_beam(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.highbeam);

	val = data_pool_get_high_beam();
	ASSERT_EQ(0, val);

	onoffval = getHighbeam();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.door);

	val = data_pool_get_door();
	ASSERT_EQ(1, val);

	onoffval = getDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.door = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.door = 1;
	val = data_pool_get_door();
	ASSERT_EQ(1, val);

	data_pool_set_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.door);

	val = data_pool_get_door();
	ASSERT_EQ(0, val);

	onoffval = getDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_right_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_right_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_right_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontRightDoor);

	val = data_pool_get_front_right_door();
	ASSERT_EQ(1, val);

	onoffval = getFrontRightDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.frontRightDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontRightDoor = 1;
	val = data_pool_get_front_right_door();
	ASSERT_EQ(1, val);

	data_pool_set_front_right_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontRightDoor);

	val = data_pool_get_front_right_door();
	ASSERT_EQ(0, val);

	onoffval = getFrontRightDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_left_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_left_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_left_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontLeftDoor);

	val = data_pool_get_front_left_door();
	ASSERT_EQ(1, val);

	onoffval = getFrontLeftDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.frontLeftDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontLeftDoor = 1;
	val = data_pool_get_front_left_door();
	ASSERT_EQ(1, val);

	data_pool_set_front_left_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontLeftDoor);

	val = data_pool_get_front_left_door();
	ASSERT_EQ(0, val);

	onoffval = getFrontLeftDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__rear_right_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_rear_right_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_rear_right_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.rearRightDoor);

	val = data_pool_get_rear_right_door();
	ASSERT_EQ(1, val);

	onoffval = getRearRightDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.rearRightDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.rearRightDoor = 1;
	val = data_pool_get_rear_right_door();
	ASSERT_EQ(1, val);

	data_pool_set_rear_right_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.rearRightDoor);

	val = data_pool_get_rear_right_door();
	ASSERT_EQ(0, val);

	onoffval = getRearRightDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__rear_left_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_rear_left_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_rear_left_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.rearLeftDoor);

	val = data_pool_get_rear_left_door();
	ASSERT_EQ(1, val);

	onoffval = getRearLeftDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.rearLeftDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.rearLeftDoor = 1;
	val = data_pool_get_rear_left_door();
	ASSERT_EQ(1, val);

	data_pool_set_rear_left_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.rearLeftDoor);

	val = data_pool_get_rear_left_door();
	ASSERT_EQ(0, val);

	onoffval = getRearLeftDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__trunk_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_trunk_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_trunk_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.trunkDoor);

	onoffval = getTrunkDoor();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_trunk_door();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.trunkDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.trunkDoor = 1;
	val = data_pool_get_trunk_door();
	ASSERT_EQ(1, val);

	data_pool_set_trunk_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trunkDoor);

	val = data_pool_get_trunk_door();
	ASSERT_EQ(0, val);

	onoffval = getTrunkDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__hood_door)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_hood_door();
	ASSERT_EQ(0, val);
	
	data_pool_set_hood_door(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.hoodDoor);

	val = data_pool_get_hood_door();
	ASSERT_EQ(1, val);

	onoffval = getHoodDoor();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.hoodDoor = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.hoodDoor = 1;
	val = data_pool_get_hood_door();
	ASSERT_EQ(1, val);

	data_pool_set_hood_door(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.hoodDoor);

	val = data_pool_get_hood_door();
	ASSERT_EQ(0, val);

	onoffval = getHoodDoor();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__eps)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_eps();
	ASSERT_EQ(0, val);
	
	data_pool_set_eps(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.eps);

	val = data_pool_get_eps();
	ASSERT_EQ(1, val);

	onoffval = getEps();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.eps = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.eps = 1;
	val = data_pool_get_eps();
	ASSERT_EQ(1, val);

	data_pool_set_eps(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.eps);

	val = data_pool_get_eps();
	ASSERT_EQ(0, val);

	onoffval = getEps();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__srs_airbag)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_srs_airbag();
	ASSERT_EQ(0, val);
	
	data_pool_set_srs_airbag(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.srsAirbag);

	val = data_pool_get_srs_airbag();
	ASSERT_EQ(1, val);

	onoffval = getSrsAirbag();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.srsAirbag = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.srsAirbag = 1;
	val = data_pool_get_srs_airbag();
	ASSERT_EQ(1, val);

	data_pool_set_srs_airbag(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.srsAirbag);

	val = data_pool_get_srs_airbag();
	ASSERT_EQ(0, val);

	onoffval = getSrsAirbag();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__abs)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_abs();
	ASSERT_EQ(0, val);
	
	data_pool_set_abs(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.abs);

	val = data_pool_get_abs();
	ASSERT_EQ(1, val);

	onoffval = getAbs();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.abs = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.abs = 1;
	val = data_pool_get_abs();
	ASSERT_EQ(1, val);

	data_pool_set_abs(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.abs);

	val = data_pool_get_abs();
	ASSERT_EQ(0, val);

	onoffval = getAbs();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__low_battery)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_low_battery();
	ASSERT_EQ(0, val);
	
	data_pool_set_low_battery(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.lowBattery);

	val = data_pool_get_low_battery();
	ASSERT_EQ(1, val);

	onoffval = getLowBattery();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.lowBattery = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.lowBattery = 1;
	val = data_pool_get_low_battery();
	ASSERT_EQ(1, val);

	data_pool_set_low_battery(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.lowBattery);

	val = data_pool_get_low_battery();
	ASSERT_EQ(0, val);

	onoffval = getLowBattery();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__oil_press)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_oil_press();
	ASSERT_EQ(0, val);
	
	data_pool_set_oil_press(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.oilPress);

	val = data_pool_get_oil_press();
	ASSERT_EQ(1, val);

	onoffval = getOilPress();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.oilPress = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.oilPress = 1;
	val = data_pool_get_oil_press();
	ASSERT_EQ(1, val);

	data_pool_set_oil_press(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.oilPress);

	val = data_pool_get_oil_press();
	ASSERT_EQ(0, val);

	onoffval = getOilPress();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__engine)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_engine();
	ASSERT_EQ(0, val);
	
	data_pool_set_engine(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.engine);

	val = data_pool_get_engine();
	ASSERT_EQ(1, val);

	onoffval = getEngine();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.engine = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.engine = 1;
	val = data_pool_get_engine();
	ASSERT_EQ(1, val);

	data_pool_set_engine(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.engine);

	val = data_pool_get_engine();
	ASSERT_EQ(0, val);

	onoffval = getEngine();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__fuel)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_fuel();
	ASSERT_EQ(0, val);
	
	data_pool_set_fuel(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.fuel);

	val = data_pool_get_fuel();
	ASSERT_EQ(1, val);

	onoffval = getFuel();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.fuel = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.fuel = 1;
	val = data_pool_get_fuel();
	ASSERT_EQ(1, val);

	data_pool_set_fuel(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.fuel);

	val = data_pool_get_fuel();
	ASSERT_EQ(0, val);

	onoffval = getFuel();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__immobi)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_immobi();
	ASSERT_EQ(0, val);
	
	data_pool_set_immobi(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.immobi);

	val = data_pool_get_immobi();
	ASSERT_EQ(1, val);

	onoffval = getImmobi();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.immobi = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.immobi = 1;
	val = data_pool_get_immobi();
	ASSERT_EQ(1, val);

	data_pool_set_immobi(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.immobi);

	val = data_pool_get_immobi();
	ASSERT_EQ(0, val);

	onoffval = getImmobi();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__tm_fail)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_tm_fail();
	ASSERT_EQ(0, val);
	
	data_pool_set_tm_fail(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.tmFail);

	val = data_pool_get_tm_fail();
	ASSERT_EQ(1, val);

	onoffval = getTMFail();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.tmFail = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.tmFail = 1;
	val = data_pool_get_tm_fail();
	ASSERT_EQ(1, val);

	data_pool_set_tm_fail(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.tmFail);

	val = data_pool_get_tm_fail();
	ASSERT_EQ(0, val);

	onoffval = getTMFail();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__esp_act)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_esp_act();
	ASSERT_EQ(0, val);
	
	data_pool_set_esp_act(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.espAct);

	val = data_pool_get_esp_act();
	ASSERT_EQ(1, val);

	onoffval = getEspAct();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.espAct = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.espAct = 1;
	val = data_pool_get_esp_act();
	ASSERT_EQ(1, val);

	data_pool_set_esp_act(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.espAct);

	val = data_pool_get_esp_act();
	ASSERT_EQ(0, val);

	onoffval = getEspAct();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__esp_off)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_esp_off();
	ASSERT_EQ(0, val);
	
	data_pool_set_esp_off(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.espOff);

	val = data_pool_get_esp_off();
	ASSERT_EQ(1, val);

	onoffval = getEspOff();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.espOff = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.espOff = 1;
	val = data_pool_get_esp_off();
	ASSERT_EQ(1, val);

	data_pool_set_esp_off(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.espOff);

	val = data_pool_get_esp_off();
	ASSERT_EQ(0, val);

	onoffval = getEspOff();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__adapting_lighting)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_adapting_lighting();
	ASSERT_EQ(0, val);
	
	data_pool_set_adapting_lighting(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.adaptingLighting);

	val = data_pool_get_adapting_lighting();
	ASSERT_EQ(1, val);

	onoffval = getAdaptingLighting();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.adaptingLighting = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.adaptingLighting = 1;
	val = data_pool_get_adapting_lighting();
	ASSERT_EQ(1, val);

	data_pool_set_adapting_lighting(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.adaptingLighting);

	val = data_pool_get_adapting_lighting();
	ASSERT_EQ(0, val);

	onoffval = getAdaptingLighting();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__auto_stop)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_auto_stop();
	ASSERT_EQ(0, val);
	
	data_pool_set_auto_stop(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.autoStop);

	val = data_pool_get_auto_stop();
	ASSERT_EQ(1, val);

	onoffval = getAutoStop();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.autoStop = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.autoStop = 1;
	val = data_pool_get_auto_stop();
	ASSERT_EQ(1, val);

	data_pool_set_auto_stop(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.autoStop);

	val = data_pool_get_auto_stop();
	ASSERT_EQ(0, val);

	onoffval = getAutoStop();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__auto_stop_fail)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_auto_stop_fail();
	ASSERT_EQ(0, val);
	
	data_pool_set_auto_stop_fail(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.autoStopFail);

	onoffval = getAutoStopFail();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_auto_stop_fail();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.autoStopFail = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.autoStopFail = 1;
	val = data_pool_get_auto_stop_fail();
	ASSERT_EQ(1, val);

	data_pool_set_auto_stop_fail(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.autoStopFail);

	val = data_pool_get_auto_stop_fail();
	ASSERT_EQ(0, val);

	onoffval = getAutoStopFail();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__parking_lights)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_parking_lights();
	ASSERT_EQ(0, val);
	
	data_pool_set_parking_lights(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.parkingLights);

	onoffval = getParkingLights();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_parking_lights();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.parkingLights = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.parkingLights = 1;
	val = data_pool_get_parking_lights();
	ASSERT_EQ(1, val);

	data_pool_set_parking_lights(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.parkingLights);

	val = data_pool_get_parking_lights();
	ASSERT_EQ(0, val);

	onoffval = getParkingLights();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__front_fog)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_front_fog();
	ASSERT_EQ(0, val);
	
	data_pool_set_front_fog(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.frontFog);

	onoffval = getFrontFog();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_front_fog();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.frontFog = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.frontFog = 1;
	val = data_pool_get_front_fog();
	ASSERT_EQ(1, val);

	data_pool_set_front_fog(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.frontFog);

	val = data_pool_get_front_fog();
	ASSERT_EQ(0, val);

	onoffval = getFrontFog();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__exterior_light_fault)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_exterior_light_fault();
	ASSERT_EQ(0, val);
	
	data_pool_set_exterior_light_fault(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.exteriorLightFault);

	onoffval = getExteriorLightFault();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_exterior_light_fault();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.exteriorLightFault = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.exteriorLightFault = 1;
	val = data_pool_get_exterior_light_fault();
	ASSERT_EQ(1, val);

	data_pool_set_exterior_light_fault(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.exteriorLightFault);

	val = data_pool_get_exterior_light_fault();
	ASSERT_EQ(0, val);

	onoffval = getExteriorLightFault();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__acc_fail)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_acc_fail();
	ASSERT_EQ(0, val);
	
	data_pool_set_acc_fail(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.accFail);

	onoffval = getAccFail();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_acc_fail();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.accFail = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.accFail = 1;
	val = data_pool_get_acc_fail();
	ASSERT_EQ(1, val);

	data_pool_set_acc_fail(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.accFail);

	val = data_pool_get_acc_fail();
	ASSERT_EQ(0, val);

	onoffval = getAccFail();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__ldw_off)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_ldw_off();
	ASSERT_EQ(0, val);
	
	data_pool_set_ldw_off(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.ldwOff);

	onoffval = getLdwOff();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_ldw_off();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.ldwOff = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.ldwOff = 1;
	val = data_pool_get_ldw_off();
	ASSERT_EQ(1, val);

	data_pool_set_ldw_off(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.ldwOff);

	val = data_pool_get_ldw_off();
	ASSERT_EQ(0, val);

	onoffval = getLdwOff();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__hill_descent)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_hill_descent();
	ASSERT_EQ(0, val);
	
	data_pool_set_hill_descent(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.hillDescent);

	val = data_pool_get_hill_descent();
	ASSERT_EQ(1, val);

	onoffval = getHillDescent();
	ASSERT_EQ(1, onoffval);

	g_agl_cluster_data_pool.data.hillDescent = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.hillDescent = 1;
	val = data_pool_get_hill_descent();
	ASSERT_EQ(1, val);

	data_pool_set_hill_descent(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.hillDescent);

	val = data_pool_get_hill_descent();
	ASSERT_EQ(0, val);

	onoffval = getHillDescent();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__auto_hi_beam_green)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_auto_hi_beam_green();
	ASSERT_EQ(0, val);
	
	data_pool_set_auto_hi_beam_green(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.autoHiBeamGreen);

	onoffval = getAutoHiBeamGreen();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_auto_hi_beam_green();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.autoHiBeamGreen = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.autoHiBeamGreen = 1;
	val = data_pool_get_auto_hi_beam_green();
	ASSERT_EQ(1, val);

	data_pool_set_auto_hi_beam_green(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.autoHiBeamGreen);

	val = data_pool_get_auto_hi_beam_green();
	ASSERT_EQ(0, val);

	onoffval = getAutoHiBeamGreen();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__auto_hi_beam_amber)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_auto_hi_beam_amber();
	ASSERT_EQ(0, val);
	
	data_pool_set_auto_hi_beam_amber(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.autoHiBeamAmber);

	onoffval = getAutoHiBeamAmber();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_auto_hi_beam_amber();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.autoHiBeamAmber = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.autoHiBeamAmber = 1;
	val = data_pool_get_auto_hi_beam_amber();
	ASSERT_EQ(1, val);

	data_pool_set_auto_hi_beam_amber(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.autoHiBeamAmber);

	val = data_pool_get_auto_hi_beam_amber();
	ASSERT_EQ(0, val);

	onoffval = getAutoHiBeamAmber();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__sports_mode)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_sports_mode();
	ASSERT_EQ(0, val);
	
	data_pool_set_sports_mode(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.sportsMode);

	onoffval = getSportsMode();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_sports_mode();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.sportsMode = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.sportsMode = 1;
	val = data_pool_get_sports_mode();
	ASSERT_EQ(1, val);

	data_pool_set_sports_mode(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.sportsMode);

	val = data_pool_get_sports_mode();
	ASSERT_EQ(0, val);

	onoffval = getSportsMode();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__ldw_operate)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_ldw_operate();
	ASSERT_EQ(0, val);
	
	data_pool_set_ldw_operate(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.ldwOperate);

	onoffval = getLdwOperate();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_ldw_operate();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.ldwOperate = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.ldwOperate = 1;
	val = data_pool_get_ldw_operate();
	ASSERT_EQ(1, val);

	data_pool_set_ldw_operate(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.ldwOperate);

	val = data_pool_get_ldw_operate();
	ASSERT_EQ(0, val);

	onoffval = getLdwOperate();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__general_warn)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_general_warn();
	ASSERT_EQ(0, val);
	
	data_pool_set_general_warn(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.generalWarn);

	onoffval = getGeneralWarn();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_general_warn();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.generalWarn = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.generalWarn = 1;
	val = data_pool_get_general_warn();
	ASSERT_EQ(1, val);

	data_pool_set_general_warn(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.generalWarn);

	val = data_pool_get_general_warn();
	ASSERT_EQ(0, val);

	onoffval = getGeneralWarn();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__driving_power_mode)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_driving_power_mode();
	ASSERT_EQ(0, val);
	
	data_pool_set_driving_power_mode(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.drivingPowerMode);

	onoffval = getDriverPowerMode();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_driving_power_mode();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.drivingPowerMode = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.drivingPowerMode = 1;
	val = data_pool_get_driving_power_mode();
	ASSERT_EQ(1, val);

	data_pool_set_driving_power_mode(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.drivingPowerMode);

	val = data_pool_get_driving_power_mode();
	ASSERT_EQ(0, val);

	onoffval = getDriverPowerMode();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__hot_temp)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_hot_temp();
	ASSERT_EQ(0, val);
	
	data_pool_set_hot_temp(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.hotTemp);

	onoffval = getHotTemp();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_hot_temp();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.hotTemp = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.hotTemp = 1;
	val = data_pool_get_hot_temp();
	ASSERT_EQ(1, val);

	data_pool_set_hot_temp(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.hotTemp);

	val = data_pool_get_hot_temp();
	ASSERT_EQ(0, val);

	onoffval = getHotTemp();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_set_get_telltale__low_temp)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_ON_OFF onoffval = IC_HMI_OFF;

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_low_temp();
	ASSERT_EQ(0, val);
	
	data_pool_set_low_temp(1);
	ASSERT_EQ(1, g_agl_cluster_data_pool.data.lowTemp);

	onoffval = getLowTemp();
	ASSERT_EQ(1, onoffval);

	val = data_pool_get_low_temp();
	ASSERT_EQ(1, val);

	g_agl_cluster_data_pool.data.lowTemp = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.lowTemp = 1;
	val = data_pool_get_low_temp();
	ASSERT_EQ(1, val);

	data_pool_set_low_temp(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.lowTemp);

	val = data_pool_get_low_temp();
	ASSERT_EQ(0, val);

	onoffval = getLowTemp();
	ASSERT_EQ(0, onoffval);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_telltale, test_data_pool_test_check_change__1)
{
	uint64_t signals = 0;
	uint64_t refsignals = 0;
	bool ret = false;
	struct S_AGLCLUSTER_SERVICE_DATA_V1 data;
	
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));
	memset(&data,0,sizeof(data));

	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	// No change
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);

	registerIcHmi(IC_HMI_TT_ALL, ic_notify);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_LOW_TEMP;
	data_pool_set_low_temp(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);


	refsignals |= IC_HMI_TT_HOT_TEMP;
	data_pool_set_hot_temp(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_DRIVING_POWER_MODE;
	data_pool_set_driving_power_mode(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_SPORTS_MODE;
	data_pool_set_sports_mode(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_GENERAL_WARN;
	data_pool_set_general_warn(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_LDW_OPERATE;
	data_pool_set_ldw_operate(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_AUTO_HI_BEAM_AMBER;
	data_pool_set_auto_hi_beam_amber(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_AUTO_HI_BEAM_GREEN;
	data_pool_set_auto_hi_beam_green(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_HILL_DESCENT;
	data_pool_set_hill_descent(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_LDW_OFF;
	data_pool_set_ldw_off(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ACC_FAIL;
	data_pool_set_acc_fail(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_EXTERIOR_LIGHT_FAULT;
	data_pool_set_exterior_light_fault(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_FRONT_FOG;
	data_pool_set_front_fog(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_PARKING_LIGHTS;
	data_pool_set_parking_lights(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_AUTO_STOP_FAIL;
	data_pool_set_auto_stop_fail(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_AUTO_STOP;
	data_pool_set_auto_stop(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ADAPTING_LIGHTING;
	data_pool_set_adapting_lighting(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ESP_OFF;
	data_pool_set_esp_off(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ESP_ACT;
	data_pool_set_esp_act(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_TM_FAIL;
	data_pool_set_tm_fail(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_IMMOBI;
	data_pool_set_immobi(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_FUEL;
	data_pool_set_fuel(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ENGINE;
	data_pool_set_engine(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_OIL_PRESS;
	data_pool_set_oil_press(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_LOW_BATTERY;
	data_pool_set_low_battery(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_ABS;
	data_pool_set_abs(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_SRS_AIRBAG;
	data_pool_set_srs_airbag(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_EPS;
	data_pool_set_eps(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_DOOR;
	data_pool_set_door(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_HIGHBEAM;
	data_pool_set_high_beam(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_SEATBELT;
	data_pool_set_seatbelt(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_BRAKE;
	data_pool_set_brake(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_TURN_L;
	data_pool_set_turn_l(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals |= IC_HMI_TT_TURN_R;
	data_pool_set_turn_r(1);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

	refsignals &= ~IC_HMI_TT_LOW_TEMP;
	data_pool_set_low_temp(0);
	signals = data_pool_check_change_v1(&data);
	ASSERT_EQ(refsignals, signals);
	ret = notifyCheck(signals);
	ASSERT_EQ(true, ret);

}



