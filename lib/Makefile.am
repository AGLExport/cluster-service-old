AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

noinst_LIBRARIES = libcluster_service_common.a

libcluster_service_common_a_SOURCES = \
		cluster-service-util.c

libcluster_service_common_a_CFLAGS = \
		-g \
		-I$(top_srcdir)/include \
		@LIBSYSTEMD_CFLAGS@ \
		-D_GNU_SOURCE


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

