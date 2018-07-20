#ifndef FIXTURES_H_BL2ZH1S6
#define FIXTURES_H_BL2ZH1S6

#include <map>
#include <string>
#include <cstring>
#include <CppUTest/TestHarness.h>

#define DIM_OF(array) (sizeof(array) / sizeof((array)[0]))

#include "exposed_conf.h"

inline void check_file_content(const char *filename, const std::string &expected)
{
    FILE *f = fopen(filename, "rb");
    if (f != NULL) {
        if (expected.size() != 0) {
            char *content = new char[expected.size() + 1];
            memset(content, 0, expected.size() + 1);
            UNSIGNED_LONGS_EQUAL(1, fread(content, expected.size(), 1, f));
            STRCMP_EQUAL(expected.c_str(), content);
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

#endif /* end of include guard: FIXTURES_H_BL2ZH1S6 */
