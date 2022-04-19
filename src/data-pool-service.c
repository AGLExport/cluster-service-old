﻿/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	data-pool-service.c
 * @brief	data service provider
 */

#include "ipc_protocol.h"
#include "data-pool-service.h"

#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>

#define SOCKET_NAME "/tmp/cluster-service.socket"

// Internal limitation for datapool service sessions. It use link list search limit.
#define DATA_POOL_SERVICE_SESSION_LIMIT		(1000)


/** data pool service session list */
struct s_data_pool_session {
	struct s_data_pool_session *next;	/**< pointer to next session*/
	sd_event_source *socket_evsource;	/**< UNIX Domain socket event source for data pool service */
};

/** data pool service handles */
struct s_data_pool_service {
	sd_event *parent_eventloop;			/**< UNIX Domain socket event source for data pool service */
	sd_event_source *socket_evsource;	/**< UNIX Domain socket event source for data pool service */
	sd_event_source *timer_evsource;	/**< Timer event source for data pool service  */
	struct s_data_pool_session *session_list;
};
typedef struct s_data_pool_service *data_pool_service_handle;


AGLCLUSTER_SERVICE_PACKET packet;

/**
 * Data pool message passenger
 *
 * @param [in]	dp			data pool service handle
 * @return int	 0 success
 *				-1 internal error
 *				-2 argument error
 */
static int data_pool_message_passanger(data_pool_service_handle dp) {
	struct s_data_pool_session *listp = NULL;
	int fd = -1;
	int ret = -1;
	
	packet.header.seqnum++;
	
	if (dp == NULL)
		return -2;
	
	if (dp->session_list != NULL) {
		listp = dp->session_list;
		
		for(int i=0; i < DATA_POOL_SERVICE_SESSION_LIMIT;i++) {
			fd = sd_event_source_get_io_fd(listp->socket_evsource);
			ret = write(fd, &packet, sizeof(packet));
			if (ret < 0) {
				if (errno == EINTR)
					continue;
				// When socket buffer is full (EAGAIN), this write is pass..
				// When socket return other error, it will handle in socket fd event handler.
			}
			
			if (listp->next != NULL) {
				listp = listp->next;
			} else {
				break;
			}
		}
	}
	
	return 0;
}

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
static int data_pool_sessions_handler(sd_event_source *event, int fd, uint32_t revents, void *userdata) {
	sd_event_source *socket_source = NULL;
	data_pool_service_handle dp = (data_pool_service_handle)userdata;
	struct s_data_pool_session *privp = NULL;
	struct s_data_pool_session *listp = NULL;
	int sessionfd = -1;
	int ret = -1;
	
	if ((revents & (EPOLLHUP | EPOLLERR)) != 0) {
		// Disconnect session
		
		if (dp->session_list != NULL) {
			listp = dp->session_list;
			for(int i=0; i < DATA_POOL_SERVICE_SESSION_LIMIT;i++) {
				if (listp->socket_evsource == event) {
					if (privp == NULL) {
						dp->session_list = listp->next;
					} else {
						privp->next = listp->next;
					}
					listp->socket_evsource = sd_event_source_disable_unref(listp->socket_evsource);
					free(listp);
					break;
				}
				privp = listp;
				listp = listp->next;
			}
		} else {
			sd_event_source_disable_unref(event);
		}
		fprintf(stderr,"Client disconnect\n");
		return -1;
	}
	if ((revents & EPOLLIN) != 0) {
		// Receive
		
		//TODO
	}

	return 0;
}

/**
 * Event handler for server socket to use incoming event
 *
 * @param [in]	event		Socket event source object
 * @param [in]	fd			File discriptor for socket session
 * @param [in]	revents		Active event (epooll)
 * @param [in]	userdata	Pointer to data_pool_service_handle
 * @return int	 0 success
 *				-1 internal error
 */
static int data_pool_incoming_handler(sd_event_source *event, int fd, uint32_t revents, void *userdata) {
	//sd_event_source *socket_source = NULL;
	data_pool_service_handle dp = (data_pool_service_handle)userdata;
	struct s_data_pool_session *session = NULL;
	struct s_data_pool_session *listp = NULL;
	int sessionfd = -1;
	int ret = -1;
	
	if ((revents & (EPOLLHUP | EPOLLERR)) != 0) {
		// False safe: Disavle server socket
		if (dp != NULL) {
			dp->socket_evsource = sd_event_source_disable_unref(dp->socket_evsource);
		}
		fprintf(stderr,"Server connection error\n");
		return -1;
	}
	if ((revents & EPOLLIN) != 0) {
		// New session
		sessionfd = accept4(fd, NULL, NULL,SOCK_NONBLOCK|SOCK_CLOEXEC);
		if (sessionfd == -1) {
			perror("accept");
			return -1;
		}
		
		if (dp == NULL) {
			close(sessionfd);
			return -1;
		}
		
		session = malloc(sizeof(struct s_data_pool_session));
		if (session == NULL) {
			close(sessionfd);
			return -1;
		}
		session->next = NULL;
		
		ret = sd_event_add_io(	dp->parent_eventloop,
								&session->socket_evsource, 
								sessionfd, 
								(EPOLLIN | EPOLLHUP | EPOLLERR ),
								data_pool_sessions_handler,
								dp);
		if (ret < 0) {
			free(session);
			close(sessionfd);
			return -1;
		}
		
		// Set automatically fd closen at delete object.
		ret = sd_event_source_set_io_fd_own(session->socket_evsource, 1);
		if (ret < 0) {
			free(session);
			close(sessionfd);
			return -1;
		}
		
		
		if (dp->session_list == NULL) {
			// 1st session
			dp->session_list = session;
		} else {
			listp = dp->session_list;
			for(int i=0; i < 1000;i++) {
				if (listp->next == NULL) {
					listp->next = session;
					break;
				}
			}
		}
	}
	fprintf(stderr,"connect\n");

	return 0;
}

