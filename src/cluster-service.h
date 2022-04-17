/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.h
 * @brief	cluster-service header
 */

#include <stdint.h>

/** data pool service handles */
struct s_data_pool_service;
typedef struct s_data_pool_service *data_pool_service_handle;


/** data pool service static configurator. It shall be set statically bosth service and client library.*/
struct s_data_pool_service_configure
{
	uint64_t notification_interval;	/**< data pool notification interval */
	
	
	char socket_name[92];			/**< data pool socket name */

};

