/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	demo-data-generator.c
 * @brief	demo data generator for cluster service
 */

#include "demo-data-generator.h"
#include "data-pool.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct s_demo_data_timer {
	sd_event_source *timer_evsource; /**< Timer event source */
	uint64_t timerval;		 /**< Timer counter */
	uint64_t demo_count;		 /** demo event counter */
};

static struct s_demo_data_timer g_demo_timer;

const uint64_t g_demo_data_update_interval = 10 * 1000; // usec


static void do_demo(void)
{
	// trip
	{
		data_pool_set_trcom_trip_a_val(data_pool_get_trcom_trip_a_val() + 1);
	}

	// speed
	{
		if ((g_demo_timer.demo_count % 500) < 400) {
			if (((g_demo_timer.demo_count / 500) % 2) == 0) {
				data_pool_set_speed_analog_val(data_pool_get_speed_analog_val() + 50);
			} else {
				data_pool_set_speed_analog_val(data_pool_get_speed_analog_val() - 50);
			}
		}
	}

	// Telltale
	{
		if (((g_demo_timer.demo_count / 300) % 4) == 1) {
			if ((g_demo_timer.demo_count % 30) == 1) {

				if (data_pool_get_turn_r() == IC_HMI_ON)
					data_pool_set_turn_r(IC_HMI_OFF);
				else
					data_pool_set_turn_r(IC_HMI_ON);


				if (data_pool_get_front_right_seatbelt() == IC_HMI_ON)
					data_pool_set_front_right_seatbelt(IC_HMI_OFF);
				else 
					data_pool_set_front_right_seatbelt(IC_HMI_ON);

				if (data_pool_get_front_left_seatbelt() == IC_HMI_ON)
					data_pool_set_front_left_seatbelt(IC_HMI_OFF);
				else
					data_pool_set_front_left_seatbelt(IC_HMI_ON);
			}
		}

		if (((g_demo_timer.demo_count / 300) % 4) == 3) {
			if ((g_demo_timer.demo_count % 30) == 1) {

				if (data_pool_get_turn_l() == IC_HMI_ON)
					data_pool_set_turn_l(IC_HMI_OFF);
				else
					data_pool_set_turn_l(IC_HMI_ON);
			}
		}
	}

	g_demo_timer.demo_count++;
}
/**
 * TImer handler for data pool passenger
 *
 * @param [in]	es	sd event source
 * @param [in]	usec	callback time (MONOTONIC time)
 * @param [in]	userdata	Pointer to g_demo_timer
 * @return int	 0 success
 *				-1 internal error (timer stop)
 */
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

/**
 * Setup function for demo data generator
 *
 * @param [in]	event	sd event loop handle
 * @return int	 0 success
 *				-1 internal error
 *				-2 argument error
 */
int demo_data_generator_setup(sd_event *event)
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
	g_demo_timer.timerval = timerval + 1 * 1000 * 1000;
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

/**
 * Cleanup function for demo data generator
 *
 * @param [in]	handle	Return pointer to data pool service handle.
 * @return int	 0 success
 */
int demo_data_generator_cleanup(void)
{
	(void) sd_event_source_disable_unref(g_demo_timer.timer_evsource);

	return 0;
}
