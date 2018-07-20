#include "conf.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace logger;

conf::conf(const char *destination,
           const char *level,
           const char *color,
           const char *info)
    : m_output(NULL)
    , m_err(std::cerr.rdbuf())
    , m_out(std::cout.rdbuf())
{
    parse_destination(destination);
    parse_level(level);
    parse_color(color);
    parse_info(info);
}

conf::~conf()
{
}


const log_level &conf::getSystemLevel() const
{
    return m_systemlevel;
}

std::ostream *conf::getOutput() const
{
    return m_output;
}

bool conf::getColor() const
{
    return m_color;
}

bool conf::getInfo() const
{
    return m_info;
}

void conf::parse_destination(const char *destination)
{
    const char *value = getenv(destination);
    if (value == NULL) {
        m_output = &m_err;
    } else {
        if (strcmp(value, "stderr") == 0) {
            m_output = &m_err;
        } else if (strcmp(value, "stdout") == 0) {
            m_output = &m_out;
        } else {
            m_file = std::ofstream(value, std::ofstream::app);
            if (m_file.is_open()) {
                m_output = &m_file;
            } else {
                std::cerr << "Fail to open " << value << std::endl;
                m_output = &m_err;
            }
        }
    }
}

void conf::parse_level(const char *level)
{
    const char *loglevel = std::getenv(level);
    if (loglevel == NULL) {
        m_systemlevel = log_level::none;
    } else {
        try {
            int value = std::stoi(loglevel);
            if (value < 0)
                m_systemlevel = log_level::none;
            else if (value > 9)
                m_systemlevel = log_level::trace;
            else
                m_systemlevel = static_cast<log_level>(value);
        } catch (std::exception &) {
            m_systemlevel = log_level::none;
        }
    }
}

void conf::parse_color(const char *color)
{
    const char *value = std::getenv(color);
    if (value == NULL) {
        m_color = false;
    } else {
        try {
            int val = std::stoi(value);
            m_color = (val == 1);
        } catch (std::exception &) {
            m_color = false;
        }
    }
}

void conf::parse_info(const char *info)
{
    const char *value = std::getenv(info);
    if (value == NULL) {
        m_info = false;
    } else {
        m_info = (strcmp(value, "debug") == 0);
    }
}
