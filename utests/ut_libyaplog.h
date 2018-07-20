#ifndef UT_LIBYAPLOG_H_SHF9IC0C
#define UT_LIBYAPLOG_H_SHF9IC0C

#include "yaplog.h"

#include <CppUTest/TestHarness.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>

#include <unistd.h>

using namespace logger;

TEST_GROUP(defaultlogger)
{
    void setup()
    {
        setenv("LOGDESTINATION", "/tmp/test.log", 1);
    }

    void teardown()
    {
        unsetenv("LOGDESTINATION");
        unlink("/tmp/test.log");
    }
};

void alllogs()
{
    short i = 42;
    long l = 1223487234;
    const char *str = "foobar";
    std::string stdstr("std::foobar");
    const uint8_t buffer[10] = { 30, 13, 38, 12, 42 };

    FLOG() << "constant C-string";
    ALOG() << i;
    CLOG() << l;
    ELOG() << "Composition: " << str;
    WLOG() << stdstr << " has a length of " << stdstr.size();
    NLOG() << buffer[2];
    ILOG() << "Information";
    DLOG() << std::setw(8) << std::setfill('0') << std::hex << 42;
    TLOG() << "Very verbose log";
}

TEST(defaultlogger, fatal)
{
    setenv("LOGLEVEL", "1", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, alert)
{
    setenv("LOGLEVEL", "2", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, crit)
{
    setenv("LOGLEVEL", "3", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, error)
{
    setenv("LOGLEVEL", "4", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, warning)
{
    setenv("LOGLEVEL", "5", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n"
                           "[W] std::foobar has a length of 11\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, notice)
{
    setenv("LOGLEVEL", "6", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n"
                           "[W] std::foobar has a length of 11\n"
                           "[N] &\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, info)
{
    setenv("LOGLEVEL", "7", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n"
                           "[W] std::foobar has a length of 11\n"
                           "[N] &\n"
                           "[I] Information\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, debug)
{
    setenv("LOGLEVEL", "8", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n"
                           "[W] std::foobar has a length of 11\n"
                           "[N] &\n"
                           "[I] Information\n"
                           "[D] 0000002a\n";
    check_file_content("/tmp/test.log", expected);
};


TEST(defaultlogger, trace)
{
    setenv("LOGLEVEL", "9", 1);
    alllogs();
    unsetenv("LOGLEVEL");

    std::string expected = "[F] constant C-string\n"
                           "[A] 42\n"
                           "[C] 1223487234\n"
                           "[E] Composition: foobar\n"
                           "[W] std::foobar has a length of 11\n"
                           "[N] &\n"
                           "[I] Information\n"
                           "[D] 0000002a\n"
                           "[T] Very verbose log\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, alllogs_colored)
{
    setenv("LOGLEVEL", "9", 1);
    setenv("LOGCOLOR", "1", 1);
    alllogs();
    unsetenv("LOGLEVEL");
    unsetenv("LOGCOLOR");

    std::string expected = "\x1b[101;97;1m[F]\x1b[0m constant C-string\n"
                           "\x1b[105;97;1m[A]\x1b[0m 42\n"
                           "\x1b[101;1m[C]\x1b[0m 1223487234\n"
                           "\x1b[91;1m[E]\x1b[0m Composition: foobar\n"
                           "\x1b[93;1m[W]\x1b[0m std::foobar has a length of 11\n"
                           "\x1b[94;1m[N]\x1b[0m &\n"
                           "\x1b[92;1m[I]\x1b[0m Information\n"
                           "\x1b[97;1m[D]\x1b[0m 0000002a\n"
                           "\x1b[1m[T]\x1b[0m Very verbose log\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, alllogs_info_colored)
{
    setenv("LOGLEVEL", "9", 1);
    setenv("LOGCOLOR", "1", 1);
    setenv("LOGINFO", "debug", 1);
    alllogs();
    unsetenv("LOGLEVEL");
    unsetenv("LOGCOLOR");
    unsetenv("LOGINFO");

    std::string expected = "\x1b[101;97;1m[F] ut_libyaplog.h:38(alllogs)\x1b[0m constant C-string\n"
                           "\x1b[105;97;1m[A] ut_libyaplog.h:39(alllogs)\x1b[0m 42\n"
                           "\x1b[101;1m[C] ut_libyaplog.h:40(alllogs)\x1b[0m 1223487234\n"
                           "\x1b[91;1m[E] ut_libyaplog.h:41(alllogs)\x1b[0m Composition: foobar\n"
                           "\x1b[93;1m[W] ut_libyaplog.h:42(alllogs)\x1b[0m std::foobar has a length of 11\n"
                           "\x1b[94;1m[N] ut_libyaplog.h:43(alllogs)\x1b[0m &\n"
                           "\x1b[92;1m[I] ut_libyaplog.h:44(alllogs)\x1b[0m Information\n"
                           "\x1b[97;1m[D] ut_libyaplog.h:45(alllogs)\x1b[0m 0000002a\n"
                           "\x1b[1m[T] ut_libyaplog.h:46(alllogs)\x1b[0m Very verbose log\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, alllogs_info)
{
    setenv("LOGLEVEL", "9", 1);
    setenv("LOGINFO", "debug", 1);
    alllogs();
    unsetenv("LOGLEVEL");
    unsetenv("LOGINFO");

    std::string expected = "[F] ut_libyaplog.h:38(alllogs) constant C-string\n"
                           "[A] ut_libyaplog.h:39(alllogs) 42\n"
                           "[C] ut_libyaplog.h:40(alllogs) 1223487234\n"
                           "[E] ut_libyaplog.h:41(alllogs) Composition: foobar\n"
                           "[W] ut_libyaplog.h:42(alllogs) std::foobar has a length of 11\n"
                           "[N] ut_libyaplog.h:43(alllogs) &\n"
                           "[I] ut_libyaplog.h:44(alllogs) Information\n"
                           "[D] ut_libyaplog.h:45(alllogs) 0000002a\n"
                           "[T] ut_libyaplog.h:46(alllogs) Very verbose log\n";
    check_file_content("/tmp/test.log", expected);
};

TEST(defaultlogger, dynamic)
{
    setenv("L", "9", 1);
    setenv("D", "/tmp/test.log", 1);
    {
        logger::conf c("D", "L", "C", "I");
        logger::InternalLog *log = new logger::InternalLog(logger::log_level::fatal,
                                                           logger::log_location("test", "file", 42),
                                                           c);
        (*log) << "Test";
        delete log;
    }
    unsetenv("L");
    unsetenv("D");

    std::string expected = "[F] Test\n";
    check_file_content("/tmp/test.log", expected);
};


#endif /* end of include guard: UT_LIBYAPLOG_H_SHF9IC0C */
