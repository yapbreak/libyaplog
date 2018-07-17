ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

SUBDIRS = yaplog

lib_LTLIBRARIES = libyaplog.la
libyaplog_la_SOURCES  = yaplog.h
libyaplog_la_SOURCES += yaplog.cpp
libyaplog_la_LIBADD = yaplog/libinternalyaplog.la
libyaplog_la_LDFLAGS = $(LIBVERSION)

include_HEADERS = yaplog.h

libyaplogextradir = $(prefix)/lib/pkgconfig
libyaplogextra_DATA = yaplog.pc
