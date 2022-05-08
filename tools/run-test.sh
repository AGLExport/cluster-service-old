#!/bin/sh -e

./test/cluster_service_util_test
./test/data_pool_service_test_socket
./test/data_pool_service_test_timer
./test/data_pool_service_test_init
./test/cluster_api_test

