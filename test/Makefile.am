AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = cluster_service_util_test data_pool_service_test

cluster_service_util_test_SOURCES = \
		cluster-service-util-test.cpp 

data_pool_service_test_SOURCES = \
		data-pool-service-test.cpp 

# options
# Additional library
LDADD = \
		$(top_srcdir)/lib/libcluster_service_common.a \
		-lrt -lpthread \
		@GTEST_MAIN_LIBS@ \
		@GMOCK_MAIN_LIBS@ 

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
		-std=c++11 \
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
