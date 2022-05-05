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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <cluster_api.h>
#include <cluster_api_internal.h>

static IPC_DATA_IC_SERVICE_S gAllSigData;
static unsigned long long gRegisteredSignals = 0x0000000000000000ULL;
static IC_HMI_FUNC_NOTIFY_IC_HMI gNotifyIcHmiCB;

static IPC_RET_E clusterClientStart(void);
static IPC_RET_E clusterReadDataPool(void);
static IPC_RET_E clusterRegisterCallback(void);
static IPC_RET_E clusterClientStop(void);
static void notifyCheck(void* pData, signed int size, int kind);


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


// === Telltale ===
IC_HMI_ON_OFF getTurnR(void)
{
    clusterReadDataPool();
    return gAllSigData.turnR;
}

IC_HMI_ON_OFF getTurnL(void)
{
    clusterReadDataPool();
    return gAllSigData.turnL;
}

IC_HMI_ON_OFF getBrake(void)
{
    clusterReadDataPool();
    return gAllSigData.brake;
}

IC_HMI_ON_OFF getSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.seatbelt;
}

IC_HMI_ON_OFF getFrontRightSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.frontRightSeatbelt;
}

IC_HMI_ON_OFF getFrontCenterSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.frontCenterSeatbelt;
}

IC_HMI_ON_OFF getFrontLeftSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.frontLeftSeatbelt;
}

IC_HMI_ON_OFF getMid1RightSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid1RightSeatbelt;
}

IC_HMI_ON_OFF getMid1CenterSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid1CenterSeatbelt;
}

IC_HMI_ON_OFF getMid1LeftSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid1LeftSeatbelt;
}

IC_HMI_ON_OFF getMid2RightSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid2RightSeatbelt;
}

IC_HMI_ON_OFF getMid2CenterSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid2CenterSeatbelt;
}

IC_HMI_ON_OFF getMid2LeftSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.mid2LeftSeatbelt;
}

IC_HMI_ON_OFF getRearRightSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.rearRightSeatbelt;
}

IC_HMI_ON_OFF getRearCenterSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.rearCenterSeatbelt;
}

IC_HMI_ON_OFF getRearLeftSeatbelt(void)
{
    clusterReadDataPool();
    return gAllSigData.rearLeftSeatbelt;
}

IC_HMI_ON_OFF getHighbeam(void)
{
    clusterReadDataPool();
    return gAllSigData.highbeam;
}

IC_HMI_ON_OFF getDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.door;
}

IC_HMI_ON_OFF getFrontRightDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.frontRightDoor;
}

IC_HMI_ON_OFF getFrontLeftDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.frontLeftDoor;
}

IC_HMI_ON_OFF getRearRightDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.rearRightDoor;
}

IC_HMI_ON_OFF getRearLeftDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.rearLeftDoor;
}

IC_HMI_ON_OFF getTrunkDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.trunkDoor;
}

IC_HMI_ON_OFF getHoodDoor(void)
{
    clusterReadDataPool();
    return gAllSigData.hoodDoor;
}

IC_HMI_ON_OFF getEps(void)
{
    clusterReadDataPool();
    return gAllSigData.eps;
}

IC_HMI_ON_OFF getSrsAirbag(void)
{
    clusterReadDataPool();
    return gAllSigData.srsAirbag;
}

IC_HMI_ON_OFF getAbs(void)
{
    clusterReadDataPool();
    return gAllSigData.abs;
}

IC_HMI_ON_OFF getLowBattery(void)
{
    clusterReadDataPool();
    return gAllSigData.lowBattery;
}

IC_HMI_ON_OFF getOilPress(void)
{
    clusterReadDataPool();
    return gAllSigData.oilPress;
}

IC_HMI_ON_OFF getEngine(void)
{
    clusterReadDataPool();
    return gAllSigData.engine;
}

IC_HMI_ON_OFF getFuel(void)
{
    clusterReadDataPool();
    return gAllSigData.fuel;
}

IC_HMI_ON_OFF getImmobi(void)
{
    clusterReadDataPool();
    return gAllSigData.immobi;
}

IC_HMI_ON_OFF getTMFail(void)
{
    clusterReadDataPool();
    return gAllSigData.tmFail;
}

IC_HMI_ON_OFF getEspAct(void)
{
    clusterReadDataPool();
    return gAllSigData.espAct;
}

IC_HMI_ON_OFF getEspOff(void)
{
    clusterReadDataPool();
    return gAllSigData.espOff;
}

IC_HMI_ON_OFF getAdaptingLighting(void)
{
    clusterReadDataPool();
    return gAllSigData.adaptingLighting;
}

IC_HMI_ON_OFF getAutoStop(void)
{
    clusterReadDataPool();
    return gAllSigData.autoStop;
}

IC_HMI_ON_OFF getAutoStopFail(void)
{
    clusterReadDataPool();
    return gAllSigData.autoStopFail;
}

