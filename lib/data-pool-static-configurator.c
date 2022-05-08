/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service.c
 * @brief	data service provider
 */

#include "data-pool-static-configurator.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>


/** data pool service static configurator. It shall be set statically bosth service and client library.*/
struct s_data_pool_service_configure {
	uint64_t notification_interval; /**< Parametor for data pool notification interval */

	int32_t data_pool_service_session_limit; /**< Parametor for internal limitation for datapool service
						    sessions. It use link list search limit. */

	char socket_name[92]; /**< data pool socket name */
};
typedef struct s_data_pool_service_configure data_pool_service_staticconfig;

static const struct s_data_pool_service_configure g_config = {
	.notification_interval = (16 * 1000),	  // usec
	.data_pool_service_session_limit = (100), // counts

	.socket_name = "\0/agl/agl-cluster-service",
};

/**
 * Getter for the data pool notification interval.
 *
 * @return uint64_t	 Interval time for the data pool notification.
 */
uint64_t get_data_pool_notification_interval(void)
{
	return g_config.notification_interval;
}

/**
 * Getter for the data pool service session limit.
 *
 * @return int	 Session limit for the data pool server.
 */
int get_data_pool_service_session_limit(void)
{
	return (int) g_config.data_pool_service_session_limit;
}

/**
 * Getter for the data pool service socket name.
 *
 * @param [in]	str		Pointer to the socket name string buffer
 * @param [in]	len		Buffer bytes for the socket name string buffer
 * @return int	>0	Socket name bytes.
 *				0<	Param len is smaller than required size. - required size.
 */
int get_data_pool_service_socket_name(char *str, int len)
{
	if (len >= sizeof(g_config.socket_name)) {
		(void) memcpy(str, g_config.socket_name, sizeof(g_config.socket_name));

		if (g_config.socket_name[0] == '\0') {
			// abstract socket
			int bytes = 1;
			for (bytes = 1; bytes < sizeof(g_config.socket_name); bytes++) {
				if (g_config.socket_name[bytes] == '\0')
					break;
			}
			return bytes;
		} else {
			// socket file
			return sizeof(g_config.socket_name);
		}
	}
	return -1;
}

/**
 * Getter for the data pool service socket name type.
 *
 * @return int	 0	Socket file
 * @return int	 1	Abstract socket
 */
int get_data_pool_service_socket_name_type(void)
{
	int ret = 0;

	if (g_config.socket_name[0] == '\0')
		ret = 1;

	return ret;
}
