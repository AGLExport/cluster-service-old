SUBDIRS = lib src example

if ENABLE_TEST
SUBDIRS += test
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = cluster_api.pc cluster-api-systemd.pc

CLEANFILES = cluster_api.pc cluster-api-systemd.pc

include_HEADERS = \
    include/cluster_api.h \
    include/cluster_api_speed.h \
    include/cluster_api_tripcomputer.h \
    include/cluster_api_registernotify.h  \
    include/cluster_api_tacho.h \
    include/cluster_api_shiftposition.h \
    include/cluster_api_telltale.h \
    lib/cluster-api-sdevent.h
