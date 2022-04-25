AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

bin_PROGRAMS = cluster_client

cluster_client_SOURCES = \
		cluster-service-util.c \
		data-pool-client.c \
		cluster-client.c 

# options
# Additional library
cluster_client_LDADD = \
		-lrt -lpthread \
		@LIBSYSTEMD_LIBS@ 
		
# C compiler options
cluster_client_CFLAGS = \
		-g \
		-I$(top_srcdir)/include \
		@LIBSYSTEMD_CFLAGS@ \
		-D_GNU_SOURCE

# Linker options
cluster_client_LDFLAGS = 


# configure option 
if ENABLE_ADDRESS_SANITIZER
cluster_client_CFLAGS   += -fsanitize=address
endif

#
#if ENABLE_PRINTFDEBUG
#exsample_CFLAGS   += -D_PRINTF_DEBUG_
#exsample_CXXFLAGS += -D_PRINTF_DEBUG_
#endif

