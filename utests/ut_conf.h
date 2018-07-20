#ifndef UT_CONF_H_KARUFICE
#define UT_CONF_H_KARUFICE

#include <CppUTest/TestHarness.h>
#include <iostream>
#include <unistd.h>

TEST_GROUP(confgroup)
{
    void setup()
    {
        c = NULL;
    }

    void teardown()
    {
        if (c != NULL)
            delete c;
        c = NULL;
    }

    exposed_conf *c;
};

TEST(confgroup, noenv)
{
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::none, c->getSystemLevel());
    CHECK_FALSE(c->getColor());
    CHECK_FALSE(c->getInfo());
    CHECK_EQUAL(std::cerr.rdbuf(), c->getOutput()->rdbuf());
}

TEST(confgroup, levels_inlimits)
{
    setenv("L", "0", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::none, c->getSystemLevel());
    delete c;
    setenv("L", "1", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::fatal, c->getSystemLevel());
    delete c;
    setenv("L", "2", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::alert, c->getSystemLevel());
    delete c;
    setenv("L", "3", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::crit, c->getSystemLevel());
    delete c;
    setenv("L", "4", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::error, c->getSystemLevel());
    delete c;
    setenv("L", "5", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::warn, c->getSystemLevel());
    delete c;
    setenv("L", "6", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::notice, c->getSystemLevel());
    delete c;
    setenv("L", "7", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::info, c->getSystemLevel());
    delete c;
    setenv("L", "8", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::debug, c->getSystemLevel());
    delete c;
    setenv("L", "9", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::trace, c->getSystemLevel());
    delete c;
    c = NULL;
    unsetenv("L");
}

TEST(confgroup, levels_lower)
{
    setenv("L", "-1", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::none, c->getSystemLevel());
    unsetenv("L");
}

TEST(confgroup, levels_higher)
{
    setenv("L", "10", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::trace, c->getSystemLevel());
    unsetenv("L");
}

TEST(confgroup, levels_invalid)
{
    setenv("L", "foo", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(logger::log_level::none, c->getSystemLevel());
    unsetenv("L");
}

TEST(confgroup, change_levelvariable)
{
    setenv("L", "9", 1);
    c = new exposed_conf("D", "LOGLEVEL", "C", "I");
    CHECK_EQUAL(logger::log_level::none, c->getSystemLevel());
    unsetenv("L");
}

TEST(confgroup, color_valid)
{
    setenv("C", "0", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_FALSE(c->getColor());
    delete c;
    setenv("C", "1", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK(c->getColor());
    delete c;
    c = NULL;
    unsetenv("C");
}

TEST(confgroup, color_outofrange)
{
    setenv("C", "-1", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_FALSE(c->getColor());
    delete c;
    setenv("C", "2", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_FALSE(c->getColor());
    delete c;
    c = NULL;
    unsetenv("C");
}

TEST(confgroup, color_invalid)
{
    setenv("C", "bar", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_FALSE(c->getColor());
    unsetenv("C");
}

TEST(confgroup, info_valid)
{
    setenv("I", "debug", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK(c->getInfo());
    delete c;
    setenv("I", "release", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_FALSE(c->getInfo());
    unsetenv("I");
}

TEST(confgroup, dest_validstd)
{
    setenv("D", "stderr", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(std::cerr.rdbuf(), c->getOutput()->rdbuf());
    delete c;
    setenv("D", "stdout", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(std::cout.rdbuf(), c->getOutput()->rdbuf());
    unsetenv("D");
}

TEST(confgroup, dest_validfile)
{
    setenv("D", "/tmp/test.log", 1);
    c = new exposed_conf("D", "L", "C", "I");
    std::ofstream *tmp = dynamic_cast<std::ofstream *>(c->getOutput());
    CHECK(tmp != NULL);
    CHECK(tmp->is_open());
    CHECK(access("/tmp/test.log", F_OK) == 0);

    delete c;
    c = NULL;
    unlink("/tmp/test.log");
}

TEST(confgroup, dest_invalidfile)
{
    setenv("D", "/mainly/not/accessible/file/I/hope.log", 1);
    c = new exposed_conf("D", "L", "C", "I");
    CHECK_EQUAL(std::cerr.rdbuf(), c->getOutput()->rdbuf());
}

#endif /* end of include guard: UT_CONF_H_KARUFICE */
