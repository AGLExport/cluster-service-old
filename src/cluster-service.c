/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.c
 * @brief	main source file for cluster-service
 */

#include "data-pool-service.h"

#include <stdlib.h>
#include <systemd/sd-daemon.h>
#include <systemd/sd-event.h>

#include <stdio.h>

/**
 * Sub function for UNIX signal handling.
 * Block SIGTERM, when this process receive SIGTERM, event loop will exit.
 *
 * @param [in]	event	第一引数の説明
 * @return int	 0 success
 * 				-2 argument error
 *				-1 internal error
 */
int signal_setup(sd_event *event)
{
	sigset_t ss;
	int ret = -1;

	if (event == NULL)
		return -2;

	// If the correct arguments are given, these function will never fail.
	(void)sigemptyset(&ss);
	(void)sigaddset(&ss, SIGTERM);

	// Block SIGTERM
	ret = pthread_sigmask(SIG_BLOCK, &ss, NULL);
	if (ret < 0)
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

int main(int argc, char *argv[])
{
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
	ret = sd_event_set_watchdog(event, 1);
	if (ret < 0)
		goto finish;

	ret = data_pool_service_setup(event, &handle);

	(void)sd_notify(1,
			"READY=1\n"
			"STATUS=Daemon startup completed, processing events.");
	ret = sd_event_loop(event);

finish:
	(void)data_pool_service_cleanup(handle);
	event = sd_event_unref(event);

	return ret < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
