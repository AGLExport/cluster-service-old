/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service.c
 * @brief	data service provider
 */
#include "cluster_api.h"
#include "data-pool-static-configurator.h"
#include "data-pool.h"

#include <pthread.h>
#include <string.h>

/** data pool client data */
struct s_agl_cluster_data_pool {
	pthread_mutex_t data_pool_lock;
	struct S_AGLCLUSTER_SERVICE_DATA_V1 data;
};

static struct s_agl_cluster_data_pool g_agl_cluster_data_pool = {
.data_pool_lock = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP,
};

/**
 *  ====== Data Management ================================
 */
/**
 * Set a data pool data by full size v1 data.
 *
 * @param [in]	data	Memory for set data pool full size v1 data
 * @return int	0	success
 *				-1	fail(Can't lock data pool lock)
 */
int data_pool_set_v1(struct S_AGLCLUSTER_SERVICE_DATA_V1 *data)
{
	int ret = -1;
	
	if (data_pool_lock() == true)
	{
		memcpy(&g_agl_cluster_data_pool.data, data, sizeof(g_agl_cluster_data_pool.data));
		
		(void)data_pool_unlock();

		ret = 0;
	}
	
	return ret;
}
/**
 * Get a data pool data.by full size v1 data.
 *
 * @param [in]	data	Memory to get data pool full size v1 data
 * @return int	0	success
 *				-1	fail(Can't lock data pool lock)
 */
int data_pool_get_v1(struct S_AGLCLUSTER_SERVICE_DATA_V1 *data)
{
	int ret = -1;
	
	if (data_pool_lock() == true)
	{
		memcpy(data , &g_agl_cluster_data_pool.data, sizeof(struct S_AGLCLUSTER_SERVICE_DATA_V1));
		
		(void)data_pool_unlock();

		ret = 0;
	}
	
	return ret;
}
/**
 * Data pool lock
 *
 * @return bool	true Success to lock
 *				false Fail to lock
 */
bool data_pool_lock(void)
{
	int ret = -1;
	bool result = true;
	ret = pthread_mutex_lock(&g_agl_cluster_data_pool.data_pool_lock);
	if (ret < 0)
		result = false;
	
	return result;
}

/**
 * Data pool unlock
 *
 * @return bool	true Success to lock
 *				false Fail to lock
 */
bool data_pool_unlock(void)
{
	int ret = -1;
	bool result = true;
	ret = pthread_mutex_unlock(&g_agl_cluster_data_pool.data_pool_lock);
	if (ret < 0)
		result = false;
	
	return result;
}


/**
 *  ====== Telltale =======================================
 */
/**
 * Data pool setter for Turn R
 *
 * @param [in]	val		ON/OFF for Turn R Telltale
 * @return void
 */
void data_pool_set_turn_r(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.turnR = val;
}
/**
 * Data pool getter for Turn R
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_turn_r(void)
{
	return g_agl_cluster_data_pool.data.turnR;
}

/**
 * Data pool setter for Turn L
 *
 * @param [in]	val		ON/OFF for Turn L Telltale
 * @return void
 */
void data_pool_set_turn_l(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.turnL = val;
}
/**
 * Data pool getter for Turn L
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_turn_l(void)
{
	return g_agl_cluster_data_pool.data.turnL;
}

/**
 * Data pool setter for Brake
 *
 * @param [in]	val		ON/OFF for Brake Telltale
 * @return void
 */
void data_pool_set_brake(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.brake = val;
}
/**
 * Data pool getter for Brake
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_brake(void)
{
	return g_agl_cluster_data_pool.data.brake;
}

/**
 * Data pool setter for Seatbelt
 *
 * @param [in]	val		ON/OFF for Seatbelt Telltale
 * @return void
 */
void data_pool_set_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.seatbelt = val;
}
/**
 * Data pool getter for Seatbelt
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.seatbelt;
}

/**
 * Data pool setter for Seatbelt at Front Right
 *
 * @param [in]	val		ON/OFF for Seatbelt at Front Right Telltale
 * @return void
 */
