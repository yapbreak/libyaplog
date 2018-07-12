#ifndef UT_DUMP_H_HWCOKENA
#define UT_DUMP_H_HWCOKENA

#include "yaplog/dump.h"


#include <string>
#include <sstream>
#include <cstring>
#include <CppUTest/TestHarness.h>

using namespace logger;

TEST_GROUP(dumper)
{
    void check_string(const char **expected, size_t line, const std::string &actual)
    {
        std::stringstream ss(actual);
        std::string chunk;
        size_t line_number = 0;

        while (std::getline(ss, chunk, '\n')) {
            CHECK_TRUE(line_number < line);
            if (line_number == 0) {
                STRCMP_CONTAINS(expected[line_number], chunk.c_str());
            } else {
                STRCMP_EQUAL(expected[line_number], chunk.c_str());
            }
            line_number++;
        }
        UNSIGNED_LONGS_EQUAL(line_number, line);
    }

};

TEST(dumper, empty_data)
{
    dump mydump(NULL, 0);
    std::string d = mydump.get_formatted_string();
    STRCMP_EQUAL("Dump 0 byte(s) starting at 0:",
                 d.c_str());
}

TEST(dumper, single_byte_data)
{
    char data[1] = { 42 };

    const char *expected[] = {
        "Dump 1 byte(s) starting at 0x",
        "00000000 2a                                               |*                |",
    };

    dump mydump(data, 1);
    std::string d = mydump.get_formatted_string();

    check_string(expected, DIM_OF(expected), d);
}

TEST(dumper, height_bytes_data)
{
    char data[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

    const char *expected[] = {
        "Dump 8 byte(s) starting at 0x",
        "00000000 00 01 02 03 04 05 06 07                          |........         |",
    };

    dump mydump(data, 8);
    std::string d = mydump.get_formatted_string();

    check_string(expected, DIM_OF(expected), d);
}

TEST(dumper, sixteen_bytes_data)
{
    char data[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
                      0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f};

    const char *expected[] = {
        "Dump 16 byte(s) starting at 0x",
        "00000000 30 31 32 33 34 35 36 37  38 39 3a 3b 3c 3d 3e 3f |01234567 89:;<=>?|",
    };

    dump mydump(data, 16);
    std::string d = mydump.get_formatted_string();

    check_string(expected, DIM_OF(expected), d);
}

TEST(dumper, many_bytes_data)
{
    const char *data = "abcdefghijklmnopqrstuvwxyz"
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "0123456789";
    const char *expected[] = {
        "Dump 62 byte(s) starting at 0x",
        "00000000 61 62 63 64 65 66 67 68  69 6a 6b 6c 6d 6e 6f 70 |abcdefgh ijklmnop|",
        "00000010 71 72 73 74 75 76 77 78  79 7a 41 42 43 44 45 46 |qrstuvwx yzABCDEF|",
        "00000020 47 48 49 4a 4b 4c 4d 4e  4f 50 51 52 53 54 55 56 |GHIJKLMN OPQRSTUV|",
        "00000030 57 58 59 5a 30 31 32 33  34 35 36 37 38 39       |WXYZ0123 456789  |",
    };

    dump mydump(data, strlen(data));
    std::string d = mydump.get_formatted_string();

    check_string(expected, DIM_OF(expected), d);
}

TEST(dumper, multiline_exactdata)
{
    const char *data = "abcdefghijklmnopqrstuvwxyz"
                       "ABCDEFGHIJKLMNOPQRSTUV";
    const char *expected[] = {
        "Dump 48 byte(s) starting at 0x",
        "00000000 61 62 63 64 65 66 67 68  69 6a 6b 6c 6d 6e 6f 70 |abcdefgh ijklmnop|",
        "00000010 71 72 73 74 75 76 77 78  79 7a 41 42 43 44 45 46 |qrstuvwx yzABCDEF|",
        "00000020 47 48 49 4a 4b 4c 4d 4e  4f 50 51 52 53 54 55 56 |GHIJKLMN OPQRSTUV|",
    };

    dump mydump(data, strlen(data));
    std::string d = mydump.get_formatted_string();

    check_string(expected, DIM_OF(expected), d);
}

#endif /* end of include guard: UT_DUMP_H_HWCOKENA */
