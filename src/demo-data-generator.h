/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	demo-data-generator.h
 * @brief	demo data generator header
 */
#ifndef DEMO_DATA_GENERATOR_H
#define DEMO_DATA_GENERATOR_H
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <systemd/sd-event.h>

int demo_data_generator_setup(sd_event *event);
int demo_data_generator_cleanup(void);

//-----------------------------------------------------------------------------
#endif //#ifndef DEMO_DATA_GENERATOR_H