void data_pool_set_front_right_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontRightSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Front Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_right_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.frontRightSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Front Center
 *
 * @param [in]	val		ON/OFF for Seatbelt at Front Center Telltale
 * @return void
 */
void data_pool_set_front_center_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontCenterSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Front Center
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_center_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.frontCenterSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Front Left
 *
 * @param [in]	val		ON/OFF for Seatbelt at Front Left Telltale
 * @return void
 */
void data_pool_set_front_left_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontLeftSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Front Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_left_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.frontLeftSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid1 Right
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid1 Right Telltale
 * @return void
 */
void data_pool_set_mid1_right_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid1RightSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid1 Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid1_right_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid1RightSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid1 Center
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid1 Center Telltale
 * @return void
 */
void data_pool_set_mid1_center_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid1CenterSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid1 Center
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid1_center_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid1CenterSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid1 Left
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid1 Left Telltale
 * @return void
 */
void data_pool_set_mid1_left_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid1LeftSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid1 Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid1_left_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid1LeftSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid2 Right
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid2 Right Telltale
 * @return void
 */
void data_pool_set_mid2_right_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid2RightSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid2 Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid2_right_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid2RightSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid2 Center
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid2 Center Telltale
 * @return void
 */
void data_pool_set_mid2_center_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid2CenterSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid2 Center
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid2_center_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid2CenterSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Mid2 Left
 *
 * @param [in]	val		ON/OFF for Seatbelt at Mid2 Left Telltale
 * @return void
 */
void data_pool_set_mid2_left_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.mid2LeftSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Mid2 Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_mid2_left_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.mid2LeftSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Rear Right
 *
 * @param [in]	val		ON/OFF for Seatbelt at Rear Right Telltale
 * @return void
 */
void data_pool_set_rear_right_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.rearRightSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Rear Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_rear_right_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.rearRightSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Rear Center
 *
 * @param [in]	val		ON/OFF for Seatbelt at Rear Center Telltale
 * @return void
 */
void data_pool_set_rear_center_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.rearCenterSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Rear Center
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_rear_center_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.rearCenterSeatbelt;
}

/**
 * Data pool setter for Seatbelt at Rear Left
 *
 * @param [in]	val		ON/OFF for Seatbelt at Rear Left Telltale
 * @return void
 */
void data_pool_set_rear_left_seatbelt(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.rearLeftSeatbelt = val;
}
/**
 * Data pool getter for Seatbelt at Rear Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_rear_left_seatbelt(void)
{
	return g_agl_cluster_data_pool.data.rearLeftSeatbelt;
}

/**
 * Data pool setter for High Beam
 *
 * @param [in]	val		ON/OFF for High Beam Telltale
 * @return void
 */
void data_pool_set_high_beam(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.highbeam = val;
}
/**
 * Data pool getter for High Beam
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_high_beam(void)
{
	return g_agl_cluster_data_pool.data.highbeam;
}

/**
 * Data pool setter for Door
 *
 * @param [in]	val		ON/OFF for Door Telltale
 * @return void
 */
void data_pool_set_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.door = val;
}
/**
 * Data pool getter for Door
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_door(void)
{
	return g_agl_cluster_data_pool.data.door;
}

/**
 * Data pool setter for Door at Front Right
 *
 * @param [in]	val		ON/OFF for Door at Front Right Telltale
 * @return void
 */
void data_pool_set_front_right_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontRightDoor = val;
}
/**
 * Data pool getter for Door at Front Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_right_door(void)
{
	return g_agl_cluster_data_pool.data.frontRightDoor;
}

/**
 * Data pool setter for Door at Front Left
 *
 * @param [in]	val		ON/OFF for Door at Front Left Telltale
 * @return void
 */
void data_pool_set_front_left_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontLeftDoor = val;
}
/**
 * Data pool getter for Door at Front Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_left_door(void)
{
	return g_agl_cluster_data_pool.data.frontLeftDoor;
}

/**
 * Data pool setter for Door at Rear Right
 *
 * @param [in]	val		ON/OFF for Door at Rear Right Telltale
 * @return void
 */
