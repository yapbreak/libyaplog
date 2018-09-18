ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

noinst_LTLIBRARIES = libinternalyaplog.la
libinternalyaplog_la_SOURCES  = dump.h
libinternalyaplog_la_SOURCES += dump.cpp
libinternalyaplog_la_SOURCES += color.h
libinternalyaplog_la_SOURCES += conf.h
libinternalyaplog_la_SOURCES += conf.cpp
libinternalyaplog_la_SOURCES += internallog.h
libinternalyaplog_la_SOURCES += internallog.cpp
libinternalyaplog_la_SOURCES += level.h
libinternalyaplog_la_SOURCES += loglocation.h

yaplogdir = $(includedir)/yaplog
yaplog_HEADERS = conf.h dump.h internallog.h level.h loglocation.h
