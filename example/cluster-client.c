/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	cluster-service.c
 * @brief	main source file for cluster-service
 */

#include "cluster-api-sdevent.h"
#include "cluster-service-util.h"
#include "cluster_api.h"

#include <stdlib.h>
#include <systemd/sd-daemon.h>
#include <systemd/sd-event.h>

#include <stdio.h>


struct s_demo_data_timer {
	sd_event_source *timer_evsource; /**< Timer event source */
	uint64_t timerval;		 /**< Timer counter */
	uint64_t demo_count;		 /** demo event counter */
};

static struct s_demo_data_timer g_demo_timer;

const uint64_t g_demo_data_update_interval = 16 * 1000; // usec


static void do_demo(void)
{
	uint32_t speed = 0;
	float fspeed = 0.0f;
	uint32_t tripa = 0, tripb = 0;
	int32_t turn_r = 0;

	speed = getSpAnalogVal();
	tripa = getTrcomTripAVal();
	tripb = getTrcomTripBVal();
	turn_r = (int32_t) getTurnR();

	fspeed = ((float) speed) / 100.0f;

	fprintf(stdout, "Speed %03.2fkm/s  : TripA %1d  TripB %1d : Turen A %1d\r", fspeed, tripa, tripb, turn_r);

	g_demo_timer.demo_count++;
}

static int timer_handler(sd_event_source *es, uint64_t usec, void *userdata)
{
	int ret = -1;

	g_demo_timer.timerval = g_demo_timer.timerval + g_demo_data_update_interval;
	ret = sd_event_source_set_time(es, g_demo_timer.timerval);
	if (ret < 0) {
		return -1;
	}

	do_demo();

	return 0;
}

int demo_data_checker_setup(sd_event *event)
{
	sd_event_source *timer_source = NULL;
	uint64_t timerval = 0;
	int ret = -1;

	if (event == NULL)
		return -2;

	// Notification timer setup
	ret = sd_event_now(event, CLOCK_MONOTONIC, &timerval);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}
	g_demo_timer.timerval = timerval + 128 * 1000;
	ret = sd_event_add_time(
		event,
		&timer_source,
		CLOCK_MONOTONIC,
		g_demo_timer.timerval, // triger time (usec)
		1 * 1000,	       // accuracy (1000usec)
		timer_handler,
		&g_demo_timer);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}

	g_demo_timer.timer_evsource = timer_source;

	ret = sd_event_source_set_enabled(timer_source, SD_EVENT_ON);
	if (ret < 0) {
		ret = -1;
		goto err_return;
	}

	return 0;

err_return:
	timer_source = sd_event_source_disable_unref(timer_source);

	return ret;
}

int demo_data_checker_cleanup(void)
{
	(void) sd_event_source_disable_unref(g_demo_timer.timer_evsource);

	return 0;
}

static void ic_notify(uint64_t signal, IC_HMI_ON_OFF val)
{
	fprintf(stdout, "Signal change notify %016lx , val=%1d\r", signal, val);
}

int main(int argc, char *argv[])
{
	sd_event *event = NULL;
	data_pool_client_handle_sdevent handle = NULL;
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

	ret = data_pool_client_setup_sdevent(event, &handle);
	if (ret < 0)
		goto finish;

	ret = demo_data_checker_setup(event);
	if (ret < 0)
		goto finish;

	(void) registerIcHmi(IC_HMI_TT_TURN_R, ic_notify);
	(void) registerIcHmi(IC_HMI_TT_TURN_L, ic_notify);

	(void) sd_notify(
		1,
		"READY=1\n"
		"STATUS=Daemon startup completed, processing events.");
	ret = sd_event_loop(event);

finish:
	(void) demo_data_checker_cleanup();
	(void) data_pool_client_cleanup_sdevent(handle);
	event = sd_event_unref(event);

	return ret < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