void data_pool_set_rear_right_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.rearRightDoor = val;
}
/**
 * Data pool getter for Door at Rear Right
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_rear_right_door(void)
{
	return g_agl_cluster_data_pool.data.rearRightDoor;
}

/**
 * Data pool setter for Door at Rear Left
 *
 * @param [in]	val		ON/OFF for Door at Rear Left Telltale
 * @return void
 */
void data_pool_set_rear_left_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.rearLeftDoor = val;
}
/**
 * Data pool getter for Door at Rear Left
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_rear_left_door(void)
{
	return g_agl_cluster_data_pool.data.rearLeftDoor;
}

/**
 * Data pool setter for Trunk Door
 *
 * @param [in]	val		ON/OFF for Trunk Door Telltale
 * @return void
 */
void data_pool_set_trunk_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.trunkDoor = val;
}
/**
 * Data pool getter for Trunk Door
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_trunk_door(void)
{
	return g_agl_cluster_data_pool.data.trunkDoor;
}

/**
 * Data pool setter for Hood Door
 *
 * @param [in]	val		ON/OFF for Hood Door Telltale
 * @return void
 */
void data_pool_set_hood_door(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.hoodDoor = val;
}
/**
 * Data pool getter for Hood Door
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_hood_door(void)
{
	return g_agl_cluster_data_pool.data.hoodDoor;
}

/**
 * Data pool setter for Eps
 *
 * @param [in]	val		ON/OFF for Eps Telltale
 * @return void
 */
void data_pool_set_eps(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.eps = val;
}
/**
 * Data pool getter for Eps
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_eps(void)
{
	return g_agl_cluster_data_pool.data.eps;
}

/**
 * Data pool setter for Srs Airbag
 *
 * @param [in]	val		ON/OFF for Srs Airbag Telltale
 * @return void
 */
void data_pool_set_srs_airbag(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.srsAirbag = val;
}
/**
 * Data pool getter for Srs Airbag
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_srs_airbag(void)
{
	return g_agl_cluster_data_pool.data.srsAirbag;
}

/**
 * Data pool setter for ABS
 *
 * @param [in]	val		ON/OFF for ABS Telltale
 * @return void
 */
void data_pool_set_abs(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.abs = val;
}
/**
 * Data pool getter for ABS
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_abs(void)
{
	return g_agl_cluster_data_pool.data.abs;
}

/**
 * Data pool setter for Low Battery
 *
 * @param [in]	val		ON/OFF for Low Battery Telltale
 * @return void
 */
void data_pool_set_low_battery(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.lowBattery = val;
}
/**
 * Data pool getter for Low Battery
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_low_battery(void)
{
	return g_agl_cluster_data_pool.data.lowBattery;
}

/**
 * Data pool setter for Oil Press
 *
 * @param [in]	val		ON/OFF for Oil Press Telltale
 * @return void
 */
void data_pool_set_oil_press(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.oilPress = val;
}
/**
 * Data pool getter for Oil Press
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_oil_press(void)
{
	return g_agl_cluster_data_pool.data.oilPress;
}

/**
 * Data pool setter for Engine
 *
 * @param [in]	val		ON/OFF for Engine Telltale
 * @return void
 */
void data_pool_set_engine(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.engine = val;
}
/**
 * Data pool getter for Engine
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_engine(void)
{
	return g_agl_cluster_data_pool.data.engine;
}

/**
 * Data pool setter for Fuel
 *
 * @param [in]	val		ON/OFF for Fuel Telltale
 * @return void
 */
void data_pool_set_fuel(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.fuel = val;
}
/**
 * Data pool getter for Fuel
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_fuel(void)
{
	return g_agl_cluster_data_pool.data.fuel;
}

/**
 * Data pool setter for Immobi
 *
 * @param [in]	val		ON/OFF for Immobi Telltale
 * @return void
 */
