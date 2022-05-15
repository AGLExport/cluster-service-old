AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = \
	cluster_service_util_test data_pool_service_test_socket data_pool_service_test_timer \
	data_pool_service_test_init \
	cluster_api_test_telltale cluster_api_test_trip 


cluster_service_util_test_SOURCES = \
	cluster-service-util-test.cpp 

data_pool_service_test_socket_SOURCES = \
	data-pool-service-test-socket.cpp 

data_pool_service_test_timer_SOURCES = \
	data-pool-service-test-timer.cpp 

data_pool_service_test_init_SOURCES = \
	data-pool-service-test-init.cpp 

cluster_api_test_telltale_SOURCES = \
	cluster-api-test-telltale.cpp

cluster_api_test_trip_SOURCES = \
	cluster-api-test-trip.cpp

# options
# Additional library
LDADD = \
	-lrt -lpthread \
	@GTEST_MAIN_LIBS@ \
	@GMOCK_MAIN_LIBS@ 

data_pool_service_test_socket_LDADD = \
	${LDADD} \
	$(top_srcdir)/lib/libcluster_service_common.a \
	$(top_srcdir)/lib/libcluster_service_static_configurator.a

data_pool_service_test_timer_LDADD = \
	${LDADD} \
	$(top_srcdir)/lib/libcluster_service_common.a \
	$(top_srcdir)/lib/libcluster_service_static_configurator.a

data_pool_service_test_init_LDADD = \
	${LDADD} \
	$(top_srcdir)/lib/libcluster_service_common.a
	
# C compiler options
CFLAGS = \
	-g \
	-fsanitize=address -coverage \
	-I$(top_srcdir)/lib \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	@GTEST_MAIN_CFLAGS@ \
	@GMOCK_MAIN_CFLAGS@ \
	-D_GNU_SOURCE

# C++ compiler options
CXXFLAGS = \
	-g \
	-std=c++11 -fno-exceptions \
	-fsanitize=address -coverage \
	-I$(top_srcdir)/lib \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	@GTEST_MAIN_CFLAGS@ \
	@GMOCK_MAIN_CFLAGS@ \
	-D_GNU_SOURCE


# Linker options
LDFLAGS = 


CLEANFILES = *.gcda *.gcno
