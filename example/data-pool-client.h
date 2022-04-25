/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.h
 * @brief	cluster-service header
 */
#ifndef DATA_POOL_CLIENT_H
#define DATA_POOL_CLIENT_H
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <systemd/sd-event.h>

/** data pool service handles */
struct s_data_pool_client;
typedef struct s_data_pool_client *data_pool_client_handle;

/** data pool service static configurator. It shall be set statically bosth service and client library.*/
struct s_data_pool_service_configure {
	uint64_t notification_interval; /**< data pool notification interval */

	char socket_name[92]; /**< data pool socket name */
};
typedef struct s_data_pool_service_configure data_pool_service_staticconfig;

int data_pool_client_setup(sd_event *event, data_pool_client_handle *handle);
int data_pool_client_cleanup(data_pool_client_handle handle);

//-----------------------------------------------------------------------------
#endif //#ifndef DATA_POOL_CLIENT_H
