/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service.c
 * @brief	data service provider
 */

#include "data-pool-static-configurator.h"
#include "ipc_protocol.h"
#include "data-pool-client.h"

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>

/** data pool service session list */
struct s_data_pool_session {
	struct s_data_pool_session *next; /**< pointer to next session*/
	sd_event_source *
		socket_evsource; /**< UNIX Domain socket event source for data pool service */
};

/** data pool client handles */
struct s_data_pool_client {
	sd_event *parent_eventloop; /**< UNIX Domain socket event source for data pool service */
	sd_event_source *
		socket_evsource; /**< UNIX Domain socket event source for data pool service */
};
typedef struct s_data_pool_client *data_pool_client_handle;

AGLCLUSTER_SERVICE_PACKET packet;

/**
 * Data pool message passenger
 *
 * @param [in]	dp			data pool service handle
* @return int	 >0 success (num of passanged sessions)
 *				-1 internal error
 *				-2 argument error
 */
/*static int data_pool_message_passanger(data_pool_service_handle dp)
{
	struct s_data_pool_session *listp = NULL;
	int fd = -1;
	ssize_t ret = -1;
	int result = -1;

	packet.header.seqnum++;

	if (dp == NULL)
		return -2;

	result = 0;

	if (dp->session_list != NULL) {
		listp = dp->session_list;

		for (int i = 0; i < DATA_POOL_SERVICE_SESSION_LIMIT; i++) {
			fd = sd_event_source_get_io_fd(listp->socket_evsource);
			ret = write(fd, &packet, sizeof(packet));
			if (ret < 0) {
				if (errno == EINTR)
					continue;
				// When socket buffer is full (EAGAIN), this write is pass..
				// When socket return other error, it will handle in socket fd event handler.
			}
			result = result + 1;

			if (listp->next != NULL) {
				listp = listp->next;
			} else {
				break;
			}
		}
		//Force loop out 
		result = -1;
	}

	return result;
}*/

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
static int data_pool_sessions_handler(sd_event_source *event, int fd,
				      uint32_t revents, void *userdata)
{
	sd_event_source *socket_source = NULL;
	data_pool_client_handle dp = (data_pool_client_handle)userdata;
	int sessionfd = -1;
	int ret = -1;
	ssize_t sret = -1;

	if ((revents & (EPOLLHUP | EPOLLERR)) != 0) {
		// Disconnect session

		if (dp != NULL) {
			dp->socket_evsource =
				sd_event_source_disable_unref(dp->socket_evsource);
		} else {
			// Arg error or end of list or loop limit,
			// Tihs event is not include session list. Faile safe it unref.
			sd_event_source_disable_unref(event);
		}
	} else if ((revents & EPOLLIN) != 0) {
		// Receive
		sret = read(fd, &packet,sizeof(packet));
		fprintf(stderr,"rcv size = %ld (req: %ld) seqnum=%lx\n", sret, sizeof(packet), packet.header.seqnum);
		ret = 0;
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
int data_pool_client_setup(sd_event *event, data_pool_client_handle *handle)
{
	sd_event_source *socket_source = NULL;
	struct sockaddr_un name;
	struct s_data_pool_client *dp = NULL;
	int sasize = -1;
	int fd = -1;
	int ret = -1;

	if (event == NULL || handle == NULL)
		return -2;

	dp = (struct s_data_pool_client *)malloc(sizeof(struct s_data_pool_client));
	if (dp == NULL) {
		ret = -1;
		goto err_return;
	}

	memset(dp, 0, sizeof(*dp));

	dp->parent_eventloop = event;

	// Create client socket
	fd = socket(AF_UNIX, SOCK_SEQPACKET | SOCK_CLOEXEC | SOCK_NONBLOCK,
		    AF_UNIX);
	if (fd < 0) {
		ret = -1;
		goto err_return;
	}

	memset(&name, 0, sizeof(name));

	name.sun_family = AF_UNIX;
	sasize = get_data_pool_service_socket_name(name.sun_path,sizeof(name.sun_path));

	ret = connect(fd, (const struct sockaddr *)&name, sizeof(name));
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}	// TODO EALREADY and EINTR

	ret = sd_event_add_io(event, &socket_source, fd, EPOLLIN,
			      data_pool_sessions_handler, dp);
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
int data_pool_client_cleanup(data_pool_client_handle handle)
{
	struct s_data_pool_client *dp = handle;

	// NULL through
	if (handle == NULL)
		return 0;

	(void)sd_event_source_disable_unref(dp->socket_evsource);

	free(dp);

	return 0;
}
