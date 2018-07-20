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
        setenv("LOGINFO", "debug", 1);
        my_real_stream = new std::ostringstream();
    };

    void teardown()
    {
        unsetenv("LOGINFO");
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

void check_file_content(const char *file, std::string &expected)
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

TEST_GROUP(customout)
{
    const char *destination = "unittests_customout.log";
    void setup()
    {
        setenv("LOGINFO", "debug", 1);
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
        unlink(destination);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
        unlink(destination);
        unsetenv("LOGDESTINATION");
        unsetenv("LOGLEVEL");
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
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
    check_file_content(destination, expected);
};

TEST_GROUP(stdoutlog)
{
    void setup()
    {
        setenv("LOGINFO", "debug", 1);
        setenv("LOGDESTINATION", "stdout", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
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
        setenv("LOGINFO", "debug", 1);
        setenv("LOGDESTINATION", "stderr", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
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
        setenv("LOGINFO", "debug", 1);
        setenv("LOGDESTINATION", "/probablynotexisting/path/to/a/logfile", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
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


TEST_GROUP(customconfvariable)
{
    void setup()
    {
        setenv("LOGINFO", "debug", 1);
        logger::setDestinationVariable("MYCUSTOM_DEST");
        logger::setLevelVariable("MYCUSTOM_LEVEL");
        setenv("MYCUSTOM_DEST", "custom_output.log", 1);
        setenv("MYCUSTOM_LEVEL", "9", 1);
        setenv("LOGLEVEL", "0", 1);
        setenv("LOGDESTINATION", "stdout", 1);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
        unsetenv("MYCUSTOM_DEST");
        unsetenv("MYCUSTOM_LEVEL");
        unsetenv("LOGLEVEL");
        unsetenv("LOGDESTINATION");
        logger::unsetDestinationVariable();
        logger::unsetLevelVariable();
        unlink("custom_output.log");
    }
};

TEST(customconfvariable, alllogs)
{
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    logger::unsetLevelVariable();
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    logger::setLevelVariable("MYCUSTOM_LEVEL");
    givelog(log_level::info) << "Info";
    logger::unsetDestinationVariable();
    givelog(log_level::debug) << "Debug";
    logger::setDestinationVariable("MYCUSTOM_DEST");
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[I] file2:38(function2) Info\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("custom_output.log", expected);
};


TEST_GROUP(colorconf)
{
    void setup()
    {
        setenv("LOGINFO", "debug", 1);
        logger::setColorVariable("MYCUSTOM_COLOR");
        setenv("LOGDESTINATION", "color_output.log", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unsetenv("LOGINFO");
        unsetenv("MYCUSTOM_COLOR");
        logger::unsetColorVariable();
        unlink("color_output.log");
    }

    void enablecolor(const char *value)
    {
        setenv("MYCUSTOM_COLOR", value, 1);
    }
};

TEST(colorconf, alllogs_defaultcolor_settings)
{
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[W] file2:38(function2) Warning\n"
                         "[N] file2:38(function2) Notice\n"
                         "[I] file2:38(function2) Info\n"
                         "[D] file2:38(function2) Debug\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("color_output.log", expected);
};

TEST(colorconf, alllogs_color_off_settings)
{
    enablecolor("0");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[W] file2:38(function2) Warning\n"
                         "[N] file2:38(function2) Notice\n"
                         "[I] file2:38(function2) Info\n"
                         "[D] file2:38(function2) Debug\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("color_output.log", expected);
};

TEST(colorconf, alllogs_color_on_settings)
{
    enablecolor("1");
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("\x1b[101;97;1m[F] file2:38(function2)\x1b[0m Fatal\n"
                         "\x1b[105;97;1m[A] file2:38(function2)\x1b[0m Alert\n"
                         "\x1b[101;1m[C] file2:38(function2)\x1b[0m Crit\n"
                         "\x1b[91;1m[E] file2:38(function2)\x1b[0m Error\n"
                         "\x1b[93;1m[W] file2:38(function2)\x1b[0m Warning\n"
                         "\x1b[94;1m[N] file2:38(function2)\x1b[0m Notice\n"
                         "\x1b[92;1m[I] file2:38(function2)\x1b[0m Info\n"
                         "\x1b[97;1m[D] file2:38(function2)\x1b[0m Debug\n"
                         "\x1b[1m[T] file2:38(function2)\x1b[0m Trace\n"
                        );
    check_file_content("color_output.log", expected);
};

TEST(colorconf, alllogs_color_unauth_values_settings)
{
    enablecolor("2");
    givelog(log_level::fatal) << "Fatal";
    enablecolor("-1");
    givelog(log_level::alert) << "Alert";
    enablecolor("foo");
    givelog(log_level::crit) << "Crit";
    enablecolor("bar");
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[W] file2:38(function2) Warning\n"
                         "[N] file2:38(function2) Notice\n"
                         "[I] file2:38(function2) Info\n"
                         "[D] file2:38(function2) Debug\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("color_output.log", expected);
};

TEST_GROUP(infocontrol)
{
    void setup()
    {
        setenv("LOGDESTINATION", "info_output.log", 1);
        setenv("LOGLEVEL", "9", 1);
    }

    void teardown()
    {
        unlink("info_output.log");
        unsetenv("LOGLEVEL");
        unsetenv("LOGDESTINATION");
        unsetenv("LOGINFO");
        logger::unsetInfoVariable();
    }
};

TEST(infocontrol, alllog_noinfo)
{
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] Fatal\n"
                         "[A] Alert\n"
                         "[C] Crit\n"
                         "[E] Error\n"
                         "[W] Warning\n"
                         "[N] Notice\n"
                         "[I] Info\n"
                         "[D] Debug\n"
                         "[T] Trace\n"
                        );
    check_file_content("info_output.log", expected);
};

TEST(infocontrol, alllog_info)
{
    setenv("LOGINFO", "debug", 1);
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    setenv("LOGINFO", "debug_ornot", 1);
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    setenv("LOGINFO", "debug", 1);
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[W] Warning\n"
                         "[N] Notice\n"
                         "[I] file2:38(function2) Info\n"
                         "[D] file2:38(function2) Debug\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("info_output.log", expected);
};

TEST(infocontrol, customvar_noinfo)
{
    logger::setInfoVariable("MYCUSTOM_INFO");
    setenv("LOGINFO", "debug", 1);
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    givelog(log_level::warn) << "Warning";
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] Fatal\n"
                         "[A] Alert\n"
                         "[C] Crit\n"
                         "[E] Error\n"
                         "[W] Warning\n"
                         "[N] Notice\n"
                         "[I] Info\n"
                         "[D] Debug\n"
                         "[T] Trace\n"
                        );
    check_file_content("info_output.log", expected);
};

TEST(infocontrol, customvar_info)
{
    logger::setInfoVariable("MYCUSTOM_INFO");
    setenv("MYCUSTOM_INFO", "debug", 1);
    givelog(log_level::fatal) << "Fatal";
    givelog(log_level::alert) << "Alert";
    givelog(log_level::crit) << "Crit";
    givelog(log_level::error) << "Error";
    setenv("MYCUSTOM_INFO", "toto", 1);
    givelog(log_level::warn) << "Warning";
    setenv("MYCUSTOM_INFO", "debug", 1);
    givelog(log_level::notice) << "Notice";
    givelog(log_level::info) << "Info";
    givelog(log_level::debug) << "Debug";
    givelog(log_level::trace) << "Trace";
    std::string expected("[F] file2:38(function2) Fatal\n"
                         "[A] file2:38(function2) Alert\n"
                         "[C] file2:38(function2) Crit\n"
                         "[E] file2:38(function2) Error\n"
                         "[W] Warning\n"
                         "[N] file2:38(function2) Notice\n"
                         "[I] file2:38(function2) Info\n"
                         "[D] file2:38(function2) Debug\n"
                         "[T] file2:38(function2) Trace\n"
                        );
    check_file_content("info_output.log", expected);
    unsetenv("MYCUSTOM_INFO");
};

#endif /* end of include guard: UT_LIBYAPLOG_H_SHF9IC0C */