IC_HMI_ON_OFF getParkingLights(void)
{
    clusterReadDataPool();
    return gAllSigData.parkingLights;
}

IC_HMI_ON_OFF getFrontFog(void)
{
    clusterReadDataPool();
    return gAllSigData.frontFog;
}

IC_HMI_ON_OFF getExteriorLightFault(void)
{
    clusterReadDataPool();
    return gAllSigData.exteriorLightFault;
}

IC_HMI_ON_OFF getAccFail(void)
{
    clusterReadDataPool();
    return gAllSigData.accFail;
}

IC_HMI_ON_OFF getLdwOff(void)
{
    clusterReadDataPool();
    return gAllSigData.ldwOff;
}

IC_HMI_ON_OFF getHillDescent(void)
{
    clusterReadDataPool();
    return gAllSigData.hillDescent;
}

IC_HMI_ON_OFF getAutoHiBeamGreen(void)
{
    clusterReadDataPool();
    return gAllSigData.autoHiBeamGreen;
}

IC_HMI_ON_OFF getAutoHiBeamAmber(void)
{
    clusterReadDataPool();
    return gAllSigData.autoHiBeamAmber;
}

IC_HMI_ON_OFF getSportsMode(void)
{
    clusterReadDataPool();
    return gAllSigData.sportsMode;
}

IC_HMI_ON_OFF getLdwOperate(void)
{
    clusterReadDataPool();
    return gAllSigData.ldwOperate;
}

IC_HMI_ON_OFF getGeneralWarn(void)
{
    clusterReadDataPool();
    return gAllSigData.generalWarn;
}

IC_HMI_ON_OFF getDriverPowerMode(void)
{
    clusterReadDataPool();
    return gAllSigData.drivingPowerMode;
}

IC_HMI_ON_OFF getHotTemp(void)
{
    clusterReadDataPool();
    return gAllSigData.hotTemp;
}

IC_HMI_ON_OFF getLowTemp(void)
{
    clusterReadDataPool();
    return gAllSigData.lowTemp;
}

// === TripComputer ===
unsigned long getTrcomTripAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.trcomTripAVal;
}

unsigned long getTrcomTripBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.trcomTripBVal;
}

unsigned long getTrcomOdoVal(void)
{
    clusterReadDataPool();
    return gAllSigData.trcomOdoVal;
}

IC_HMI_TRCOM_UNIT_VAL getTrcomUnitVal(void)
{
    clusterReadDataPool();
    return gAllSigData.trcomUnitVal;
}

unsigned short getAvgSpeedAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.avgSpeedAVal;
}

unsigned short getAvgSpeedBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.avgSpeedBVal;
}

unsigned short getHourAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.hourAVal;
}

unsigned short getHourBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.hourBVal;
}

unsigned char getMinuteAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.minuteAVal;
}

unsigned char getMinuteBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.minuteBVal;
}

unsigned char getSecondAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.secondAVal;
}

unsigned char getSecondBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.secondBVal;
}

signed short getOTempVal(void)
{
    clusterReadDataPool();
    return gAllSigData.oTempVal;
}

IC_HMI_OTEMP_UNIT_VAL getOTempUnitVal(void)
{
    clusterReadDataPool();
    return gAllSigData.oTempUnitVal;
}

unsigned short getCruRangeVal(void)
{
    clusterReadDataPool();
    return gAllSigData.cruRangeVal;
}

unsigned short getAvgFuelAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.avgFuelAVal;
}

unsigned short getAvgFuelBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.avgFuelBVal;
}

unsigned short getInsFuelAVal(void)
{
    clusterReadDataPool();
    return gAllSigData.insFuelAVal;
}

unsigned short getInsFuelBVal(void)
{
    clusterReadDataPool();
    return gAllSigData.insFuelBVal;
}

IC_HMI_FUEL_ECONOMY_UNIT_VAL getFuelEconomyUnitVal(void)
{
    clusterReadDataPool();
    return gAllSigData.fuelEconomyUnitVal;
}

// === ShiftPosition ===
IC_HMI_GEAR_AT_VAL getGearAtVal(void)
{
    clusterReadDataPool();
    return gAllSigData.gearAtVal;
}

IC_HMI_GEAR_MT_VAL getGearMtVal(void)
{
    clusterReadDataPool();
    return gAllSigData.gearMtVal;
}

// === Speed ===
unsigned long getSpAnalogVal(void)
{
    clusterReadDataPool();
    return gAllSigData.spAnalogVal;
}

IC_HMI_SP_UNIT_VAL getSpAnaDigUnitVal(void)
{
    clusterReadDataPool();
    return gAllSigData.spAnaDigUnitVal;
}

// === Tacho ===
unsigned long getTaAnalogVal(void)
{
    clusterReadDataPool();
    return gAllSigData.taAnalogVal;
}

