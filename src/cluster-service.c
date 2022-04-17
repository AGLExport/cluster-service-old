/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.c
 * @brief	main source file for cluster-service
 */

#include "cluster-service.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <sys/timerfd.h>

#include "ipc_protocol.h"


#define SOCKET_NAME "/tmp/cluster-service.socket"
#define BUFFER_SIZE (1024*64)



#include <alloca.h>
#include <endian.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <systemd/sd-daemon.h>
#include <systemd/sd-event.h>



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
AGLCLUSTER_SERVICE_PACKET packet;

static int data_pool_message_passanger(data_pool_service_handle dp) {
	struct s_data_pool_session *listp = NULL;
	int fd = -1;
	int ret = -1;
	
	packet.header.seqnum++;
	
	if (dp->session_list != NULL) {
		listp = dp->session_list;
		
		for(int i=0; i < 1000;i++) {
			fd = sd_event_source_get_io_fd(listp->socket_evsource);
			ret = write(fd, &packet, sizeof(packet));
			if (ret < 0) {
				//TODO
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
			for(int i=0; i < 1000;i++) {
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
	sd_event_source *socket_source = NULL;
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
 * Sub function for data pool passenger setup
 *
 * @param [in]	event	TODO
 * @param [out]	errcode	TODO
 * @return int	 0 success
 *				-2 argument error
 *				-1 internal error
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

	return -1;
}

/**
 * Sub function for UNIX signal handling.
 * Block SIGTERM, when this process receive SIGTERM, event loop will exit.
 *
 * @param [in]	event	第一引数の説明
 * @return int	 0 success
 * 				-2 argument error
 *				-1 internal error
 */
int signal_setup(sd_event *event) {
	sigset_t ss;
	int ret = -1;
	
	if (event == NULL)
		return -2;
	
	// If the correct arguments are given, these function will never fail.
	(void)sigemptyset(&ss);
	(void)sigaddset(&ss, SIGTERM);
	
	// Block SIGTERM
	ret = pthread_sigmask(SIG_BLOCK, &ss, NULL);
	if ( ret < 0)
		goto err_return;
	
	ret = sd_event_add_signal(event, NULL, SIGTERM, NULL, NULL);
	if (ret < 0) {
		pthread_sigmask(SIG_UNBLOCK, &ss, NULL);
		goto err_return;
	}
	
	return 0;
	
err_return:
	return -1;
}

int main(int argc, char *argv[]) {
	sd_event *event = NULL;
	data_pool_service_handle handle = NULL;
	int ret = -1;
	
	ret = sd_event_default(&event);
	if (ret < 0)
		goto finish;

	ret = signal_setup(event);
	if (ret < 0)
		goto finish;
	
	// Enable automatic service watchdog support
	ret = sd_event_set_watchdog(event, true);
	if (ret < 0)
		goto finish;

	ret = data_pool_service_setup(event, &handle);
	
	
	(void)sd_notify(false,
					"READY=1\n"
					"STATUS=Daemon startup completed, processing events.");

	ret = sd_event_loop(event);

finish:
	event = sd_event_unref(event);

	if (ret < 0)
		fprintf(stderr, "Failure: %s\n", strerror(-ret));

	return ret < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

/*
int main(int argc, char *argv[])
{
	struct sockaddr_un name;
	int down_flag = 0;
	int ret;
	int connection_socket;
	int data_socket;
	int result;
	//char buffer[BUFFER_SIZE];
	AGLCLUSTER_SERVICE_PACKET packet;
	
	int count = 0;
	int sss;
	int bufsize;

	memset(&packet, 0, sizeof(packet));

	
	connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, AF_UNIX);
	if (connection_socket == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	memset(&name, 0, sizeof(name));

	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);


	ret = bind(connection_socket, (const struct sockaddr *) &name, sizeof(name));
	if (ret == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	ret = listen(connection_socket, 20);
	if (ret == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for (;;) {
        data_socket = accept4(connection_socket, NULL, NULL,SOCK_NONBLOCK|SOCK_CLOEXEC);
        if (data_socket == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
		
		bufsize = 0;
		sss = sizeof(bufsize);
		ret = getsockopt(data_socket, SOL_SOCKET, SO_SNDBUF, &bufsize, &sss);
		if (ret == 0)
		{
			fprintf(stderr,"getsockopt %d \n",bufsize);
		} else {
			fprintf(stderr,"setsockopt error \n");
		}
		
		bufsize = BUFFER_SIZE * 4;
		fprintf(stderr,"setsockopt %d \n",bufsize);
		ret = setsockopt(data_socket, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
		if (ret != 0)
		{
			fprintf(stderr,"setsockopt error \n");
		}
		
		bufsize = 0;
		sss = sizeof(bufsize);
		ret = getsockopt(data_socket, SOL_SOCKET, SO_SNDBUF, &bufsize, &sss);
		if (ret == 0)
		{
			fprintf(stderr,"getsockopt %d \n",bufsize);
		} else {
			fprintf(stderr,"setsockopt error \n");
		}
		
		
        result = 0;
        for (;;) {
			packet.header.seqnum++;
        	fprintf(stderr,"send count = %ld,  total buff = %ld\n",packet.header.seqnum,sizeof(packet));
        	ret = write(data_socket, &packet, sizeof(packet));
	        if (ret == -1) {
	            perror("write");
	            //exit(EXIT_FAILURE);
	        	break;
	        }
        	else
        	{
	        	fprintf(stderr,"writed buffer = %d\n",ret);        		
        	}
	    }
	}

	sleep(10);
	
	
    close(connection_socket);

    unlink(SOCKET_NAME);

	return 0;
}
*/
