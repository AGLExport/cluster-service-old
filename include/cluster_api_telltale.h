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

#ifndef CLUSTER_API_TELLTALE_H
#define CLUSTER_API_TELLTALE_H

// Signal flags
#define IC_HMI_TT_TURN_R 0x0000000000000001ULL
#define IC_HMI_TT_TURN_L 0x0000000000000002ULL
#define IC_HMI_TT_BRAKE 0x0000000000000004ULL
#define IC_HMI_TT_SEATBELT 0x0000000000000008ULL
#define IC_HMI_TT_HIGHBEAM 0x0000000000000010ULL
#define IC_HMI_TT_DOOR 0x0000000000000020ULL
#define IC_HMI_TT_EPS 0x0000000000000040ULL
#define IC_HMI_TT_SRS_AIRBAG 0x0000000000000080ULL
#define IC_HMI_TT_ABS 0x0000000000000100ULL
#define IC_HMI_TT_LOW_BATTERY 0x0000000000000200ULL
#define IC_HMI_TT_OIL_PRESS 0x0000000000000400ULL
#define IC_HMI_TT_ENGINE 0x0000000000000800ULL
#define IC_HMI_TT_FUEL 0x0000000000001000ULL
#define IC_HMI_TT_IMMOBI 0x0000000000002000ULL
#define IC_HMI_TT_TM_FAIL 0x0000000000004000ULL
#define IC_HMI_TT_ESP_ACT 0x0000000000008000ULL
#define IC_HMI_TT_ESP_OFF 0x0000000000010000ULL
#define IC_HMI_TT_ADAPTING_LIGHTING 0x0000000000020000ULL
#define IC_HMI_TT_AUTO_STOP 0x0000000000040000ULL
#define IC_HMI_TT_AUTO_STOP_FAIL 0x0000000000080000ULL
#define IC_HMI_TT_PARKING_LIGHTS 0x0000000000100000ULL
#define IC_HMI_TT_FRONT_FOG 0x0000000000200000ULL
#define IC_HMI_TT_EXTERIOR_LIGHT_FAULT 0x0000000000400000ULL
#define IC_HMI_TT_ACC_FAIL 0x0000000000800000ULL
#define IC_HMI_TT_LDW_OFF 0x0000000001000000ULL
#define IC_HMI_TT_HILL_DESCENT 0x0000000002000000ULL
#define IC_HMI_TT_AUTO_HI_BEAM_GREEN 0x0000000004000000ULL
#define IC_HMI_TT_AUTO_HI_BEAM_AMBER 0x0000000008000000ULL
#define IC_HMI_TT_LDW_OPERATE 0x0000000010000000ULL
#define IC_HMI_TT_GENERAL_WARN 0x0000000020000000ULL
#define IC_HMI_TT_SPORTS_MODE 0x0000000040000000ULL
#define IC_HMI_TT_DRIVING_POWER_MODE 0x0000000080000000ULL
#define IC_HMI_TT_HOT_TEMP 0x0000000100000000ULL
#define IC_HMI_TT_LOW_TEMP 0x0000000200000000ULL
#define IC_HMI_TT_ALL 0xFFFFFFFFFFFFFFFFULL

IC_HMI_ON_OFF getTurnR(void);
IC_HMI_ON_OFF getTurnL(void);
IC_HMI_ON_OFF getBrake(void);
IC_HMI_ON_OFF getSeatbelt(void);
IC_HMI_ON_OFF getFrontRightSeatbelt(void);
IC_HMI_ON_OFF getFrontCenterSeatbelt(void);
IC_HMI_ON_OFF getFrontLeftSeatbelt(void);
IC_HMI_ON_OFF getMid1RightSeatbelt(void);
IC_HMI_ON_OFF getMid1CenterSeatbelt(void);
IC_HMI_ON_OFF getMid1LeftSeatbelt(void);
IC_HMI_ON_OFF getMid2RightSeatbelt(void);
IC_HMI_ON_OFF getMid2CenterSeatbelt(void);
IC_HMI_ON_OFF getMid2LeftSeatbelt(void);
IC_HMI_ON_OFF getRearRightSeatbelt(void);
IC_HMI_ON_OFF getRearCenterSeatbelt(void);
IC_HMI_ON_OFF getRearLeftSeatbelt(void);
IC_HMI_ON_OFF getHighbeam(void);
IC_HMI_ON_OFF getDoor(void);
IC_HMI_ON_OFF getFrontRightDoor(void);
IC_HMI_ON_OFF getFrontLeftDoor(void);
IC_HMI_ON_OFF getRearRightDoor(void);
IC_HMI_ON_OFF getRearLeftDoor(void);
IC_HMI_ON_OFF getTrunkDoor(void);
IC_HMI_ON_OFF getHoodDoor(void);
IC_HMI_ON_OFF getEps(void);
IC_HMI_ON_OFF getSrsAirbag(void);
IC_HMI_ON_OFF getAbs(void);
IC_HMI_ON_OFF getLowBattery(void);
IC_HMI_ON_OFF getOilPress(void);
IC_HMI_ON_OFF getEngine(void);
IC_HMI_ON_OFF getFuel(void);
IC_HMI_ON_OFF getImmobi(void);
IC_HMI_ON_OFF getTMFail(void);
IC_HMI_ON_OFF getEspAct(void);
IC_HMI_ON_OFF getEspOff(void);
IC_HMI_ON_OFF getAdaptingLighting(void);
IC_HMI_ON_OFF getAutoStop(void);
IC_HMI_ON_OFF getAutoStopFail(void);
IC_HMI_ON_OFF getParkingLights(void);
IC_HMI_ON_OFF getFrontFog(void);
IC_HMI_ON_OFF getExteriorLightFault(void);
IC_HMI_ON_OFF getAccFail(void);
IC_HMI_ON_OFF getLdwOff(void);
IC_HMI_ON_OFF getHillDescent(void);
IC_HMI_ON_OFF getAutoHiBeamGreen(void);
IC_HMI_ON_OFF getAutoHiBeamAmber(void);
IC_HMI_ON_OFF getSportsMode(void);
IC_HMI_ON_OFF getLdwOperate(void);
IC_HMI_ON_OFF getGeneralWarn(void);
IC_HMI_ON_OFF getDriverPowerMode(void);
IC_HMI_ON_OFF getHotTemp(void);
IC_HMI_ON_OFF getLowTemp(void);

#endif // CLUSTER_API_TELLTALE_H
