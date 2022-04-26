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


int data_pool_service_setup(sd_event *event, data_pool_service_handle *handle);
int data_pool_service_cleanup(data_pool_service_handle handle);

//-----------------------------------------------------------------------------
#endif //#ifndef DATA_POOL_SERVICE_H