void data_pool_set_immobi(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.immobi = val;
}
/**
 * Data pool getter for Immobi
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_immobi(void)
{
	return g_agl_cluster_data_pool.data.immobi;
}

/**
 * Data pool setter for TM Fail
 *
 * @param [in]	val		ON/OFF for TM Fail Telltale
 * @return void
 */
void data_pool_set_tm_fail(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.tmFail = val;
}
/**
 * Data pool getter for TM Fail
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_tm_fail(void)
{
	return g_agl_cluster_data_pool.data.tmFail;
}

/**
 * Data pool setter for Esp Act
 *
 * @param [in]	val		ON/OFF for Esp Act Telltale
 * @return void
 */
void data_pool_set_esp_act(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.espAct = val;
}
/**
 * Data pool getter for Esp Act
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_esp_act(void)
{
	return g_agl_cluster_data_pool.data.espAct;
}

/**
 * Data pool setter for Esp Off
 *
 * @param [in]	val		ON/OFF for Esp Off Telltale
 * @return void
 */
void data_pool_set_esp_off(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.espOff = val;
}
/**
 * Data pool getter for Esp Off
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_esp_off(void)
{
	return g_agl_cluster_data_pool.data.espOff;
}

/**
 * Data pool setter for Adapting Lighting
 *
 * @param [in]	val		ON/OFF for Adapting Lighting Telltale
 * @return void
 */
void data_pool_set_adapting_lighting(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.adaptingLighting = val;
}
/**
 * Data pool getter for Adapting Lighting
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_adapting_lighting(void)
{
	return g_agl_cluster_data_pool.data.adaptingLighting;
}

/**
 * Data pool setter for Auto Stop
 *
 * @param [in]	val		ON/OFF for Auto Stop Telltale
 * @return void
 */
void data_pool_set_auto_stop(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.autoStop = val;
}
/**
 * Data pool getter for Auto Stop
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_auto_stop(void)
{
	return g_agl_cluster_data_pool.data.autoStop;
}

/**
 * Data pool setter for Auto Stop Fail
 *
 * @param [in]	val		ON/OFF for Auto Stop Fail Telltale
 * @return void
 */
void data_pool_set_auto_stop_fail(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.autoStopFail = val;
}
/**
 * Data pool getter for Auto Stop Fail
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_auto_stop_fail(void)
{
	return g_agl_cluster_data_pool.data.autoStopFail;
}

/**
 * Data pool setter for Parking Lights
 *
 * @param [in]	val		ON/OFF for Parking Lights Telltale
 * @return void
 */
void data_pool_set_parking_lights(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.parkingLights = val;
}
/**
 * Data pool getter for Parking Lights
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_parking_lights(void)
{
	return g_agl_cluster_data_pool.data.parkingLights;
}

/**
 * Data pool setter for Front Fog
 *
 * @param [in]	val		ON/OFF for Front Fog Telltale
 * @return void
 */
void data_pool_set_front_fog(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.frontFog = val;
}
/**
 * Data pool getter for Front Fog
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_front_fog(void)
{
	return g_agl_cluster_data_pool.data.frontFog;
}

/**
 * Data pool setter for Exterior Light Fault
 *
 * @param [in]	val		ON/OFF for Exterior Light Fault Telltale
 * @return void
 */
void data_pool_set_exterior_light_fault(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.exteriorLightFault = val;
}
/**
 * Data pool getter for Exterior Light Fault
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_exterior_light_fault(void)
{
	return g_agl_cluster_data_pool.data.exteriorLightFault;
}

/**
 * Data pool setter for Acc Fail
 *
 * @param [in]	val		ON/OFF for Acc Fail Telltale
 * @return void
 */
void data_pool_set_acc_fail(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.accFail = val;
}
/**
 * Data pool getter for Acc Fail
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_acc_fail(void)
{
	return g_agl_cluster_data_pool.data.accFail;
}

/**
 * Data pool setter for Ldw Off
 *
 * @param [in]	val		ON/OFF for Ldw Off Telltale
 * @return void
 */
