AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = cluster_service ms_client

cluster_service_SOURCES = \
		data-pool-service.c \
		cluster-service.c 

# options
# Additional library
cluster_service_LDADD = \
		$(top_srcdir)/lib/libcluster_service_common.a \
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



ms_client_SOURCES = \
		ms_client.c 

# options
# Additional library
ms_client_LDADD = \
		-lrt -lpthread \
		@LIBSYSTEMD_LIBS@

# C compiler options
ms_client_CFLAGS = \
		-g \
		-I$(top_srcdir)/include \
		@LIBSYSTEMD_CFLAGS@ \
		-D_GNU_SOURCE

# Linker options
ms_client_LDFLAGS = 


# configure option 
if ENABLE_ADDRESS_SANITIZER
cluster_service_CFLAGS   += -fsanitize=address
endif

#
#if ENABLE_PRINTFDEBUG
#exsample_CFLAGS   += -D_PRINTF_DEBUG_
#exsample_CXXFLAGS += -D_PRINTF_DEBUG_
#endif

