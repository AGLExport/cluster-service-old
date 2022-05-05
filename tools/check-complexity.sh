#!/bin/sh

complexity --histogram --score --thresh=3 \
	src/cluster-service.c \
	src/data-pool-service.c \
	src/data-pool-service.h \
	\
	lib/cluster-api-core.c \
	lib/cluster-api-sdevent.c \
	lib/data-pool.c \
	lib/data-pool-static-configurator.c \
	lib/cluster-api-glib.c \
	lib/cluster-service-util.c \
	lib/data-pool-client.c \
	lib/cluster_api_internal.h \
	lib/cluster-service-util.h \
	lib/data-pool.h \
	lib/data-pool-storage.h \
	lib/cluster-api-sdevent.h \
	lib/data-pool-client.h \
	lib/data-pool-static-configurator.h \
	\
	example/cluster-client.c \
	\
	include/cluster_api.h \
	include/cluster_api_speed.h \
	include/cluster_api_tripcomputer.h \
	include/cluster_api_registernotify.h  \
	include/cluster_api_tacho.h \
	include/config.h \
	include/cluster_api_shiftposition.h \
	include/cluster_api_telltale.h \
	include/ipc_protocol.h
	


