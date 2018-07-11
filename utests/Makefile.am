ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/utests/Makefile.test.common

SUBDIRS = fixtures

TESTS = ut_libyaplog.xtest

noinst_PROGRAMS = $(TESTS)

check_PROGRAMS = $(TESTS)

ut_libyaplog_xtest_SOURCES  = ut_libyaplog.h
ut_libyaplog_xtest_SOURCES += main.cpp
ut_libyaplog_xtest_CFLAGS = $(TESTCFLAGS)
ut_libyaplog_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_libyaplog_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_libyaplog_xtest_LDADD  = $(top_builddir)/src/libyaplog.la
ut_libyaplog_xtest_LDADD += $(top_builddir)/utests/fixtures/libfixtures.la
