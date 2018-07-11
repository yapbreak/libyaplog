ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libyaplog.la
libyaplog_la_SOURCES  = yaplog.h
libyaplog_la_SOURCES += yaplog.cpp

include_HEADERS = yaplog.h

libyaplogextradir = $(prefix)/lib/pkgconfig
libyaplogextra_DATA = yaplog.pc
