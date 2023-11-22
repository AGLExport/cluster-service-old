AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

# Shared libraries
lib_LTLIBRARIES = libcluster-api-systemd.la

libcluster_api_systemd_la_SOURCES = \
	cluster-api-sdevent.c

libcluster_api_systemd_la_LIBADD = \
	$(top_srcdir)/lib/libcluster_service_client.a \
	$(top_srcdir)/lib/libcluster_service_common.a \
	$(top_srcdir)/lib/libcluster_service_static_configurator.a \
	-lrt -lpthread \
	@LIBSYSTEMD_LIBS@

libcluster_api_systemd_la_CFLAGS = \
	-g -Wall -Wno-unused-but-set-variable \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	-D_GNU_SOURCE


# Internal static libraries
noinst_LIBRARIES = \
	libcluster_service_static_configurator.a \
	libcluster_service_common.a \
	libcluster_service_client.a 

libcluster_service_static_configurator_a_SOURCES = \
	data-pool-static-configurator.c

libcluster_service_static_configurator_a_CFLAGS = \
	-g -Wall -Wno-unused-but-set-variable \
	-fpie \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	-D_GNU_SOURCE


libcluster_service_common_a_SOURCES = \
	data-pool.c

libcluster_service_common_a_CFLAGS = \
	-g -Wall -Wno-unused-but-set-variable \
	-fpie \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	-D_GNU_SOURCE


libcluster_service_client_a_SOURCES = \
	data-pool-client.c \
	cluster-api-core.c

libcluster_service_client_a_CFLAGS = \
	-g -Wall -Wno-unused-but-set-variable \
	-fpie \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	-D_GNU_SOURCE


# configure option 
if ENABLE_ADDRESS_SANITIZER
CFLAGS   += -fsanitize=address
endif

if ENABLE_GCOV
CFLAGS   += -coverage
endif

#lib_LTLIBRARIES = libexsample.la

#libexsample_la_SOURCES = \
#		libexsample-c.c 
#
#libexsample_la_LBSADD = 
#
#libexsample_la_CFLAGS = \
#		-I$(top_srcdir)/include 
#
#libexsample_la_LDFLAGS = 

CLEANFILES = *.gcda *.gcno
