/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service-util.h
 * @brief	cluster-service utility header
 */
#ifndef CLUSTER_SERVICE_UTIL_H
#define CLUSTER_SERVICE_UTIL_H
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <systemd/sd-event.h>

int signal_setup(sd_event *event);

//-----------------------------------------------------------------------------
#endif //#ifndef CLUSTER_SERVICE_UTIL_H