void data_pool_set_ldw_off(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.ldwOff = val;
}
/**
 * Data pool getter for Ldw Off
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_ldw_off(void)
{
	return g_agl_cluster_data_pool.data.ldwOff;
}

/**
 * Data pool setter for Hill Descent
 *
 * @param [in]	val		ON/OFF for Hill Descent Telltale
 * @return void
 */
void data_pool_set_hill_descent(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.hillDescent = val;
}
/**
 * Data pool getter for Hill Descent
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_hill_descent(void)
{
	return g_agl_cluster_data_pool.data.hillDescent;
}

/**
 * Data pool setter for Auto Hi Beam Green
 *
 * @param [in]	val		ON/OFF for Auto Hi Beam Green Telltale
 * @return void
 */
void data_pool_set_auto_hi_beam_green(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.autoHiBeamGreen = val;
}
/**
 * Data pool getter for Auto Hi Beam Green
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_auto_hi_beam_green(void)
{
	return g_agl_cluster_data_pool.data.autoHiBeamGreen;
}

/**
 * Data pool setter for Auto Hi Beam Amber
 *
 * @param [in]	val		ON/OFF for Auto Hi Beam Amber Telltale
 * @return void
 */
void data_pool_set_auto_hi_beam_amber(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.autoHiBeamAmber = val;
}
/**
 * Data pool getter for Auto Hi Beam Amber
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_auto_hi_beam_amber(void)
{
	return g_agl_cluster_data_pool.data.autoHiBeamAmber;
}

/**
 * Data pool setter for Sports Mode
 *
 * @param [in]	val		ON/OFF for Sports Mode Telltale
 * @return void
 */
void data_pool_set_sports_mode(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.sportsMode = val;
}
/**
 * Data pool getter for Sports Mode
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_sports_mode(void)
{
	return g_agl_cluster_data_pool.data.sportsMode;
}

/**
 * Data pool setter for Ldw Operate
 *
 * @param [in]	val		ON/OFF for Ldw Operate Telltale
 * @return void
 */
void data_pool_set_ldw_operate(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.ldwOperate = val;
}
/**
 * Data pool getter for Ldw Operate
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_ldw_operate(void)
{
	return g_agl_cluster_data_pool.data.ldwOperate;
}

/**
 * Data pool setter for General Warn
 *
 * @param [in]	val		ON/OFF for General Warn Telltale
 * @return void
 */
void data_pool_set_general_warn(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.generalWarn = val;
}
/**
 * Data pool getter for General Warn
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_general_warn(void)
{
	return g_agl_cluster_data_pool.data.generalWarn;
}

/**
 * Data pool setter for Driver Power Mode
 *
 * @param [in]	val		ON/OFF for Driver Power Mode Telltale
 * @return void
 */
void data_pool_set_driving_power_mode(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.drivingPowerMode = val;
}
/**
 * Data pool getter for Driver Power Mode
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_driving_power_mode(void)
{
	return g_agl_cluster_data_pool.data.drivingPowerMode;
}

/**
 * Data pool setter for Hot Temp
 *
 * @param [in]	val		ON/OFF for Hot Temp Telltale
 * @return void
 */
void data_pool_set_hot_temp(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.hotTemp = val;
}
/**
 * Data pool getter for Hot Temp
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_hot_temp(void)
{
	return g_agl_cluster_data_pool.data.hotTemp;
}

/**
 * Data pool setter for Low Temp
 *
 * @param [in]	val		ON/OFF for Low Temp Telltale
 * @return void
 */
void data_pool_set_low_temp(IC_HMI_ON_OFF val)
{
	g_agl_cluster_data_pool.data.lowTemp = val;
}
/**
 * Data pool getter for Low Temp
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 *							IC_HMI_ON	off
 */
IC_HMI_ON_OFF data_pool_get_low_temp(void)
{
	return g_agl_cluster_data_pool.data.lowTemp;
}

/**
 *  ===== Trip Computer =============================================
 */
/**
 * Data pool setter for Trcom TripA Val
 *
 * @param [in]	val		Value for Trcom TripA 
 * @return void
 */