static uint64_t timerval=0;
int g_count = 0;
static int timer_handler(sd_event_source *es, uint64_t usec, void *userdata) {
	data_pool_service_handle dp = (data_pool_service_handle)userdata;
	int ret = -1;
	
	if ((usec - timerval) > 10) {
		fprintf(stderr,"timer event sch=%ld  real=%ld\n", timerval,usec);
	}
	timerval = timerval + 10*1000;
	ret = sd_event_source_set_time(es, timerval);
	if (ret < 0) {
		return -1;
	}
	
	(void)data_pool_message_passanger(dp);
	
	return 0;
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
int data_pool_service_setup(sd_event *event, data_pool_service_handle *handle) {
	sd_event_source *socket_source = NULL;
	sd_event_source *timer_source = NULL;
	struct sockaddr_un name;
	struct s_data_pool_service *dp = NULL;
	int fd = -1;
	int ret = -1;
	
	if (event == NULL || handle ==NULL)
		return -2;

	// unlink existing sicket file.
	unlink(SOCKET_NAME);

	dp = malloc(sizeof(struct s_data_pool_service));
	if (dp == NULL) {
		ret = -1;
		goto err_return;
	}
	
	memset(dp, 0, sizeof(*dp));
	
	dp->parent_eventloop = event;
	
	// Create server socket.
	fd = socket(AF_UNIX, SOCK_SEQPACKET|SOCK_CLOEXEC|SOCK_NONBLOCK, AF_UNIX);
	if (fd < 0) {
		ret = -1;
		goto err_return;
	}

	memset(&name, 0, sizeof(name));

	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
	
	ret = bind(fd, (const struct sockaddr *) &name, sizeof(name));
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}

	ret = listen(fd, 8);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}
	
	ret = sd_event_add_io(event, &socket_source, fd, EPOLLIN, data_pool_incoming_handler, dp);
	if (ret < 0){
		ret = -1;
		goto err_return;
	}
	
	// Set automatically fd closen at delete object.
	ret = sd_event_source_set_io_fd_own(socket_source, 1);
	if (ret < 0){
		ret = -1;
		goto err_return;
	}
	
	// After the automaticall fd close settig shall not close fd in error path
	fd = -1;
	
	dp->socket_evsource = socket_source;
	
	// Notification timer setup
	ret = sd_event_now(event, CLOCK_MONOTONIC, &timerval);
	timerval = timerval + 1*1000*1000;
	ret = sd_event_add_time(event,
							&timer_source,
							CLOCK_MONOTONIC,
							timerval, //triger time (usec)
							1*1000,	//accuracy (1000usec)
 							timer_handler,
							dp);
	if (ret < 0){
		ret = -1;
		goto err_return;
	}

	dp->timer_evsource = timer_source;
	
	ret = sd_event_source_set_enabled(timer_source,SD_EVENT_ON);
	if (ret < 0){
		ret = -1;
		goto err_return;
	}
	
	(*handle) = dp;
	
	return 0;
	
err_return:
	timer_source = sd_event_source_disable_unref(timer_source);
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
int data_pool_service_cleanup(data_pool_service_handle handle) {
	struct s_data_pool_service *dp = handle;
	struct s_data_pool_session *listp = NULL;
	struct s_data_pool_session *listp_free = NULL;
	
	// NULL through
	if (handle == NULL)
		return 0;
	
	if (dp->session_list != NULL) {
		listp = dp->session_list;
		for(int i=0; i < DATA_POOL_SERVICE_SESSION_LIMIT;i++) {
			listp->socket_evsource = sd_event_source_disable_unref(listp->socket_evsource);
			listp_free = listp;
			listp = listp->next;
			free(listp_free);
			if (listp == NULL)
				break;
		}
	}

	(void)sd_event_source_disable_unref(dp->timer_evsource);
	(void)sd_event_source_disable_unref(dp->socket_evsource);

	free(dp);
	
	return 0;
}