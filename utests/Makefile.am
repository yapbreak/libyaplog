ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/utests/Makefile.test.common

SUBDIRS = fixtures

TESTS = ut_libyaplog.xtest

check_PROGRAMS = $(TESTS)

ut_libyaplog_xtest_SOURCES  = ut_libyaplog.h
ut_libyaplog_xtest_SOURCES += ut_conf.h
ut_libyaplog_xtest_SOURCES += ut_dump.h
ut_libyaplog_xtest_SOURCES += main.cpp
ut_libyaplog_xtest_CFLAGS = $(TESTCFLAGS) -include $(TEST_ROOT)/fixtures/fixtures.h
ut_libyaplog_xtest_CXXFLAGS = $(TESTCXXFLAGS) -include $(TEST_ROOT)/fixtures/fixtures.h
ut_libyaplog_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_libyaplog_xtest_LDADD  = $(top_builddir)/src/libyaplog.la
ut_libyaplog_xtest_LDADD += $(top_builddir)/utests/fixtures/libfixtures.la