void data_pool_set_trcom_trip_a_val(uint32_t val)
{
	g_agl_cluster_data_pool.data.trcomTripAVal = val;
}
/**
 * Data pool getter for Trcom TripA Val
 *
 * @param [in]	void
 * @return uint32_t	Value for Trcom TripA
 */
uint32_t data_pool_get_trcom_trip_a_val(void)
{
	return g_agl_cluster_data_pool.data.trcomTripAVal;
}

/**
 * Data pool setter for Trcom TripB Val
 *
 * @param [in]	val		Value for Trcom TripB
 * @return void
 */
void data_pool_set_trcom_trip_b_val(uint32_t val)
{
	g_agl_cluster_data_pool.data.trcomTripBVal = val;
}
/**
 * Data pool getter for Trcom TripB Val
 *
 * @param [in]	void
 * @return uint32_t	Value for Trcom TripB
 */
uint32_t data_pool_get_trcom_trip_b_val(void)
{
	return g_agl_cluster_data_pool.data.trcomTripBVal;
}

/**
 * Data pool setter for Trcom Odo Val
 *
 * @param [in]	val		Value for Trcom Odo
 * @return void
 */
void data_pool_set_trcom_odo_val(uint32_t val)
{
	g_agl_cluster_data_pool.data.trcomOdoVal = val;
}
/**
 * Data pool getter for Trcom Odo Val
 *
 * @param [in]	void
 * @return uint32_t	Value for Trcom Odo
 */
uint32_t data_pool_get_trcom_odo_val(void)
{
	return g_agl_cluster_data_pool.data.trcomOdoVal;
}

/**
 * Data pool setter for Trcom Unit Val
 *
 * @param [in]	val		Value for Trcom Unit
 * @return void
 */
void data_pool_set_trcom_unit_val(int32_t val)
{
	g_agl_cluster_data_pool.data.trcomUnitVal = val;
}
/**
 * Data pool getter for Trcom Unit Val
 *
 * @param [in]	void
 * @return int32_t	Value for Trcom Unit
 */
int32_t data_pool_get_trcom_unit_val(void)
{
	return g_agl_cluster_data_pool.data.trcomUnitVal;
}

/**
 * Data pool setter for Avg SpeedA Val
 *
 * @param [in]	val		Value for Avg SpeedA
 * @return void
 */
void data_pool_set_avg_speed_a_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.avgSpeedAVal = val;
}
/**
 * Data pool getter for Avg SpeedA Val
 *
 * @param [in]	void
 * @return uint16_t	Value for Avg SpeedA
 */
uint16_t data_pool_get_avg_speed_a_val(void)
{
	return g_agl_cluster_data_pool.data.avgSpeedAVal;
}

/**
 * Data pool setter for Avg SpeedB Val
 *
 * @param [in]	val		ON/OFF for Avg SpeedB Val
 * @return void
 */
void data_pool_set_avg_speed_b_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.avgSpeedBVal = val;
}
/**
 * Data pool getter for Avg SpeedB Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_avg_speed_b_val(void)
{
	return g_agl_cluster_data_pool.data.avgSpeedBVal;
}

/**
 * Data pool setter for HourA Val
 *
 * @param [in]	val		ON/OFF for HourA Val
 * @return void
 */
void data_pool_set_hour_a_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.hourAVal = val;
}
/**
 * Data pool getter for HourA Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_hour_a_val(void)
{
	return g_agl_cluster_data_pool.data.hourAVal;
}

/**
 * Data pool setter for HourB Val
 *
 * @param [in]	val		ON/OFF for HourB Val
 * @return void
 */
void data_pool_set_hour_b_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.hourBVal = val;
}
/**
 * Data pool getter for HourB Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_hour_b_val(void)
{
	return g_agl_cluster_data_pool.data.hourBVal;
}

/**
 * Data pool setter for Minute A Val
 *
 * @param [in]	val		ON/OFF for Minute A Val
 * @return void
 */
