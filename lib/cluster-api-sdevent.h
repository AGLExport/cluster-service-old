/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service-util.h
 * @brief	cluster-service utility header
 */
#ifndef CLUSTER_API_SDEVENT_H
#define CLUSTER_API_SDEVENT_H
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <systemd/sd-event.h>

/** data pool service handles */
struct s_data_pool_client_sdevent;
typedef struct s_data_pool_client_sdevent *data_pool_client_handle_sdevent;

int data_pool_client_setup_sdevent(sd_event *event, data_pool_client_handle_sdevent *handle);
int data_pool_client_cleanup_sdevent(data_pool_client_handle_sdevent handle);
//-----------------------------------------------------------------------------
#endif //#ifndef CLUSTER_SERVICE_UTIL_H
