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

#ifndef CLUSTER_API_TRIPCOMPUTER_H
#define CLUSTER_API_TRIPCOMPUTER_H

typedef enum
{
    IC_HMI_TRCOM_KM = 0,
    IC_HMI_TRCOM_MILE = 1,
} IC_HMI_TRCOM_UNIT_VAL;

typedef enum
{
    IC_HMI_FUEL_KM_L = 0,
    IC_HMI_FUEL_MPG_US,
    IC_HMI_FUEL_MPG_IG,
    IC_HMI_FUEL_L_100KM,
    IC_HMI_FUEL_MILE_KWH,
    IC_HMI_FUEL_KM_KWH,
    IC_HMI_FUEL_MILE_KG,
    IC_HMI_FUEL_KM_KG,
    IC_HMI_FUEL_KWH_100KM,
} IC_HMI_FUEL_ECONOMY_UNIT_VAL;

typedef enum
{
    IC_HMI_OTEMP_UNIT_C = 0,
    IC_HMI_OTEMP_UNIT_K = 1,
} IC_HMI_OTEMP_UNIT_VAL;

unsigned long getTrcomTripAVal(void);
unsigned long getTrcomTripBVal(void);
unsigned long getTrcomOdoVal(void);
IC_HMI_TRCOM_UNIT_VAL getTrcomUnitVal(void);
unsigned short getAvgSpeedAVal(void);
unsigned short getAvgSpeedBVal(void);
unsigned short getHourAVal(void);
unsigned short getHourBVal(void);
unsigned char getMinuteAVal(void);
unsigned char getMinuteBVal(void);
unsigned char getSecondAVal(void);
unsigned char getSecondBVal(void);
signed short getOTempVal(void);
IC_HMI_OTEMP_UNIT_VAL getOTempUnitVal(void);
unsigned short getCruRangeVal(void);
unsigned short getAvgFuelAVal(void);
unsigned short getAvgFuelBVal(void);
unsigned short getInsFuelAVal(void);
unsigned short getInsFuelBVal(void);
IC_HMI_FUEL_ECONOMY_UNIT_VAL getFuelEconomyUnitVal(void);

#endif // CLUSTER_API_TRIPCOMPUTER_H
