#include <map>

#include <CppUTest/CommandLineTestRunner.h>
#include "ut_dump.h"
#include "ut_conf.h"
#include "ut_libyaplog.h"

int main(int argc, const char *argv[])
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
