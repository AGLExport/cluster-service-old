#!/bin/sh

complexity --histogram --score --thresh=3 \
	src/cluster-service.c \
	src/data-pool-service.c \
	src/data-pool-service.h \
	src/ipc_protocol.h

