#ifndef UT_LIBYAPLOG_H_SHF9IC0C
#define UT_LIBYAPLOG_H_SHF9IC0C

#include "yaplog.h"

#include <CppUTest/TestHarness.h>
#include <sstream>
#include <cstdlib>
#include <cstring>

#include <unistd.h>

using namespace logger;

TEST_GROUP(internallog)
{
    void setup()
    {
        my_real_stream = new std::ostringstream();
    };

    void teardown()
    {
    };

    std::ostringstream *my_real_stream;
};

TEST(internallog, dynamicallocation)
{
    InternalLog *log = new InternalLog(log_level::alert,
                                       log_location("function2", "file2", 38),
                                       my_real_stream);


    STRCMP_EQUAL("[A] file2:38(function2) ",
                 my_real_stream->str().c_str());

    delete log;
};

TEST(internallog, withdata)
{
    InternalLog *log = new InternalLog(log_level::alert,
                                       log_location("function2", "file2", 38),
                                       my_real_stream);

    (*log) << "Test with string";

    STRCMP_EQUAL("[A] file2:38(function2) Test with string",
                 my_real_stream->str().c_str());

    delete log;
};

TEST_GROUP(customout)
{
    const char *destination = "unittests_customout.log";
    void setup()
    {
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
        unlink(destination);
    }

    void teardown()
    {
        unlink(destination);
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
    }

    void check_file_content(const char *file)
    {
        FILE *f = fopen(file, "rb");
        if (f != NULL) {
            if (expected.size() != 0) {
                char *content = new char[expected.size() + 1];
                memset(content, 0, expected.size() + 1);
                UNSIGNED_LONGS_EQUAL(1, fread(content, expected.size(), 1, f));
                MEMCMP_EQUAL(expected.c_str(), content, expected.size());
                delete [] content;
            }

            char extra[1024] = { };
            size_t ret = fread(extra, 1, 1024, f);
            if (ret != 0) {
                FAIL(extra);
            }
            UNSIGNED_LONGS_EQUAL(0, ret);
            fclose(f);
        } else {
            UNSIGNED_LONGS_EQUAL(0, expected.size());
        }
    }


    void init(const char *level) {
        setenv("LOGDESTINATION", destination, 1);
        setenv("LOGLEVEL", level, 1);
    }

    std::string expected;
};

#define givelog(level) InternalLog(level, \
                                   log_location("function2", "file2", 38), \
                                   InternalLog::getOstream(), \
                                   InternalLog::getSystemLevel())


TEST(customout, nothing)
{
    FLOG() << "Fatal";
    ALOG() << "Alert";
    CLOG() << "Crit";
    ELOG() << "Error";
    WLOG() << "Warning";
    NLOG() << "Notice";
    ILOG() << "Info";
    DLOG() << "Debug";
    TLOG() << "Trace";

    expected = std::string("");
    check_file_content(destination);
};

TEST(customout, file_invalidlevel)
{
    init("failure");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("");
    check_file_content(destination);
};

TEST(customout, file_levelnone)
{
    init("0");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("");
    check_file_content(destination);
};

TEST(customout, file_levelnegative)
{
    init("-1");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("");
    check_file_content(destination);
};

TEST(customout, file_levelfatal)
{
    init("1");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n");
    check_file_content(destination);
};

TEST(customout, file_levelalert)
{
    init("2");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n");
    check_file_content(destination);
};

TEST(customout, file_levelcrit)
{
    init("3");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_levelerror)
{
    init("4");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_levelwarn)
{
    init("5");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_levelnotice)
{
    init("6");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_levelinfo)
{
    init("7");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_leveldebug)
{
    init("8");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                           "[D] file2:38(function2) Debug\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_leveltrace)
{
    init("9");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                           "[D] file2:38(function2) Debug\n"
                           "[T] file2:38(function2) Trace\n"
                          );
    check_file_content(destination);
};

TEST(customout, file_levelgreater)
{
    init("10");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                           "[D] file2:38(function2) Debug\n"
                           "[T] file2:38(function2) Trace\n"
                          );
    check_file_content(destination);
};

TEST_GROUP(stdoutlog)
{
    void setup()
    {
        setenv("LOGDESTINATION", "stdout", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
    }
};

TEST(stdoutlog, alllogs)
{
    FLOG() << "Fatal";
    ALOG() << "Alert";
    CLOG() << "Crit";
    ELOG() << "Error";
    WLOG() << "Warning";
    NLOG() << "Notice";
    ILOG() << "Info";
    DLOG() << "Debug";
    TLOG() << "Trace";
};

TEST_GROUP(stderrlog)
{
    void setup()
    {
        setenv("LOGDESTINATION", "stderr", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
    }
};

TEST(stderrlog, alllogs)
{
    FLOG() << "Fatal";
    ALOG() << "Alert";
    CLOG() << "Crit";
    ELOG() << "Error";
    WLOG() << "Warning";
    NLOG() << "Notice";
    ILOG() << "Info";
    DLOG() << "Debug";
    TLOG() << "Trace";
};

TEST_GROUP(invalidfilelog)
{
    void setup()
    {
        setenv("LOGDESTINATION", "/probablynotexisting/path/to/a/logfile", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
    }
};

TEST(invalidfilelog, alllogs)
{
    FLOG() << "Fatal";
    ALOG() << "Alert";
    CLOG() << "Crit";
    ELOG() << "Error";
    WLOG() << "Warning";
    NLOG() << "Notice";
    ILOG() << "Info";
    DLOG() << "Debug";
    TLOG() << "Trace";
};


#endif /* end of include guard: UT_LIBYAPLOG_H_SHF9IC0C */
