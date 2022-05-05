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

#ifndef CLUSTER_API_SHIFTPOSITION_H
#define CLUSTER_API_SHIFTPOSITION_H

typedef enum {
	IC_HMI_AT_OFF = 0,
	IC_HMI_AT_PARKING,
	IC_HMI_AT_REVERSE,
	IC_HMI_AT_NEUTRAL,
	IC_HMI_AT_DRIVE,
	IC_HMI_AT_SECOND,
	IC_HMI_AT_LOW_GEAR,
	IC_HMI_AT_FIRST,
	IC_HMI_AT_MANUAL,
	IC_HMI_AT_BRAKE,
	IC_HMI_AT_ALL_ON,
	IC_HMI_AT_ALL_OFF,
	IC_HMI_AT_UNUSED,
} IC_HMI_GEAR_AT_VAL;

typedef enum {
	IC_HMI_MT_OFF = 0,
	IC_HMI_MT_FIRST,
	IC_HMI_MT_SECOND,
	IC_HMI_MT_THIRD,
	IC_HMI_MT_FOURTH,
	IC_HMI_MT_FIFTH,
	IC_HMI_MT_SIXTH,
	IC_HMI_MT_SEVENTH,
	IC_HMI_MT_EIGHTTH,
} IC_HMI_GEAR_MT_VAL;

IC_HMI_GEAR_AT_VAL getGearAtVal(void);
IC_HMI_GEAR_MT_VAL getGearMtVal(void);

#endif // CLUSTER_API_SHIFTPOSITION_H