void data_pool_set_minute_a_val(uint8_t val)
{
	g_agl_cluster_data_pool.data.minuteAVal = val;
}
/**
 * Data pool getter for Minute A Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint8_t data_pool_get_minute_a_val(void)
{
	return g_agl_cluster_data_pool.data.minuteAVal;
}

/**
 * Data pool setter for Minute B Val
 *
 * @param [in]	val		ON/OFF for Minute B Val
 * @return void
 */
void data_pool_set_minute_b_val(uint8_t val)
{
	g_agl_cluster_data_pool.data.minuteBVal = val;
}
/**
 * Data pool getter for Minute B Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint8_t data_pool_get_minute_b_val(void)
{
	return g_agl_cluster_data_pool.data.minuteBVal;
}

/**
 * Data pool setter for Second A Val
 *
 * @param [in]	val		ON/OFF for Second A Val
 * @return void
 */
void data_pool_set_second_a_val(uint8_t val)
{
	g_agl_cluster_data_pool.data.secondAVal = val;
}
/**
 * Data pool getter for Second A Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint8_t data_pool_get_second_a_val(void)
{
	return g_agl_cluster_data_pool.data.secondAVal;
}

/**
 * Data pool setter for Second B Val
 *
 * @param [in]	val		ON/OFF for Second B Val
 * @return void
 */
void data_pool_set_second_b_val(uint8_t val)
{
	g_agl_cluster_data_pool.data.secondBVal = val;
}
/**
 * Data pool getter for Second B Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint8_t data_pool_get_second_b_val(void)
{
	return g_agl_cluster_data_pool.data.secondBVal;
}

/**
 * Data pool setter for O Temp Val
 *
 * @param [in]	val		ON/OFF for O Temp Val
 * @return void
 */
void data_pool_set_o_temp_val(int16_t val)
{
	g_agl_cluster_data_pool.data.oTempVal = val;
}
/**
 * Data pool getter for O Temp Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
int16_t data_pool_get_o_temp_val(void)
{
	return g_agl_cluster_data_pool.data.oTempVal;
}

/**
 * Data pool setter for O Temp Unit Val
 *
 * @param [in]	val		ON/OFF for O Temp Unit Val
 * @return void
 */
void data_pool_set_o_temp_unit_val(IC_HMI_OTEMP_UNIT_VAL val)
{
	g_agl_cluster_data_pool.data.oTempUnitVal = val;
}
/**
 * Data pool getter for O Temp Unit Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
IC_HMI_OTEMP_UNIT_VAL data_pool_get_o_temp_unit_val(void)
{
	return g_agl_cluster_data_pool.data.oTempUnitVal;
}

/**
 * Data pool setter for Cru Range Val
 *
 * @param [in]	val		ON/OFF for Cru Range Val
 * @return void
 */
void data_pool_set_cru_range_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.cruRangeVal = val;
}
/**
 * Data pool getter for Cru Range Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_cru_range_val(void)
{
	return g_agl_cluster_data_pool.data.cruRangeVal;
}

/**
 * Data pool setter for Avg FuelA Val
 *
 * @param [in]	val		ON/OFF for Avg FuelA Val
 * @return void
 */
void data_pool_set_avg_fuel_a_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.avgFuelAVal = val;
}
/**
 * Data pool getter for Avg FuelA Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_avg_fuel_a_val(void)
{
	return g_agl_cluster_data_pool.data.avgFuelAVal;
}

/**
 * Data pool setter for Avg FuelB Val
 *
 * @param [in]	val		ON/OFF for Avg FuelB Val
 * @return void
 */
void data_pool_set_avg_fuel_b_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.avgFuelBVal = val;
}
/**
 * Data pool getter for Avg FuelB Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_avg_fuel_b_val(void)
{
	return g_agl_cluster_data_pool.data.avgFuelBVal;
}

/**
 * Data pool setter for Ins FuelA Val
 *
 * @param [in]	val		ON/OFF for Ins FuelA Val
 * @return void
 */
void data_pool_set_ins_fuel_a_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.insFuelAVal = val;
}
/**
 * Data pool getter for Ins FuelA Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_ins_fuel_a_val(void)
{
	return g_agl_cluster_data_pool.data.insFuelAVal;
}

/**
 * Data pool setter for Ins FuelB Val
 *
 * @param [in]	val		ON/OFF for Ins FuelB Val
 * @return void
 */
