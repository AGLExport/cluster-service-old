/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service.c
 * @brief	data service provider
 */

#include "cluster-api-sdevent.h"
#include "cluster_api.h"
#include "data-pool-client.h"
#include "data-pool-static-configurator.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>

/** data pool service session list */
struct s_data_pool_session {
	struct s_data_pool_session *next; /**< pointer to next session*/
	sd_event_source *socket_evsource; /**< UNIX Domain socket event source for data pool service */
};

/** data pool client handles */
struct s_data_pool_client_sdevent {
	sd_event *parent_eventloop;	  /**< UNIX Domain socket event source for data pool service */
	sd_event_source *socket_evsource; /**< UNIX Domain socket event source for data pool service */
};
typedef struct s_data_pool_client_sdevent *data_pool_client_handle_sdevent;

/**
 * Event handler for server session socket
 *
 * @param [in]	event		Socket event source object
 * @param [in]	fd			File discriptor for socket session
 * @param [in]	revents		Active event (epooll)
 * @param [in]	userdata	Pointer to data_pool_service_handle
 * @return int	 0 success
 *				-1 internal error
 */
static int data_pool_sessions_handler(sd_event_source *event, int fd, uint32_t revents, void *userdata)
{
	sd_event_source *socket_source = NULL;
	data_pool_client_handle_sdevent dp = (data_pool_client_handle_sdevent) userdata;
	int sessionfd = -1;
	int ret = -1;
	ssize_t sret = -1;

	if ((revents & (EPOLLHUP | EPOLLERR)) != 0) {
		// Disconnect session

		if (dp != NULL) {
			dp->socket_evsource = sd_event_source_disable_unref(dp->socket_evsource);
		} else {
			// Arg error or end of list or loop limit,
			// Tihs event is not include session list. Faile safe it unref.
			sd_event_source_disable_unref(event);
		}
	} else if ((revents & EPOLLIN) != 0) {
		// Receive
		ret = data_pool_receive(fd);
	}

	return ret;
}

/**
 * Function for data pool passenger setup
 *
 * @param [in]	event	sd event loop handle
 * @param [out]	handle	Return pointer for data pool service handle.
 * @return int	 0 success
 *				-1 internal error
 *				-2 argument error
 */
int data_pool_client_setup_sdevent(sd_event *event, data_pool_client_handle_sdevent *handle)
{
	sd_event_source *socket_source = NULL;
	struct sockaddr_un name;
	struct s_data_pool_client_sdevent *dp = NULL;
	int sasize = -1;
	int fd = -1;
	int ret = -1;

	if (event == NULL || handle == NULL)
		return -2;

	dp = (struct s_data_pool_client_sdevent *) malloc(sizeof(struct s_data_pool_client_sdevent));
	if (dp == NULL) {
		ret = -1;
		goto err_return;
	}

	memset(dp, 0, sizeof(*dp));

	dp->parent_eventloop = event;

	// Create client socket
	fd = socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK, AF_UNIX);
	if (fd < 0) {
		ret = -1;
		goto err_return;
	}

	memset(&name, 0, sizeof(name));

	name.sun_family = AF_UNIX;
	sasize = get_data_pool_service_socket_name(name.sun_path, sizeof(name.sun_path));

	ret = connect(fd, (const struct sockaddr *) &name, sasize + sizeof(sa_family_t));
	if (ret < 0) {
		ret = -1;
		goto err_return;
	} // TODO EALREADY and EINTR

	ret = sd_event_add_io(event, &socket_source, fd, EPOLLIN, data_pool_sessions_handler, dp);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}

	// Set automatically fd closen at delete object.
	ret = sd_event_source_set_io_fd_own(socket_source, 1);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}

	// After the automaticall fd close settig shall not close fd in error path
	fd = -1;

	dp->socket_evsource = socket_source;

	clusterInit();
	(*handle) = dp;

	return 0;

err_return:
	socket_source = sd_event_source_disable_unref(socket_source);
	free(dp);
	if (fd != -1)
		close(fd);

	return ret;
}

/**
 * Function for data pool passenger cleanup
 *
 * @param [in]	handle	Return pointer to data pool service handle.
 * @return int	 0 success
 */
int data_pool_client_cleanup_sdevent(data_pool_client_handle_sdevent handle)
{
	struct s_data_pool_client_sdevent *dp = handle;

	// NULL through
	if (handle == NULL)
		return 0;

	clusterTerm();

	(void) sd_event_source_disable_unref(dp->socket_evsource);

	free(dp);

	return 0;
}
