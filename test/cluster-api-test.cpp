/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service-test.c
 * @brief	Unit test fot data-pool-service-test.c
 */
#include <gtest/gtest.h>
#include "mock/libpthread_mock.hpp"

// Test Terget files ---------------------------------------
extern "C" {
#include "../lib/cluster-api-core.c"
#include "../lib/data-pool.c"

struct S_AGLCLUSTER_SERVICE_DATA_V1 zerodata;

static void ic_notify(uint64_t signal, IC_HMI_ON_OFF val)
{
	return;
}

bool notifyCheck_true(uint64_t signals)
{
	return true;
}
bool notifyCheck_false(uint64_t signals)
{
	return false;
}
}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_test_others : Test, LibpthreadMockBase {};
struct data_pool_test_set_get_others : Test {};

//--------------------------------------------------------------------------------------------------------
/*TEST_F(data_pool_test_others, test_data_pool_test_data_pool_lock__false)
{
	bool ret = true;

	EXPECT_CALL(lpm, pthread_mutex_lock(_))
			.WillOnce(Return(-1));
	ret = data_pool_lock();
	ASSERT_EQ(false, ret);
}*/
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_others, test_data_pool_test_data_pool_lock__true)
{
	bool ret = false;

	/*EXPECT_CALL(lpm, pthread_mutex_lock(_))
			.WillOnce(Return(0));*/
	ret = data_pool_lock();
	ASSERT_EQ(true, ret);
}
//--------------------------------------------------------------------------------------------------------
/*TEST_F(data_pool_test_others, test_data_pool_test_data_pool_unlock__false)
{
	bool ret = true;

	EXPECT_CALL(lpm, pthread_mutex_unlock(_))
			.WillOnce(Return(-1));
	ret = data_pool_unlock();
	ASSERT_EQ(false, ret);
}*/
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_others, test_data_pool_test_data_pool_unlock__true)
{
	bool ret = false;

/*	EXPECT_CALL(lpm, pthread_mutex_unlock(_))
			.WillOnce(Return(0));*/
	ret = data_pool_unlock();
	ASSERT_EQ(true, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_others, test_data_pool_test_data_pool_register_change_notify__true_false)
{
	bool ret = true;

	ret = data_pool_register_change_notify(NULL);
	ASSERT_EQ(true, ret);

	ret = data_pool_register_change_notify(notifyCheck);
	ASSERT_EQ(true, ret);

	ret = data_pool_register_change_notify(notifyCheck);
	ASSERT_EQ(false, ret);

	ret = data_pool_register_change_notify(NULL);
	ASSERT_EQ(true, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_others, test_data_pool_test_data_pool_set_v1__true_false)
{
	int ret = -1;
	bool bret = true;
	struct S_AGLCLUSTER_SERVICE_DATA_V1 dmydata;

	memset(&dmydata,0,sizeof(dmydata));

	// ff
	ret = data_pool_set_v1(&zerodata);
	ASSERT_EQ(0, ret);

	// tf
	bret = data_pool_register_change_notify(notifyCheck_true);
	ASSERT_EQ(true, bret);

	ret = data_pool_set_v1(&dmydata);
	ASSERT_EQ(0, ret);

	// tt - t
	dmydata.turnR = 1;

	ret = data_pool_set_v1(&dmydata);
	ASSERT_EQ(0, ret);

	// ft
	dmydata.turnL = 1;
	bret = data_pool_register_change_notify(NULL);
	ASSERT_EQ(true, bret);

	ret = data_pool_set_v1(&dmydata);
	ASSERT_EQ(0, ret);

	// tt - f
	dmydata.brake = 1;
	bret = data_pool_register_change_notify(notifyCheck_false);
	ASSERT_EQ(true, bret);

	ret = data_pool_set_v1(&dmydata);
	ASSERT_EQ(0, ret);
	
	//cleas
	ret = data_pool_set_v1(&zerodata);
	ASSERT_EQ(0, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_others, test_data_pool_test_data_pool_get_v1__true)
{
	int ret = -1;
	bool bret = true;
	struct S_AGLCLUSTER_SERVICE_DATA_V1 dmydata;

	memset(&dmydata,0,sizeof(dmydata));

	// ff
	ret = data_pool_get_v1(&dmydata);
	ASSERT_EQ(0, ret);
}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__if)
{
	bool ret = false;

	ret = clusterInit();
	ASSERT_EQ(true, ret);
	
	ret = clusterTerm();
	ASSERT_EQ(true, ret);

	ret = registerIcHmi(IC_HMI_TT_TURN_R, NULL);
	ASSERT_EQ(false, ret);

	ret = registerIcHmi(IC_HMI_TT_TURN_R, ic_notify);
	ASSERT_EQ(true, ret);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__gear_at_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_GEAR_AT_VAL apival = IC_HMI_AT_UNUSED;
	/*
	 0：IC_HMI_AT_OFF
	 1：IC_HMI_AT_PARKING
	 2：IC_HMI_AT_REVERSE
	 3：IC_HMI_AT_NEUTRAL
	 4：IC_HMI_AT_DRIVE
	 5：IC_HMI_AT_SECOND
	 6：IC_HMI_AT_LOW_GEAR
	 7：IC_HMI_AT_FIRST
	 8：IC_HMI_AT_MANUAL
	 9：IC_HMI_AT_BRAKE
	 10：IC_HMI_AT_ALL_ON
	 11：IC_HMI_AT_ALL_OFF
	 12：IC_HMI_AT_UNUSED
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_gear_at_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_gear_at_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.gearAtVal);

	val = data_pool_get_gear_at_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.gearAtVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.gearAtVal = INT32_MAX;
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_gear_at_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.gearAtVal);

	data_pool_set_gear_at_val(0);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(0, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_OFF, (int32_t)apival);

	data_pool_set_gear_at_val(1);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(1, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_PARKING, (int32_t)apival);

	data_pool_set_gear_at_val(2);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(2, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_REVERSE, (int32_t)apival);

	data_pool_set_gear_at_val(3);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(3, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_NEUTRAL, (int32_t)apival);

	data_pool_set_gear_at_val(4);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(4, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_DRIVE, (int32_t)apival);

	data_pool_set_gear_at_val(5);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(5, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_SECOND, (int32_t)apival);

	data_pool_set_gear_at_val(6);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(6, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_LOW_GEAR, (int32_t)apival);

	data_pool_set_gear_at_val(7);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(7, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_FIRST, (int32_t)apival);

	data_pool_set_gear_at_val(8);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(8, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_MANUAL, (int32_t)apival);

	data_pool_set_gear_at_val(9);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(9, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_BRAKE, (int32_t)apival);

	data_pool_set_gear_at_val(10);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(10, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_ALL_ON, (int32_t)apival);

	data_pool_set_gear_at_val(11);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(11, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_ALL_OFF, (int32_t)apival);

	data_pool_set_gear_at_val(12);
	val = data_pool_get_gear_at_val();
	ASSERT_EQ(12, val);

	apival = getGearAtVal();
	ASSERT_EQ(IC_HMI_AT_UNUSED, (int32_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__gear_mt_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_GEAR_MT_VAL apival = IC_HMI_MT_EIGHTH;
	/*
	 0：IC_HMI_MT_OFF
	 1：IC_HMI_MT_FIRST
	 2：IC_HMI_MT_SECOND
	 3：IC_HMI_MT_THIRD
	 4：IC_HMI_MT_FOURTH
	 5：IC_HMI_MT_FIFTH
	 6：IC_HMI_MT_SIXTH
	 7：IC_HMI_MT_SEVENTH
	 8：IC_HMI_MT_EIGHTH
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_gear_mt_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.gearMtVal);

	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.gearMtVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.gearMtVal = INT32_MAX;
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_gear_mt_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.gearMtVal);

	data_pool_set_gear_mt_val(0);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(0, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_OFF, (int32_t)apival);

	data_pool_set_gear_mt_val(1);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(1, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_FIRST, (int32_t)apival);

	data_pool_set_gear_mt_val(2);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(2, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_SECOND, (int32_t)apival);

	data_pool_set_gear_mt_val(3);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(3, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_THIRD, (int32_t)apival);

	data_pool_set_gear_mt_val(4);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(4, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_FOURTH, (int32_t)apival);

	data_pool_set_gear_mt_val(5);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(5, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_FIFTH, (int32_t)apival);

	data_pool_set_gear_mt_val(6);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(6, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_SIXTH, (int32_t)apival);

	data_pool_set_gear_mt_val(7);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(7, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_SEVENTH, (int32_t)apival);

	data_pool_set_gear_mt_val(8);
	val = data_pool_get_gear_mt_val();
	ASSERT_EQ(8, val);

	apival = getGearMtVal();
	ASSERT_EQ(IC_HMI_MT_EIGHTH, (int32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__speed_analog_val)
{
	int ret = -1;
	uint32_t val = 0;
	unsigned long apival = 0;
	uint64_t checker = 0;

	const uint32_t minimam_val = 0x00000000ul;	//Min Speed (0.00)
	const uint32_t max_val = 0x00007530ul;	// Max Speed (300.00)
	const uint32_t out_of_range_start_val = 0x00007531ul;	//invalid value (300.01~42949672.95)
	const uint32_t out_of_range_end_val = 0xFFFFFFFFul;	//invalid value (300.01~42949672.95)

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_speed_analog_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_speed_analog_val(UINT32_MAX);
	ASSERT_EQ(UINT32_MAX, g_agl_cluster_data_pool.data.spAnalogVal);

	val = data_pool_get_speed_analog_val();
	ASSERT_EQ(UINT32_MAX, val);

	g_agl_cluster_data_pool.data.spAnalogVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.spAnalogVal = UINT32_MAX;
	val = data_pool_get_speed_analog_val();
	ASSERT_EQ(UINT32_MAX, val);

	data_pool_set_speed_analog_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.spAnalogVal);

	checker = 0;
	for (uint32_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_speed_analog_val(i);
		val = data_pool_get_speed_analog_val();
		ASSERT_EQ(i, val);

		apival = getSpAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_speed_analog_val(i);
		val = data_pool_get_speed_analog_val();
		ASSERT_EQ(i, val);

		apival = getSpAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_end_val-100; (i <= out_of_range_end_val) && (out_of_range_start_val < i);i++) {
		data_pool_set_speed_analog_val(i);
		val = data_pool_get_speed_analog_val();
		ASSERT_EQ(i, val);

		apival = getSpAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__analog_digital_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_SP_UNIT_VAL apival = IC_HMI_SP_MPH;
	/*
	 0：IC_HMI_SP_KM_H
	 1：IC_HMI_SP_MPH
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_speed_analog_digital_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_speed_analog_digital_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.spAnaDigUnitVal);

	val = data_pool_get_speed_analog_digital_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.spAnaDigUnitVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.spAnaDigUnitVal = INT32_MAX;
	val = data_pool_get_speed_analog_digital_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_speed_analog_digital_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.spAnaDigUnitVal);

	data_pool_set_speed_analog_digital_val(0);
	val = data_pool_get_speed_analog_digital_val();
	ASSERT_EQ(0, val);

	apival = getSpAnaDigUnitVal();
	ASSERT_EQ(IC_HMI_SP_KM_H, (int32_t)apival);

	data_pool_set_speed_analog_digital_val(1);
	val = data_pool_get_speed_analog_digital_val();
	ASSERT_EQ(1, val);

	apival = getSpAnaDigUnitVal();
	ASSERT_EQ(IC_HMI_SP_MPH, (int32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_others, test_data_pool_test_set_get_others__tacho_analog_val)
{
	int ret = -1;
	uint32_t val = 0;
	unsigned long apival = 0;
	uint64_t checker = 0;

	const uint32_t minimam_val = 0x00000000ul;	//Min rpm (0)
	const uint32_t max_val = 0x00004e20ul;	// Max rpm (20000)
	const uint32_t out_of_range_start_val = 0x00004e21ul;	//invalid value (20001~4294967295)
	const uint32_t out_of_range_end_val = 0xFFFFFFFFul;	//invalid value (20001~4294967295)

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_tacho_analog_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_tacho_analog_val(UINT32_MAX);
	ASSERT_EQ(UINT32_MAX, g_agl_cluster_data_pool.data.taAnalogVal);

	val = data_pool_get_tacho_analog_val();
	ASSERT_EQ(UINT32_MAX, val);

	g_agl_cluster_data_pool.data.taAnalogVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.taAnalogVal = UINT32_MAX;
	val = data_pool_get_tacho_analog_val();
	ASSERT_EQ(UINT32_MAX, val);

	data_pool_set_tacho_analog_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.taAnalogVal);

	checker = 0;
	for (uint32_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_tacho_analog_val(i);
		val = data_pool_get_tacho_analog_val();
		ASSERT_EQ(i, val);

		apival = getTaAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_tacho_analog_val(i);
		val = data_pool_get_tacho_analog_val();
		ASSERT_EQ(i, val);

		apival = getTaAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_end_val-100; (i <= out_of_range_end_val) && (out_of_range_start_val < i);i++) {
		data_pool_set_tacho_analog_val(i);
		val = data_pool_get_tacho_analog_val();
		ASSERT_EQ(i, val);

		apival = getTaAnalogVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}
}