void data_pool_set_ins_fuel_b_val(uint16_t val)
{
	g_agl_cluster_data_pool.data.insFuelBVal = val;
}
/**
 * Data pool getter for Ins FuelB Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint16_t data_pool_get_ins_fuel_b_val(void)
{
	return g_agl_cluster_data_pool.data.insFuelBVal;
}

/**
 * Data pool setter for Fuel Economy Unit Val
 *
 * @param [in]	val		ON/OFF for Fuel Economy Unit Val
 * @return void
 */
void data_pool_set_fuel_economy_uit_val(IC_HMI_FUEL_ECONOMY_UNIT_VAL val)
{
	g_agl_cluster_data_pool.data.fuelEconomyUnitVal = val;
}
/**
 * Data pool getter for Fuel Economy Unit Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
IC_HMI_FUEL_ECONOMY_UNIT_VAL data_pool_get_fuel_economy_uit_val(void)
{
	return g_agl_cluster_data_pool.data.fuelEconomyUnitVal;
}

/**
 *  ===== Shift Position ============================================
 */
/**
 * Data pool setter for Gear At Val
 *
 * @param [in]	val		ON/OFF for Gear At Val
 * @return void
 */
void data_pool_set_gear_at_val(IC_HMI_GEAR_AT_VAL val)
{
	g_agl_cluster_data_pool.data.gearAtVal = val;
}
/**
 * Data pool getter for Gear At Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
IC_HMI_GEAR_AT_VAL data_pool_get_gear_at_val(void)
{
	return g_agl_cluster_data_pool.data.gearAtVal;
}

/**
 * Data pool setter for Gear Mt Val
 *
 * @param [in]	val		ON/OFF for Gear Mt Val
 * @return void
 */
void data_pool_set_gear_mt_val(IC_HMI_GEAR_MT_VAL val)
{
	g_agl_cluster_data_pool.data.gearMtVal = val;
}
/**
 * Data pool getter for Gear Mt Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
IC_HMI_GEAR_MT_VAL data_pool_get_gear_mt_val(void)
{
	return g_agl_cluster_data_pool.data.gearMtVal;
}

/**
 *  ===== Speed =====================================================
 */
/**
 * Data pool setter for Speed Analog Val
 *
 * @param [in]	val		ON/OFF for Speed Analog Val
 * @return void
 */
void data_pool_set_speed_analog_val(uint32_t val)
{
	g_agl_cluster_data_pool.data.spAnalogVal = val;
}
/**
 * Data pool getter for Speed Analog Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint32_t data_pool_get_speed_analog_val(void)
{
	return g_agl_cluster_data_pool.data.spAnalogVal;
}

/**
 * Data pool setter for Speed Analog Digital Val
 *
 * @param [in]	val		ON/OFF for Speed Analog Digital Val
 * @return void
 */
void data_pool_set_speed_analog_digital_val(IC_HMI_SP_UNIT_VAL val)
{
	g_agl_cluster_data_pool.data.spAnaDigUnitVal = val;
}
/**
 * Data pool getter for Speed Analog Digital Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
IC_HMI_SP_UNIT_VAL data_pool_get_speed_analog_digital_val(void)
{
	return g_agl_cluster_data_pool.data.spAnaDigUnitVal;
}

/**
 *  ===== Tacho =====================================================
 */
/**
 * Data pool setter for Tacho Analog Val
 *
 * @param [in]	val		ON/OFF for Tacho Analog Val
 * @return void
 */
void data_pool_set_tacho_analog_val(uint32_t val)
{
	g_agl_cluster_data_pool.data.taAnalogVal = val;
}
/**
 * Data pool getter for Tacho Analog Val
 *
 * @param [in]	void
 * @return IC_HMI_ON_OFF	IC_HMI_OFF	on
 							IC_HMI_ON	off
 */
uint32_t data_pool_get_tacho_analog_val(void)
{
	return g_agl_cluster_data_pool.data.taAnalogVal;
}

