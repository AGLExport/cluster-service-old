AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = cluster_service 

cluster_service_SOURCES = \
	data-pool-service.c \
	cluster-service.c \
	demo-data-generator.c

# options
# Additional library
cluster_service_LDADD = \
	$(top_srcdir)/lib/libcluster_service_common.a \
	$(top_srcdir)/lib/libcluster_service_static_configurator.a \
	-lrt -lpthread \
	@LIBSYSTEMD_LIBS@ 

# C compiler options
cluster_service_CFLAGS = \
	-g \
	-I$(top_srcdir)/lib \
	-I$(top_srcdir)/include \
	@LIBSYSTEMD_CFLAGS@ \
	-D_GNU_SOURCE

# Linker options
cluster_service_LDFLAGS = 


# configure option 
if ENABLE_ADDRESS_SANITIZER
CFLAGS   += -fsanitize=address
endif

if ENABLE_GCOV
CFLAGS   += -coverage
endif


#
#if ENABLE_PRINTFDEBUG
#exsample_CFLAGS   += -D_PRINTF_DEBUG_
#exsample_CXXFLAGS += -D_PRINTF_DEBUG_
#endif

CLEANFILES = *.gcda *.gcno
