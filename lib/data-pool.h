/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data_pool.h
 * @brief	data pool header
 */
#ifndef DATA_POOL_H
#define DATA_POOL_H
//-----------------------------------------------------------------------------
#include "cluster_api.h"
#include "ipc_protocol.h"
#include <stdbool.h>

#include "data-pool-storage.h"

/**
 *  ====== Telltale =======================================
 */
void data_pool_set_turn_r(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_turn_r(void);

void data_pool_set_turn_l(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_turn_l(void);

void data_pool_set_brake(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_brake(void);

void data_pool_set_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_seatbelt(void);

void data_pool_set_front_right_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_right_seatbelt(void);

void data_pool_set_front_center_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_center_seatbelt(void);

void data_pool_set_front_left_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_left_seatbelt(void);

void data_pool_set_mid1_right_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid1_right_seatbelt(void);

void data_pool_set_mid1_center_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid1_center_seatbelt(void);

void data_pool_set_mid1_left_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid1_left_seatbelt(void);

void data_pool_set_mid2_right_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid2_right_seatbelt(void);

void data_pool_set_mid2_center_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid2_center_seatbelt(void);

void data_pool_set_mid2_left_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_mid2_left_seatbelt(void);

void data_pool_set_rear_right_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_rear_right_seatbelt(void);

void data_pool_set_rear_center_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_rear_center_seatbelt(void);

void data_pool_set_rear_left_seatbelt(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_rear_left_seatbelt(void);

void data_pool_set_high_beam(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_high_beam(void);

void data_pool_set_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_door(void);

void data_pool_set_front_right_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_right_door(void);

void data_pool_set_front_left_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_left_door(void);

void data_pool_set_rear_right_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_rear_right_door(void);

void data_pool_set_rear_left_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_rear_left_door(void);

void data_pool_set_trunk_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_trunk_door(void);

void data_pool_set_hood_door(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_hood_door(void);

void data_pool_set_eps(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_eps(void);

void data_pool_set_srs_airbag(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_srs_airbag(void);

void data_pool_set_abs(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_abs(void);

void data_pool_set_low_battery(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_low_battery(void);

void data_pool_set_oil_press(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_oil_press(void);

void data_pool_set_engine(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_engine(void);

void data_pool_set_fuel(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_fuel(void);

void data_pool_set_immobi(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_immobi(void);

void data_pool_set_tm_fail(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_tm_fail(void);

void data_pool_set_esp_act(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_esp_act(void);

void data_pool_set_esp_off(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_esp_off(void);

void data_pool_set_adapting_lighting(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_adapting_lighting(void);

void data_pool_set_auto_stop(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_auto_stop(void);

void data_pool_set_auto_stop_fail(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_auto_stop_fail(void);

void data_pool_set_parking_lights(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_parking_lights(void);

void data_pool_set_front_fog(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_front_fog(void);

void data_pool_set_exterior_light_fault(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_exterior_light_fault(void);

void data_pool_set_acc_fail(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_acc_fail(void);

void data_pool_set_ldw_off(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_ldw_off(void);

void data_pool_set_hill_descent(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_hill_descent(void);

void data_pool_set_auto_hi_beam_green(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_auto_hi_beam_green(void);

void data_pool_set_auto_hi_beam_amber(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_auto_hi_beam_amber(void);

void data_pool_set_sports_mode(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_sports_mode(void);

void data_pool_set_ldw_operate(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_ldw_operate(void);

void data_pool_set_general_warn(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_general_warn(void);

void data_pool_set_driving_power_mode(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_driving_power_mode(void);

void data_pool_set_hot_temp(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_hot_temp(void);

void data_pool_set_low_temp(IC_HMI_ON_OFF val);
IC_HMI_ON_OFF data_pool_get_low_temp(void);

/**
 *  ===== Trip Computer =============================================
 */
void data_pool_set_trcom_trip_a_val(uint32_t val);
uint32_t data_pool_get_trcom_trip_a_val(void);

void data_pool_set_trcom_trip_b_val(uint32_t val);
uint32_t data_pool_get_trcom_trip_b_val(void);

void data_pool_set_trcom_odo_val(uint32_t val);
uint32_t data_pool_get_trcom_odo_val(void);

void data_pool_set_trcom_unit_val(int32_t val);
int32_t data_pool_get_trcom_unit_val(void);

void data_pool_set_avg_speed_a_val(uint16_t val);
uint16_t data_pool_get_avg_speed_a_val(void);

void data_pool_set_avg_speed_b_val(uint16_t val);
uint16_t data_pool_get_avg_speed_b_val(void);

void data_pool_set_hour_a_val(uint16_t val);
uint16_t data_pool_get_hour_a_val(void);

void data_pool_set_hour_b_val(uint16_t val);
uint16_t data_pool_get_hour_b_val(void);

void data_pool_set_minute_a_val(uint8_t val);
uint8_t data_pool_get_minute_a_val(void);

void data_pool_set_minute_b_val(uint8_t val);
uint8_t data_pool_get_minute_b_val(void);

void data_pool_set_second_a_val(uint8_t val);
uint8_t data_pool_get_second_a_val(void);

void data_pool_set_second_b_val(uint8_t val);
uint8_t data_pool_get_second_b_val(void);

void data_pool_set_o_temp_val(int16_t val);
int16_t data_pool_get_o_temp_val(void);

void data_pool_set_o_temp_unit_val(IC_HMI_OTEMP_UNIT_VAL val);
IC_HMI_OTEMP_UNIT_VAL data_pool_get_o_temp_unit_val(void);

void data_pool_set_cru_range_val(uint16_t val);
uint16_t data_pool_get_cru_range_val(void);

void data_pool_set_avg_fuel_a_val(uint16_t val);
uint16_t data_pool_get_avg_fuel_a_val(void);

void data_pool_set_avg_fuel_b_val(uint16_t val);
uint16_t data_pool_get_avg_fuel_b_val(void);

void data_pool_set_ins_fuel_a_val(uint16_t val);
uint16_t data_pool_get_ins_fuel_a_val(void);

void data_pool_set_ins_fuel_b_val(uint16_t val);
uint16_t data_pool_get_ins_fuel_b_val(void);

void data_pool_set_fuel_economy_uit_val(IC_HMI_FUEL_ECONOMY_UNIT_VAL val);
IC_HMI_FUEL_ECONOMY_UNIT_VAL data_pool_get_fuel_economy_uit_val(void);

/**
 *  ===== Shift Position ============================================
 */
void data_pool_set_gear_at_val(IC_HMI_GEAR_AT_VAL val);
IC_HMI_GEAR_AT_VAL data_pool_get_gear_at_val(void);

void data_pool_set_gear_mt_val(IC_HMI_GEAR_MT_VAL val);
IC_HMI_GEAR_MT_VAL data_pool_get_gear_mt_val(void);

/**
 *  ===== Speed =====================================================
 */
void data_pool_set_speed_analog_val(uint32_t val);
uint32_t data_pool_get_speed_analog_val(void);

void data_pool_set_speed_analog_digital_val(IC_HMI_SP_UNIT_VAL val);
IC_HMI_SP_UNIT_VAL data_pool_get_speed_analog_digital_val(void);

/**
 *  ===== Tacho =====================================================
 */
void data_pool_set_tacho_analog_val(uint32_t val);
uint32_t data_pool_get_tacho_analog_val(void);

//-----------------------------------------------------------------------------
#endif //#ifndef DATA_POOL_H
