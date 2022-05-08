/*
 * Copyright (c) 2021, Nippon Seiki Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "data-pool.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cluster_api.h>

static uint64_t gRegisteredSignals = 0x0000000000000000ULL;
static IC_HMI_FUNC_NOTIFY_IC_HMI gNotifyIcHmiCB;

static bool notifyCheck(uint64_t signals);

// == API functions for apps ==
// === Initialize/Terminate ===
bool clusterInit(void)
{
	gRegisteredSignals = 0x0000000000000000ULL;
	gNotifyIcHmiCB = NULL;
	(void) data_pool_register_change_notify(notifyCheck);

	return true;
}

bool clusterTerm(void)
{
	(void) data_pool_register_change_notify(NULL);
	gRegisteredSignals = 0x0000000000000000ULL;
	gNotifyIcHmiCB = NULL;

	return true;
}

// === Register/Notify ===
bool registerIcHmi(uint64_t arg_1, IC_HMI_FUNC_NOTIFY_IC_HMI addr)
{
	if (addr == NULL) {
		return false;
	}

	gNotifyIcHmiCB = addr;
	gRegisteredSignals = (gRegisteredSignals | arg_1);

	return true;
}

bool notifyCheck(uint64_t signals)
{
	uint64_t targetsignals = signals & gRegisteredSignals;

	if ((gNotifyIcHmiCB == NULL) || (targetsignals == 0))
		return 0;

	if ((targetsignals & IC_HMI_TT_TURN_R) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_TURN_R, data_pool_get_turn_r());

	if ((targetsignals & IC_HMI_TT_TURN_L) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_TURN_L, data_pool_get_turn_l());

	if ((targetsignals & IC_HMI_TT_BRAKE) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_BRAKE, data_pool_get_brake());

	if ((targetsignals & IC_HMI_TT_SEATBELT) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_SEATBELT, data_pool_get_seatbelt());

	if ((targetsignals & IC_HMI_TT_HIGHBEAM) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_HIGHBEAM, data_pool_get_high_beam());

	if ((targetsignals & IC_HMI_TT_DOOR) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_DOOR, data_pool_get_door());

	if ((targetsignals & IC_HMI_TT_EPS) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_EPS, data_pool_get_eps());

	if ((targetsignals & IC_HMI_TT_SRS_AIRBAG) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_SRS_AIRBAG, data_pool_get_srs_airbag());

	if ((targetsignals & IC_HMI_TT_ABS) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ABS, data_pool_get_abs());

	if ((targetsignals & IC_HMI_TT_LOW_BATTERY) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_LOW_BATTERY, data_pool_get_low_battery());

	if ((targetsignals & IC_HMI_TT_OIL_PRESS) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_OIL_PRESS, data_pool_get_oil_press());

	if ((targetsignals & IC_HMI_TT_ENGINE) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ENGINE, data_pool_get_engine());

	if ((targetsignals & IC_HMI_TT_FUEL) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_FUEL, data_pool_get_fuel());

	if ((targetsignals & IC_HMI_TT_IMMOBI) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_IMMOBI, data_pool_get_immobi());

	if ((targetsignals & IC_HMI_TT_TM_FAIL) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_TM_FAIL, data_pool_get_tm_fail());

	if ((targetsignals & IC_HMI_TT_ESP_ACT) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ESP_ACT, data_pool_get_esp_act());

	if ((targetsignals & IC_HMI_TT_ESP_OFF) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ESP_OFF, data_pool_get_esp_off());

	if ((targetsignals & IC_HMI_TT_ADAPTING_LIGHTING) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ADAPTING_LIGHTING, data_pool_get_adapting_lighting());

	if ((targetsignals & IC_HMI_TT_AUTO_STOP) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_AUTO_STOP, data_pool_get_auto_stop());

	if ((targetsignals & IC_HMI_TT_AUTO_STOP_FAIL) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_AUTO_STOP_FAIL, data_pool_get_auto_stop_fail());

	if ((targetsignals & IC_HMI_TT_PARKING_LIGHTS) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_PARKING_LIGHTS, data_pool_get_parking_lights());

	if ((targetsignals & IC_HMI_TT_FRONT_FOG) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_FRONT_FOG, data_pool_get_front_fog());

	if ((targetsignals & IC_HMI_TT_EXTERIOR_LIGHT_FAULT) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_EXTERIOR_LIGHT_FAULT, data_pool_get_exterior_light_fault());

	if ((targetsignals & IC_HMI_TT_ACC_FAIL) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_ACC_FAIL, data_pool_get_acc_fail());

	if ((targetsignals & IC_HMI_TT_LDW_OFF) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_LDW_OFF, data_pool_get_ldw_off());

	if ((targetsignals & IC_HMI_TT_HILL_DESCENT) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_HILL_DESCENT, data_pool_get_hill_descent());

	if ((targetsignals & IC_HMI_TT_AUTO_HI_BEAM_GREEN) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_AUTO_HI_BEAM_GREEN, data_pool_get_auto_hi_beam_green());

	if ((targetsignals & IC_HMI_TT_AUTO_HI_BEAM_AMBER) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_AUTO_HI_BEAM_AMBER, data_pool_get_auto_hi_beam_amber());

	if ((targetsignals & IC_HMI_TT_LDW_OPERATE) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_LDW_OPERATE, data_pool_get_ldw_operate());

	if ((targetsignals & IC_HMI_TT_GENERAL_WARN) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_GENERAL_WARN, data_pool_get_general_warn());

	if ((targetsignals & IC_HMI_TT_SPORTS_MODE) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_SPORTS_MODE, data_pool_get_sports_mode());

	if ((targetsignals & IC_HMI_TT_DRIVING_POWER_MODE) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_DRIVING_POWER_MODE, data_pool_get_driving_power_mode());

	if ((targetsignals & IC_HMI_TT_HOT_TEMP) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_HOT_TEMP, data_pool_get_hot_temp());

	if ((targetsignals & IC_HMI_TT_LOW_TEMP) != 0)
		gNotifyIcHmiCB(IC_HMI_TT_LOW_TEMP, data_pool_get_low_temp());

	return true;
}
// === Telltale ===
IC_HMI_ON_OFF getTurnR(void)
{
	return data_pool_get_turn_r();
}

IC_HMI_ON_OFF getTurnL(void)
{
	return data_pool_get_turn_l();
}

IC_HMI_ON_OFF getBrake(void)
{
	return data_pool_get_brake();
}

IC_HMI_ON_OFF getSeatbelt(void)
{
	return data_pool_get_seatbelt();
}

IC_HMI_ON_OFF getFrontRightSeatbelt(void)
{
	return data_pool_get_front_right_seatbelt();
}

IC_HMI_ON_OFF getFrontCenterSeatbelt(void)
{
	return data_pool_get_front_center_seatbelt();
}

IC_HMI_ON_OFF getFrontLeftSeatbelt(void)
{
	return data_pool_get_front_left_seatbelt();
}

IC_HMI_ON_OFF getMid1RightSeatbelt(void)
{
	return data_pool_get_mid1_right_seatbelt();
}

IC_HMI_ON_OFF getMid1CenterSeatbelt(void)
{
	return data_pool_get_mid1_center_seatbelt();
}

IC_HMI_ON_OFF getMid1LeftSeatbelt(void)
{
	return data_pool_get_mid1_left_seatbelt();
}

IC_HMI_ON_OFF getMid2RightSeatbelt(void)
{
	return data_pool_get_mid2_right_seatbelt();
}

IC_HMI_ON_OFF getMid2CenterSeatbelt(void)
{
	return data_pool_get_mid2_center_seatbelt();
}

IC_HMI_ON_OFF getMid2LeftSeatbelt(void)
{
	return data_pool_get_mid2_left_seatbelt();
}

IC_HMI_ON_OFF getRearRightSeatbelt(void)
{
	return data_pool_get_rear_right_seatbelt();
}

IC_HMI_ON_OFF getRearCenterSeatbelt(void)
{
	return data_pool_get_rear_center_seatbelt();
}

IC_HMI_ON_OFF getRearLeftSeatbelt(void)
{
	return data_pool_get_rear_left_seatbelt();
}

IC_HMI_ON_OFF getHighbeam(void)
{
	return data_pool_get_high_beam();
}

IC_HMI_ON_OFF getDoor(void)
{
	return data_pool_get_door();
}

IC_HMI_ON_OFF getFrontRightDoor(void)
{
	return data_pool_get_front_right_door();
}

IC_HMI_ON_OFF getFrontLeftDoor(void)
{
	return data_pool_get_front_left_door();
}

IC_HMI_ON_OFF getRearRightDoor(void)
{
	return data_pool_get_rear_right_door();
}

IC_HMI_ON_OFF getRearLeftDoor(void)
{
	return data_pool_get_rear_left_door();
}

IC_HMI_ON_OFF getTrunkDoor(void)
{
	return data_pool_get_trunk_door();
}

IC_HMI_ON_OFF getHoodDoor(void)
{
	return data_pool_get_hood_door();
}

IC_HMI_ON_OFF getEps(void)
{
	return data_pool_get_eps();
}

IC_HMI_ON_OFF getSrsAirbag(void)
{
	return data_pool_get_srs_airbag();
}

IC_HMI_ON_OFF getAbs(void)
{
	return data_pool_get_abs();
}

IC_HMI_ON_OFF getLowBattery(void)
{
	return data_pool_get_low_battery();
}

IC_HMI_ON_OFF getOilPress(void)
{
	return data_pool_get_oil_press();
}

IC_HMI_ON_OFF getEngine(void)
{
	return data_pool_get_engine();
}

IC_HMI_ON_OFF getFuel(void)
{
	return data_pool_get_fuel();
}

IC_HMI_ON_OFF getImmobi(void)
{
	return data_pool_get_immobi();
}

IC_HMI_ON_OFF getTMFail(void)
{
	return data_pool_get_tm_fail();
}

IC_HMI_ON_OFF getEspAct(void)
{
	return data_pool_get_esp_act();
}

IC_HMI_ON_OFF getEspOff(void)
{
	return data_pool_get_esp_off();
}

IC_HMI_ON_OFF getAdaptingLighting(void)
{
	return data_pool_get_adapting_lighting();
}

IC_HMI_ON_OFF getAutoStop(void)
{
	return data_pool_get_auto_stop();
}

IC_HMI_ON_OFF getAutoStopFail(void)
{
	return data_pool_get_auto_stop_fail();
}

IC_HMI_ON_OFF getParkingLights(void)
{
	return data_pool_get_parking_lights();
}

IC_HMI_ON_OFF getFrontFog(void)
{
	return data_pool_get_front_fog();
}

IC_HMI_ON_OFF getExteriorLightFault(void)
{
	return data_pool_get_exterior_light_fault();
}

IC_HMI_ON_OFF getAccFail(void)
{
	return data_pool_get_acc_fail();
}

IC_HMI_ON_OFF getLdwOff(void)
{
	return data_pool_get_ldw_off();
}

IC_HMI_ON_OFF getHillDescent(void)
{
	return data_pool_get_hill_descent();
}

IC_HMI_ON_OFF getAutoHiBeamGreen(void)
{
	return data_pool_get_auto_hi_beam_green();
}

IC_HMI_ON_OFF getAutoHiBeamAmber(void)
{
	return data_pool_get_auto_hi_beam_amber();
}

IC_HMI_ON_OFF getSportsMode(void)
{
	return data_pool_get_sports_mode();
}

IC_HMI_ON_OFF getLdwOperate(void)
{
	return data_pool_get_ldw_operate();
}

IC_HMI_ON_OFF getGeneralWarn(void)
{
	return data_pool_get_general_warn();
}

IC_HMI_ON_OFF getDriverPowerMode(void)
{
	return data_pool_get_driving_power_mode();
}

IC_HMI_ON_OFF getHotTemp(void)
{
	return data_pool_get_hot_temp();
}

IC_HMI_ON_OFF getLowTemp(void)
{
	return data_pool_get_low_temp();
}

// === TripComputer ===
unsigned long getTrcomTripAVal(void)
{
	return data_pool_get_trcom_trip_a_val();
}

unsigned long getTrcomTripBVal(void)
{
	return data_pool_get_trcom_trip_b_val();
}

unsigned long getTrcomOdoVal(void)
{
	return data_pool_get_trcom_odo_val();
}

IC_HMI_TRCOM_UNIT_VAL getTrcomUnitVal(void)
{
	return data_pool_get_trcom_unit_val();
}

unsigned short getAvgSpeedAVal(void)
{
	return data_pool_get_avg_speed_a_val();
}

unsigned short getAvgSpeedBVal(void)
{
	return data_pool_get_avg_speed_b_val();
}

unsigned short getHourAVal(void)
{
	return data_pool_get_hour_a_val();
}

unsigned short getHourBVal(void)
{
	return data_pool_get_hour_b_val();
}

unsigned char getMinuteAVal(void)
{
	return data_pool_get_minute_a_val();
}

unsigned char getMinuteBVal(void)
{
	return data_pool_get_minute_b_val();
}

unsigned char getSecondAVal(void)
{
	return data_pool_get_second_a_val();
}

unsigned char getSecondBVal(void)
{
	return data_pool_get_second_b_val();
}

signed short getOTempVal(void)
{
	return data_pool_get_o_temp_val();
}

IC_HMI_OTEMP_UNIT_VAL getOTempUnitVal(void)
{
	return data_pool_get_o_temp_unit_val();
}

unsigned short getCruRangeVal(void)
{
	return data_pool_get_cru_range_val();
}

unsigned short getAvgFuelAVal(void)
{
	return data_pool_get_avg_fuel_a_val();
}

unsigned short getAvgFuelBVal(void)
{
	return data_pool_get_avg_fuel_b_val();
}

unsigned short getInsFuelAVal(void)
{
	return data_pool_get_ins_fuel_a_val();
}

unsigned short getInsFuelBVal(void)
{
	return data_pool_get_ins_fuel_b_val();
}

IC_HMI_FUEL_ECONOMY_UNIT_VAL getFuelEconomyUnitVal(void)
{
	return data_pool_get_fuel_economy_uit_val();
}

// === ShiftPosition ===
IC_HMI_GEAR_AT_VAL getGearAtVal(void)
{
	return data_pool_get_gear_at_val();
}

IC_HMI_GEAR_MT_VAL getGearMtVal(void)
{
	return data_pool_get_gear_mt_val();
}

// === Speed ===
unsigned long getSpAnalogVal(void)
{
	return data_pool_get_speed_analog_val();
}

IC_HMI_SP_UNIT_VAL getSpAnaDigUnitVal(void)
{
	return data_pool_get_speed_analog_digital_val();
}

// === Tacho ===
unsigned long getTaAnalogVal(void)
{
	return data_pool_get_tacho_analog_val();
}
