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

}
// Test Terget files ---------------------------------------
using namespace ::testing;

struct data_pool_test_set_get_trip : Test {};

//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__trip_a_val)
{
	int ret = -1;
	uint32_t val = 0;
	unsigned long apival = 0;
	uint64_t checker = 0;

	const uint32_t minimam_val = 0x00000000ul;	//TripA Min (0.0)
	const uint32_t max_val = 0x0001869Ful;	// TripA Max (9999.9)
	const uint32_t out_of_range_start_val = 0x00018670ul;	//invalid value (10000.0~429496729.5)
	const uint32_t out_of_range_end_val = 0xFFFFFFFEul;	//invalid value (10000.0~429496729.5)
	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/
	
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_trcom_trip_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_trcom_trip_a_val(UINT32_MAX);
	ASSERT_EQ(UINT32_MAX, g_agl_cluster_data_pool.data.trcomTripAVal);

	val = data_pool_get_trcom_trip_a_val();
	ASSERT_EQ(UINT32_MAX, val);

	g_agl_cluster_data_pool.data.trcomTripAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.trcomTripAVal = UINT32_MAX;
	val = data_pool_get_trcom_trip_a_val();
	ASSERT_EQ(UINT32_MAX, val);

	data_pool_set_trcom_trip_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trcomTripAVal);

	checker = 0;
	for (uint32_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_trcom_trip_a_val(i);
		val = data_pool_get_trcom_trip_a_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripAVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_trcom_trip_a_val(i);
		val = data_pool_get_trcom_trip_a_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripAVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint32_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_trcom_trip_a_val(i);
		val = data_pool_get_trcom_trip_a_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripAVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/
	data_pool_set_trcom_trip_a_val(0xFFFFFFFEul);
	val = data_pool_get_trcom_trip_a_val();
	ASSERT_EQ(0xFFFFFFFEul, val);

	apival = getTrcomTripAVal();
	ASSERT_EQ(0xFFFFFFFEul, (uint32_t)apival);

	data_pool_set_trcom_trip_a_val(0xFFFFFFFFul);
	val = data_pool_get_trcom_trip_a_val();
	ASSERT_EQ(0xFFFFFFFFul, val);

	apival = getTrcomTripAVal();
	ASSERT_EQ(0xFFFFFFFFul, (uint32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__trip_b_val)
{
	int ret = -1;
	uint32_t val = 0;
	unsigned long apival = 0;
	uint64_t checker = 0;

	const uint32_t minimam_val = 0x00000000ul;	//TripB Min (0.0)
	const uint32_t max_val = 0x0001869Ful;	// TripB Max (9999.9)
	const uint32_t out_of_range_start_val = 0x00018670ul;	//invalid value (10000.0~429496729.5)
	const uint32_t out_of_range_end_val = 0xFFFFFFFEul;	//invalid value (10000.0~429496729.5)
	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/
	
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_trcom_trip_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_trcom_trip_b_val(UINT32_MAX);
	ASSERT_EQ(UINT32_MAX, g_agl_cluster_data_pool.data.trcomTripBVal);

	val = data_pool_get_trcom_trip_b_val();
	ASSERT_EQ(UINT32_MAX, val);

	g_agl_cluster_data_pool.data.trcomTripBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.trcomTripBVal = UINT32_MAX;
	val = data_pool_get_trcom_trip_b_val();
	ASSERT_EQ(UINT32_MAX, val);

	data_pool_set_trcom_trip_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trcomTripBVal);

	checker = 0;
	for (uint32_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_trcom_trip_b_val(i);
		val = data_pool_get_trcom_trip_b_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripBVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_trcom_trip_b_val(i);
		val = data_pool_get_trcom_trip_b_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripBVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint32_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_trcom_trip_b_val(i);
		val = data_pool_get_trcom_trip_b_val();
		ASSERT_EQ(i, val);

		apival = getTrcomTripBVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/
	data_pool_set_trcom_trip_b_val(0xFFFFFFFEul);
	val = data_pool_get_trcom_trip_b_val();
	ASSERT_EQ(0xFFFFFFFEul, val);

	apival = getTrcomTripBVal();
	ASSERT_EQ(0xFFFFFFFEul, (uint32_t)apival);

	data_pool_set_trcom_trip_b_val(0xFFFFFFFFul);
	val = data_pool_get_trcom_trip_b_val();
	ASSERT_EQ(0xFFFFFFFFul, val);

	apival = getTrcomTripBVal();
	ASSERT_EQ(0xFFFFFFFFul, (uint32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__odo_val)
{
	int ret = -1;
	uint32_t val = 0;
	unsigned long apival = 0;
	uint64_t checker = 0;

	const uint32_t minimam_val = 0x00000000ul;	//ODO Min (0)
	const uint32_t max_val = 0x000f423ful;	// ODO Max (999999)
	const uint32_t out_of_range_start_val = 0x000f4240ul;	//invalid value (1000000~4294967295)
	const uint32_t out_of_range_end_val = 0xFFFFFFFEul;	//invalid value (1000000~4294967295)
	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_trcom_odo_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_trcom_odo_val(UINT32_MAX);
	ASSERT_EQ(UINT32_MAX, g_agl_cluster_data_pool.data.trcomOdoVal);

	val = data_pool_get_trcom_odo_val();
	ASSERT_EQ(UINT32_MAX, val);

	g_agl_cluster_data_pool.data.trcomOdoVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.trcomOdoVal = UINT32_MAX;
	val = data_pool_get_trcom_odo_val();
	ASSERT_EQ(UINT32_MAX, val);

	data_pool_set_trcom_odo_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trcomOdoVal);

	checker = 0;
	for (uint32_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_trcom_odo_val(i);
		val = data_pool_get_trcom_odo_val();
		ASSERT_EQ(i, val);

		apival = getTrcomOdoVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	checker = 0;
	for (uint32_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_trcom_odo_val(i);
		val = data_pool_get_trcom_odo_val();
		ASSERT_EQ(i, val);

		apival = getTrcomOdoVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint32_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_trcom_odo_val(i);
		val = data_pool_get_trcom_odo_val();
		ASSERT_EQ(i, val);

		apival = getTrcomOdoVal();
		ASSERT_EQ(i, (uint32_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT32_MAX);
		checker++;
	}

	/* others
		0xFFFFFFFE ："-" view
		0xFFFFFFFF ：disable
	*/
	data_pool_set_trcom_odo_val(0xFFFFFFFEul);
	val = data_pool_get_trcom_odo_val();
	ASSERT_EQ(0xFFFFFFFEul, val);

	apival = getTrcomOdoVal();
	ASSERT_EQ(0xFFFFFFFEul, (uint32_t)apival);

	data_pool_set_trcom_odo_val(0xFFFFFFFFul);
	val = data_pool_get_trcom_odo_val();
	ASSERT_EQ(0xFFFFFFFFul, val);

	apival = getTrcomOdoVal();
	ASSERT_EQ(0xFFFFFFFFul, (uint32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__unit_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_TRCOM_UNIT_VAL apival = IC_HMI_TRCOM_MILE;
	/*
	 0：IC_HMI_TRCOM_KM
	 1：IC_HMI_TRCOM_MILE
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_trcom_unit_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_trcom_unit_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.trcomUnitVal);

	val = data_pool_get_trcom_unit_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.trcomUnitVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.trcomUnitVal = INT32_MAX;
	val = data_pool_get_trcom_unit_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_trcom_unit_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trcomUnitVal);

	data_pool_set_trcom_unit_val(0);
	val = data_pool_get_trcom_unit_val();
	ASSERT_EQ(0, val);

	apival = getTrcomUnitVal();
	ASSERT_EQ(IC_HMI_TRCOM_KM, (int32_t)apival);

	data_pool_set_trcom_unit_val(1);
	val = data_pool_get_trcom_unit_val();
	ASSERT_EQ(1, val);

	apival = getTrcomUnitVal();
	ASSERT_EQ(IC_HMI_TRCOM_MILE, (int32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__avg_speed_a_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Speed A Min (0)
	const uint16_t max_val = 0x012cul;	// Average Speed A Max (300)
	const uint16_t out_of_range_start_val = 0x012dul;	//invalid value (300~65533)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (300~65533)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_avg_speed_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_avg_speed_a_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.avgSpeedAVal);

	val = data_pool_get_avg_speed_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.avgSpeedAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.avgSpeedAVal = UINT16_MAX;
	val = data_pool_get_avg_speed_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_avg_speed_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.avgSpeedAVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_avg_speed_a_val(i);
		val = data_pool_get_avg_speed_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_avg_speed_a_val(i);
		val = data_pool_get_avg_speed_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_avg_speed_a_val(i);
		val = data_pool_get_avg_speed_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_avg_speed_a_val(0xFFFEul);
	val = data_pool_get_avg_speed_a_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getAvgSpeedAVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_avg_speed_a_val(0xFFFFul);
	val = data_pool_get_avg_speed_a_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getAvgSpeedAVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__avg_speed_b_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Speed B Min (0)
	const uint16_t max_val = 0x012cul;	// Average Speed B Max (300)
	const uint16_t out_of_range_start_val = 0x012dul;	//invalid value (300~65533)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (300~65533)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_avg_speed_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_avg_speed_b_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.avgSpeedBVal);

	val = data_pool_get_avg_speed_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.avgSpeedBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.avgSpeedBVal = UINT16_MAX;
	val = data_pool_get_avg_speed_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_avg_speed_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.avgSpeedBVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_avg_speed_b_val(i);
		val = data_pool_get_avg_speed_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_avg_speed_b_val(i);
		val = data_pool_get_avg_speed_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_avg_speed_b_val(i);
		val = data_pool_get_avg_speed_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgSpeedBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_avg_speed_b_val(0xFFFEul);
	val = data_pool_get_avg_speed_b_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getAvgSpeedBVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_avg_speed_b_val(0xFFFFul);
	val = data_pool_get_avg_speed_b_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getAvgSpeedBVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__hour_a_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Hour A Min (0)
	const uint16_t max_val = 0x03e7ul;	// Hour A Max (999)
	const uint16_t out_of_range_start_val = 0x03e8ul;	//invalid value (1000~65533)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (1000~65533)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_hour_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_hour_a_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.hourAVal);

	val = data_pool_get_hour_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.hourAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.hourAVal = UINT16_MAX;
	val = data_pool_get_hour_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_hour_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.hourAVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_hour_a_val(i);
		val = data_pool_get_hour_a_val();
		ASSERT_EQ(i, val);

		apival = getHourAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_hour_a_val(i);
		val = data_pool_get_hour_a_val();
		ASSERT_EQ(i, val);

		apival = getHourAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_hour_a_val(i);
		val = data_pool_get_hour_a_val();
		ASSERT_EQ(i, val);

		apival = getHourAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_hour_a_val(0xFFFEul);
	val = data_pool_get_hour_a_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getHourAVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_hour_a_val(0xFFFFul);
	val = data_pool_get_hour_a_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getHourAVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__hour_b_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Hour A Min (0)
	const uint16_t max_val = 0x03e7ul;	// Hour A Max (999)
	const uint16_t out_of_range_start_val = 0x03e8ul;	//invalid value (1000~65533)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (1000~65533)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_hour_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_hour_b_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.hourBVal);

	val = data_pool_get_hour_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.hourBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.hourBVal = UINT16_MAX;
	val = data_pool_get_hour_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_hour_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.hourBVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_hour_b_val(i);
		val = data_pool_get_hour_b_val();
		ASSERT_EQ(i, val);

		apival = getHourBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_hour_b_val(i);
		val = data_pool_get_hour_b_val();
		ASSERT_EQ(i, val);

		apival = getHourBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_hour_b_val(i);
		val = data_pool_get_hour_b_val();
		ASSERT_EQ(i, val);

		apival = getHourBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_hour_b_val(0xFFFEul);
	val = data_pool_get_hour_b_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getHourBVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_hour_b_val(0xFFFFul);
	val = data_pool_get_hour_b_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getHourBVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__minute_a_val)
{
	int ret = -1;
	uint8_t val = 0;
	unsigned char apival = 0;
	uint64_t checker = 0;

	const uint8_t minimam_val = 0x00ul;	//Minute A Min (0)
	const uint8_t max_val = 0x3bul;	//Minute A Max (59)
	const uint8_t out_of_range_start_val = 0x3cul;	//invalid value (60~253)
	const uint8_t out_of_range_end_val = 0xfdul;	//invalid value (60~253)
	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_minute_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_minute_a_val(UINT8_MAX);
	ASSERT_EQ(UINT8_MAX, g_agl_cluster_data_pool.data.minuteAVal);

	val = data_pool_get_minute_a_val();
	ASSERT_EQ(UINT8_MAX, val);

	g_agl_cluster_data_pool.data.minuteAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.minuteAVal = UINT8_MAX;
	val = data_pool_get_minute_a_val();
	ASSERT_EQ(UINT8_MAX, val);

	data_pool_set_minute_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.minuteAVal);

	checker = 0;
	for (uint8_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_minute_a_val(i);
		val = data_pool_get_minute_a_val();
		ASSERT_EQ(i, val);

		apival = getMinuteAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	checker = 0;
	for (uint8_t i = out_of_range_start_val; i <= (out_of_range_start_val+4);i++) {
		data_pool_set_minute_a_val(i);
		val = data_pool_get_minute_a_val();
		ASSERT_EQ(i, val);

		apival = getMinuteAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint8_t i = out_of_range_end_val-4; i <= out_of_range_end_val;i++) {
		data_pool_set_minute_a_val(i);
		val = data_pool_get_minute_a_val();
		ASSERT_EQ(i, val);

		apival = getMinuteAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	data_pool_set_minute_a_val(0xFEul);
	val = data_pool_get_minute_a_val();
	ASSERT_EQ(0xFEul, val);

	apival = getMinuteAVal();
	ASSERT_EQ(0xFEul, (uint8_t)apival);

	data_pool_set_minute_a_val(0xFFul);
	val = data_pool_get_minute_a_val();
	ASSERT_EQ(0xFFul, val);

	apival = getMinuteAVal();
	ASSERT_EQ(0xFFul, (uint8_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__minute_b_val)
{
	int ret = -1;
	uint8_t val = 0;
	unsigned char apival = 0;
	uint64_t checker = 0;

	const uint8_t minimam_val = 0x00ul;	//Minute B Min (0)
	const uint8_t max_val = 0x3bul;	//Minute B Max (59)
	const uint8_t out_of_range_start_val = 0x3cul;	//invalid value (60~253)
	const uint8_t out_of_range_end_val = 0xfdul;	//invalid value (60~253)
	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_minute_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_minute_b_val(UINT8_MAX);
	ASSERT_EQ(UINT8_MAX, g_agl_cluster_data_pool.data.minuteBVal);

	val = data_pool_get_minute_b_val();
	ASSERT_EQ(UINT8_MAX, val);

	g_agl_cluster_data_pool.data.minuteBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.minuteBVal = UINT8_MAX;
	val = data_pool_get_minute_b_val();
	ASSERT_EQ(UINT8_MAX, val);

	data_pool_set_minute_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.minuteBVal);

	checker = 0;
	for (uint8_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_minute_b_val(i);
		val = data_pool_get_minute_b_val();
		ASSERT_EQ(i, val);

		apival = getMinuteBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	checker = 0;
	for (uint8_t i = out_of_range_start_val; i <= (out_of_range_start_val+4);i++) {
		data_pool_set_minute_b_val(i);
		val = data_pool_get_minute_b_val();
		ASSERT_EQ(i, val);

		apival = getMinuteBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint8_t i = out_of_range_end_val-4; i <= out_of_range_end_val;i++) {
		data_pool_set_minute_b_val(i);
		val = data_pool_get_minute_b_val();
		ASSERT_EQ(i, val);

		apival = getMinuteBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	data_pool_set_minute_b_val(0xFEul);
	val = data_pool_get_minute_b_val();
	ASSERT_EQ(0xFEul, val);

	apival = getMinuteBVal();
	ASSERT_EQ(0xFEul, (uint8_t)apival);

	data_pool_set_minute_b_val(0xFFul);
	val = data_pool_get_minute_b_val();
	ASSERT_EQ(0xFFul, val);

	apival = getMinuteBVal();
	ASSERT_EQ(0xFFul, (uint8_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__second_a_val)
{
	int ret = -1;
	uint8_t val = 0;
	unsigned char apival = 0;
	uint64_t checker = 0;

	const uint8_t minimam_val = 0x00ul;	//Second A Min (0)
	const uint8_t max_val = 0x3bul;	//Second A Max (59)
	const uint8_t out_of_range_start_val = 0x3cul;	//invalid value (60~253)
	const uint8_t out_of_range_end_val = 0xfdul;	//invalid value (60~253)
	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_second_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_second_a_val(UINT8_MAX);
	ASSERT_EQ(UINT8_MAX, g_agl_cluster_data_pool.data.secondAVal);

	val = data_pool_get_second_a_val();
	ASSERT_EQ(UINT8_MAX, val);

	g_agl_cluster_data_pool.data.secondAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.secondAVal = UINT8_MAX;
	val = data_pool_get_second_a_val();
	ASSERT_EQ(UINT8_MAX, val);

	data_pool_set_second_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.secondAVal);

	checker = 0;
	for (uint8_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_second_a_val(i);
		val = data_pool_get_second_a_val();
		ASSERT_EQ(i, val);

		apival = getSecondAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	checker = 0;
	for (uint8_t i = out_of_range_start_val; i <= (out_of_range_start_val+4);i++) {
		data_pool_set_second_a_val(i);
		val = data_pool_get_second_a_val();
		ASSERT_EQ(i, val);

		apival = getSecondAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint8_t i = out_of_range_end_val-4; i <= out_of_range_end_val;i++) {
		data_pool_set_second_a_val(i);
		val = data_pool_get_second_a_val();
		ASSERT_EQ(i, val);

		apival = getSecondAVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	data_pool_set_second_a_val(0xFEul);
	val = data_pool_get_second_a_val();
	ASSERT_EQ(0xFEul, val);

	apival = getSecondAVal();
	ASSERT_EQ(0xFEul, (uint8_t)apival);

	data_pool_set_second_a_val(0xFFul);
	val = data_pool_get_second_a_val();
	ASSERT_EQ(0xFFul, val);

	apival = getSecondAVal();
	ASSERT_EQ(0xFFul, (uint8_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__second_b_val)
{
	int ret = -1;
	uint8_t val = 0;
	unsigned char apival = 0;
	uint64_t checker = 0;

	const uint8_t minimam_val = 0x00ul;	//Second A Min (0)
	const uint8_t max_val = 0x3bul;	//Second A Max (59)
	const uint8_t out_of_range_start_val = 0x3cul;	//invalid value (60~253)
	const uint8_t out_of_range_end_val = 0xfdul;	//invalid value (60~253)
	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_second_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_second_b_val(UINT8_MAX);
	ASSERT_EQ(UINT8_MAX, g_agl_cluster_data_pool.data.secondBVal);

	val = data_pool_get_second_b_val();
	ASSERT_EQ(UINT8_MAX, val);

	g_agl_cluster_data_pool.data.secondBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.secondBVal = UINT8_MAX;
	val = data_pool_get_second_b_val();
	ASSERT_EQ(UINT8_MAX, val);

	data_pool_set_second_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.secondBVal);

	checker = 0;
	for (uint8_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_second_b_val(i);
		val = data_pool_get_second_b_val();
		ASSERT_EQ(i, val);

		apival = getSecondBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	checker = 0;
	for (uint8_t i = out_of_range_start_val; i <= (out_of_range_start_val+4);i++) {
		data_pool_set_second_b_val(i);
		val = data_pool_get_second_b_val();
		ASSERT_EQ(i, val);

		apival = getSecondBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint8_t i = out_of_range_end_val-4; i <= out_of_range_end_val;i++) {
		data_pool_set_second_b_val(i);
		val = data_pool_get_second_b_val();
		ASSERT_EQ(i, val);

		apival = getSecondBVal();
		ASSERT_EQ(i, (uint8_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT8_MAX);
		checker++;
	}

	/* others
		0xFE ："-" view
		0xFF ：disable
	*/
	data_pool_set_second_b_val(0xFEul);
	val = data_pool_get_second_b_val();
	ASSERT_EQ(0xFEul, val);

	apival = getSecondBVal();
	ASSERT_EQ(0xFEul, (uint8_t)apival);

	data_pool_set_second_b_val(0xFFul);
	val = data_pool_get_second_b_val();
	ASSERT_EQ(0xFFul, val);

	apival = getSecondBVal();
	ASSERT_EQ(0xFFul, (uint8_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__o_temp_val)
{
	int ret = -1;
	int16_t val = 0;
	signed short apival = 0;
	uint64_t checker = 0;

	const int16_t minimam_val = -40;	//Outside Temp Min (-40)
	const int16_t max_val = 131;	//Outside Temp Max (131)
	const int16_t out_of_range_start_val = -32768;	//invalid value (-32768 ~ -41)
	const int16_t out_of_range_end_val = -41;	//invalid value (-32767 ~ -41)
	const int16_t out_of_range_start_val2 = 132;	//invalid value (132 ~ 32765)
	const int16_t out_of_range_end_val2 = 32765;	//invalid value (132 ~ 32765)
	/* others
		0x7FFE ："-" view
		0x7FFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_o_temp_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_o_temp_val(INT16_MAX);
	ASSERT_EQ(INT16_MAX, g_agl_cluster_data_pool.data.oTempVal);

	val = data_pool_get_o_temp_val();
	ASSERT_EQ(INT16_MAX, val);

	g_agl_cluster_data_pool.data.oTempVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.oTempVal = INT16_MAX;
	val = data_pool_get_o_temp_val();
	ASSERT_EQ(INT16_MAX, val);

	data_pool_set_o_temp_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.oTempVal);

	checker = 0;
	for (int16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_o_temp_val(i);
		val = data_pool_get_o_temp_val();
		ASSERT_EQ(i, val);

		apival = getOTempVal();
		ASSERT_EQ(i, (int16_t)apival);

		ASSERT_LE(checker, (uint64_t)INT16_MAX);
		checker++;
	}

	checker = 0;
	for (int16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_o_temp_val(i);
		val = data_pool_get_o_temp_val();
		ASSERT_EQ(i, val);

		apival = getOTempVal();
		ASSERT_EQ(i, (int16_t)apival);

		ASSERT_LE(checker, (uint64_t)INT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (int16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_o_temp_val(i);
		val = data_pool_get_o_temp_val();
		ASSERT_EQ(i, val);

		apival = getOTempVal();
		ASSERT_EQ(i, (int16_t)apival);

		ASSERT_LE(checker, (uint64_t)INT16_MAX);
		checker++;
	}

	checker = 0;
	for (int16_t i = out_of_range_start_val2; i <= (out_of_range_start_val2+100);i++) {
		data_pool_set_o_temp_val(i);
		val = data_pool_get_o_temp_val();
		ASSERT_EQ(i, val);

		apival = getOTempVal();
		ASSERT_EQ(i, (int16_t)apival);

		ASSERT_LE(checker, (uint64_t)INT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (int16_t i = out_of_range_end_val2-100; i <= out_of_range_end_val2;i++) {
		data_pool_set_o_temp_val(i);
		val = data_pool_get_o_temp_val();
		ASSERT_EQ(i, val);

		apival = getOTempVal();
		ASSERT_EQ(i, (int16_t)apival);

		ASSERT_LE(checker, (uint64_t)INT16_MAX);
		checker++;
	}

	/* others
		0x7FFE ："-" view
		0x7FFF ：disable
	*/
	data_pool_set_o_temp_val(0x7FFE);
	val = data_pool_get_o_temp_val();
	ASSERT_EQ(0x7FFE, val);

	apival = getOTempVal();
	ASSERT_EQ(0x7FFE, (int16_t)apival);

	data_pool_set_o_temp_val(0x7FFF);
	val = data_pool_get_o_temp_val();
	ASSERT_EQ(0x7FFF, val);

	apival = getOTempVal();
	ASSERT_EQ(0x7FFF, (int16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__o_temp_unit_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_OTEMP_UNIT_VAL apival = IC_HMI_OTEMP_UNIT_K;
	/*
	 0：IC_HMI_OTEMP_UNIT_C
	 1：IC_HMI_OTEMP_UNIT_K
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_o_temp_unit_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_o_temp_unit_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.oTempUnitVal);

	val = data_pool_get_o_temp_unit_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.oTempUnitVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.oTempUnitVal = INT32_MAX;
	val = data_pool_get_o_temp_unit_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_o_temp_unit_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.trcomUnitVal);

	data_pool_set_o_temp_unit_val(0);
	val = data_pool_get_o_temp_unit_val();
	ASSERT_EQ(0, val);

	apival = getOTempUnitVal();
	ASSERT_EQ(IC_HMI_OTEMP_UNIT_C, (int32_t)apival);

	data_pool_set_o_temp_unit_val(1);
	val = data_pool_get_o_temp_unit_val();
	ASSERT_EQ(1, val);

	apival = getOTempUnitVal();
	ASSERT_EQ(IC_HMI_OTEMP_UNIT_K, (int32_t)apival);

}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__cru_range_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Cruise Range Min (0)
	const uint16_t max_val = 0x064aul;	//Cruise Range Max (1610)
	const uint16_t out_of_range_start_val = 0x064bul;	//invalid value (1611~65533)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (1611~65533)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_cru_range_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_cru_range_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.cruRangeVal);

	val = data_pool_get_cru_range_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.cruRangeVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.cruRangeVal = UINT16_MAX;
	val = data_pool_get_cru_range_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_cru_range_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.cruRangeVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_cru_range_val(i);
		val = data_pool_get_cru_range_val();
		ASSERT_EQ(i, val);

		apival = getCruRangeVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_cru_range_val(i);
		val = data_pool_get_cru_range_val();
		ASSERT_EQ(i, val);

		apival = getCruRangeVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_cru_range_val(i);
		val = data_pool_get_cru_range_val();
		ASSERT_EQ(i, val);

		apival = getCruRangeVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_cru_range_val(0xFFFEul);
	val = data_pool_get_cru_range_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getCruRangeVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_cru_range_val(0xFFFFul);
	val = data_pool_get_cru_range_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getCruRangeVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__avg_fuel_a_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Fuel TripA Min (0.0)
	const uint16_t max_val = 0x07cful;	//Average Fuel TripA Max (199.9)
	const uint16_t out_of_range_start_val = 0x07d0ul;	//invalid value (200.0~6553.3)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (200.0~6553.3)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_avg_fuel_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_avg_fuel_a_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.avgFuelAVal);

	val = data_pool_get_avg_fuel_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.avgFuelAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.avgFuelAVal = UINT16_MAX;
	val = data_pool_get_avg_fuel_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_avg_fuel_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.avgFuelAVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_avg_fuel_a_val(i);
		val = data_pool_get_avg_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_avg_fuel_a_val(i);
		val = data_pool_get_avg_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_avg_fuel_a_val(i);
		val = data_pool_get_avg_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_avg_fuel_a_val(0xFFFEul);
	val = data_pool_get_avg_fuel_a_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getAvgFuelAVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_avg_fuel_a_val(0xFFFFul);
	val = data_pool_get_avg_fuel_a_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getAvgFuelAVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__avg_fuel_b_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Fuel TripB Min (0.0)
	const uint16_t max_val = 0x07cful;	//Average Fuel TripB Max (199.9)
	const uint16_t out_of_range_start_val = 0x07d0ul;	//invalid value (200.0~6553.3)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (200.0~6553.3)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_avg_fuel_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_avg_fuel_b_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.avgFuelBVal);

	val = data_pool_get_avg_fuel_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.avgFuelBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.avgFuelBVal = UINT16_MAX;
	val = data_pool_get_avg_fuel_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_avg_fuel_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.avgFuelBVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_avg_fuel_b_val(i);
		val = data_pool_get_avg_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_avg_fuel_b_val(i);
		val = data_pool_get_avg_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_avg_fuel_b_val(i);
		val = data_pool_get_avg_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getAvgFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_avg_fuel_b_val(0xFFFEul);
	val = data_pool_get_avg_fuel_b_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getAvgFuelBVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_avg_fuel_b_val(0xFFFFul);
	val = data_pool_get_avg_fuel_b_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getAvgFuelBVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__ins_fuel_a_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Fuel TripA Min (0.0)
	const uint16_t max_val = 0x07cful;	//Average Fuel TripA Max (199.9)
	const uint16_t out_of_range_start_val = 0x07d0ul;	//invalid value (200.0~6553.3)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (200.0~6553.3)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_ins_fuel_a_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_ins_fuel_a_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.insFuelAVal);

	val = data_pool_get_ins_fuel_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.insFuelAVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.insFuelAVal = UINT16_MAX;
	val = data_pool_get_ins_fuel_a_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_ins_fuel_a_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.insFuelAVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_ins_fuel_a_val(i);
		val = data_pool_get_ins_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_ins_fuel_a_val(i);
		val = data_pool_get_ins_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_ins_fuel_a_val(i);
		val = data_pool_get_ins_fuel_a_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelAVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_ins_fuel_a_val(0xFFFEul);
	val = data_pool_get_ins_fuel_a_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getInsFuelAVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_ins_fuel_a_val(0xFFFFul);
	val = data_pool_get_ins_fuel_a_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getInsFuelAVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__ins_fuel_b_val)
{
	int ret = -1;
	uint16_t val = 0;
	unsigned short apival = 0;
	uint64_t checker = 0;

	const uint16_t minimam_val = 0x0000ul;	//Average Fuel TripA Min (0.0)
	const uint16_t max_val = 0x07cful;	//Average Fuel TripA Max (199.9)
	const uint16_t out_of_range_start_val = 0x07d0ul;	//invalid value (200.0~6553.3)
	const uint16_t out_of_range_end_val = 0xfffdul;	//invalid value (200.0~6553.3)
	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_ins_fuel_b_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_ins_fuel_b_val(UINT16_MAX);
	ASSERT_EQ(UINT16_MAX, g_agl_cluster_data_pool.data.insFuelBVal);

	val = data_pool_get_ins_fuel_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	g_agl_cluster_data_pool.data.insFuelBVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.insFuelBVal = UINT16_MAX;
	val = data_pool_get_ins_fuel_b_val();
	ASSERT_EQ(UINT16_MAX, val);

	data_pool_set_ins_fuel_b_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.insFuelBVal);

	checker = 0;
	for (uint16_t i = minimam_val; i <= max_val;i++) {
		data_pool_set_ins_fuel_b_val(i);
		val = data_pool_get_ins_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	checker = 0;
	for (uint16_t i = out_of_range_start_val; i <= (out_of_range_start_val+100);i++) {
		data_pool_set_ins_fuel_b_val(i);
		val = data_pool_get_ins_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}
	
	checker = 0;
	for (uint16_t i = out_of_range_end_val-100; i <= out_of_range_end_val;i++) {
		data_pool_set_ins_fuel_b_val(i);
		val = data_pool_get_ins_fuel_b_val();
		ASSERT_EQ(i, val);

		apival = getInsFuelBVal();
		ASSERT_EQ(i, (uint16_t)apival);

		ASSERT_LE(checker, (uint64_t)UINT16_MAX);
		checker++;
	}

	/* others
		0xFFFE ："-" view
		0xFFFF ：disable
	*/
	data_pool_set_ins_fuel_b_val(0xFFFEul);
	val = data_pool_get_ins_fuel_b_val();
	ASSERT_EQ(0xFFFEul, val);

	apival = getInsFuelBVal();
	ASSERT_EQ(0xFFFEul, (uint16_t)apival);

	data_pool_set_ins_fuel_b_val(0xFFFFul);
	val = data_pool_get_ins_fuel_b_val();
	ASSERT_EQ(0xFFFFul, val);

	apival = getInsFuelBVal();
	ASSERT_EQ(0xFFFFul, (uint16_t)apival);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(data_pool_test_set_get_trip, test_data_pool_test_set_get_trcom__fuel_economy_uit_val)
{
	int ret = -1;
	int32_t val = 0;
	IC_HMI_FUEL_ECONOMY_UNIT_VAL apival = IC_HMI_FUEL_KWH_100KM;
	/*
	 0：IC_HMI_FUEL_KM_L
	 1：IC_HMI_FUEL_MPG_US
	 2：IC_HMI_FUEL_MPG_IG
	 3：IC_HMI_FUEL_L_100KM
	 4：IC_HMI_FUEL_MILE_KWH
	 5：IC_HMI_FUEL_KM_KWH
	 6：IC_HMI_FUEL_MILE_KG
	 7：IC_HMI_FUEL_KM_KG
	 8：IC_HMI_FUEL_KWH_100KM
	*/

	memset(&g_agl_cluster_data_pool.data,0,sizeof(g_agl_cluster_data_pool.data));

	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(0, val);
	
	data_pool_set_fuel_economy_uit_val(INT32_MAX);
	ASSERT_EQ(INT32_MAX, g_agl_cluster_data_pool.data.fuelEconomyUnitVal);

	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(INT32_MAX, val);

	g_agl_cluster_data_pool.data.fuelEconomyUnitVal = 0;
	ret = memcmp(&g_agl_cluster_data_pool.data, &zerodata, sizeof(zerodata));
	ASSERT_EQ(0, ret);

	g_agl_cluster_data_pool.data.fuelEconomyUnitVal = INT32_MAX;
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(INT32_MAX, val);

	data_pool_set_fuel_economy_uit_val(0);
	ASSERT_EQ(0, g_agl_cluster_data_pool.data.fuelEconomyUnitVal);

	data_pool_set_fuel_economy_uit_val(0);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(0, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_KM_L, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(1);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(1, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_MPG_US, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(2);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(2, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_MPG_IG, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(3);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(3, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_L_100KM, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(4);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(4, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_MILE_KWH, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(5);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(5, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_KM_KWH, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(6);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(6, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_MILE_KG, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(7);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(7, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_KM_KG, (int32_t)apival);

	data_pool_set_fuel_economy_uit_val(8);
	val = data_pool_get_fuel_economy_uit_val();
	ASSERT_EQ(8, val);

	apival = getFuelEconomyUnitVal();
	ASSERT_EQ(IC_HMI_FUEL_KWH_100KM, (int32_t)apival);
}
