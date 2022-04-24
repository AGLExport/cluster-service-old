/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.h
 * @brief	cluster-service header
 */
#ifndef DATA_POOL_SERVICE_H
#define DATA_POOL_SERVICE_H
//-----------------------------------------------------------------------------
#include <stdint.h>
#include <systemd/sd-event.h>

/** data pool service handles */
struct s_data_pool_service;
typedef struct s_data_pool_service *data_pool_service_handle;

/** data pool service static configurator. It shall be set statically bosth service and client library.*/
struct s_data_pool_service_configure {
	uint64_t notification_interval; /**< data pool notification interval */

	char socket_name[92]; /**< data pool socket name */
};
typedef struct s_data_pool_service_configure data_pool_service_staticconfig;

int data_pool_service_setup(sd_event *event, data_pool_service_handle *handle);
int data_pool_service_cleanup(data_pool_service_handle handle);

//-----------------------------------------------------------------------------
#endif //#ifndef DATA_POOL_SERVICE_H
