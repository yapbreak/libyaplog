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
    void setup()
    {
        unsetenv("CSER_LOGDESTINATION");
        unsetenv("CSER_LOGLEVEL");
        unlink("unittests_customout.log");
    }

    void teardown()
    {
        delete flog;
        delete alog;
        delete clog;
        delete elog;
        delete wlog;
        delete nlog;
        delete ilog;
        delete dlog;
        delete tlog;

        check_file_content("unittests_customout.log");
        unlink("unittests_customout.log");
        unsetenv("CSER_LOGDESTINATION");
        unsetenv("CSER_LOGLEVEL");
    }

    void check_file_content(const char *file)
    {
        FILE *f = fopen(file, "rb");
        if (expected.size() != 0) {
            char *content = new char[expected.size() + 1];
            memset(content, 0, expected.size() + 1);
            UNSIGNED_LONGS_EQUAL(1, fread(content, expected.size(), 1, f));
            MEMCMP_EQUAL(expected.c_str(), content, expected.size());
            delete [] content;
        }
        if (f != NULL) {
            char extra[1024] = { };
            size_t ret = fread(extra, 1, 1024, f);
            if (ret != 0) {
                FAIL(extra);
            }
            UNSIGNED_LONGS_EQUAL(0, ret);
            fclose(f);
        }
    }

    void init(const char *level) {
        setenv("CSER_LOGDESTINATION", "unittests_customout.log", 1);
        setenv("CSER_LOGLEVEL", level, 1);
        flog = new InternalLog(log_level::fatal,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        alog = new InternalLog(log_level::alert,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        clog = new InternalLog(log_level::crit,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        elog = new InternalLog(log_level::error,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        wlog = new InternalLog(log_level::warn,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        nlog = new InternalLog(log_level::notice,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        ilog = new InternalLog(log_level::info,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        dlog = new InternalLog(log_level::debug,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
        tlog = new InternalLog(log_level::trace,
                               log_location("function2", "file2", 38),
                               InternalLog::getOstream(),
                               InternalLog::getSystemLevel());
    }

    InternalLog *flog;
    InternalLog *alog;
    InternalLog *clog;
    InternalLog *elog;
    InternalLog *wlog;
    InternalLog *nlog;
    InternalLog *ilog;
    InternalLog *dlog;
    InternalLog *tlog;
    std::string expected;
};

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
};

TEST(customout, file_invalidlevel)
{
    init("failure");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("");
};

TEST(customout, file_levelnone)
{
    init("0");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("");
};

TEST(customout, file_levelnegative)
{
    init("-1");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("");
};

TEST(customout, file_levelfatal)
{
    init("1");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n");
};

TEST(customout, file_levelalert)
{
    init("2");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n");
};

TEST(customout, file_levelcrit)
{
    init("3");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                          );
};

TEST(customout, file_levelerror)
{
    init("4");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                          );
};

TEST(customout, file_levelwarn)
{
    init("5");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                          );
};

TEST(customout, file_levelnotice)
{
    init("6");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                          );
};

TEST(customout, file_levelinfo)
{
    init("7");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                          );
};

TEST(customout, file_leveldebug)
{
    init("8");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

    expected = std::string("[F] file2:38(function2) Fatal\n"
                           "[A] file2:38(function2) Alert\n"
                           "[C] file2:38(function2) Crit\n"
                           "[E] file2:38(function2) Error\n"
                           "[W] file2:38(function2) Warning\n"
                           "[N] file2:38(function2) Notice\n"
                           "[I] file2:38(function2) Info\n"
                           "[D] file2:38(function2) Debug\n"
                          );
};

TEST(customout, file_leveltrace)
{
    init("9");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

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
};

TEST(customout, file_levelgreater)
{
    init("10");
    (*flog) << "Fatal";
    (*alog) << "Alert";
    (*clog) << "Crit";
    (*elog) << "Error";
    (*wlog) << "Warning";
    (*nlog) << "Notice";
    (*ilog) << "Info";
    (*dlog) << "Debug";
    (*tlog) << "Trace";

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
};

#endif /* end of include guard: UT_LIBYAPLOG_H_SHF9IC0C */
