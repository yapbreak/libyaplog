#include "yaplog.h"

#include <iostream>
#include <cstring>
#include <fstream>

#include "color.h"

using namespace logger;

InternalLog::InternalLog(log_level level,
                         const log_location &loc,
                         const conf &c)
    : m_level(level)
    , m_location(loc)
    , m_conf(c)
{
    if (m_level <= m_conf.getSystemLevel())
        print_header();
}

InternalLog::~InternalLog()
{
    if (m_level <= m_conf.getSystemLevel()) {
        (*this) << "\n";
    }
}

char InternalLog::char_from_level(enum log_level l)
{
    switch (l) {
        case fatal:
            return 'F';
        case alert:
            return 'A';
        case crit:
            return 'C';
        case error:
            return 'E';
        case warn:
            return 'W';
        case notice:
            return 'N';
        case info:
            return 'I';
        case debug:
            return 'D';
        case trace:
            return 'T';
        default:
            return ' ';
    }
}

void InternalLog::print_header()
{
    bool color = m_conf.getColor();
    std::ostream *output = m_conf.getOutput();
    (*output) << color_start(color)
              << "[" << char_from_level(m_level) << "]";
    if (m_conf.getInfo()) {
        (*output) << " " << m_location.m_file << ":"
                    << m_location.m_line << "("
                    << m_location.m_function << ")";
    }
    (*output) << color_end(color) << " ";
}



const char *InternalLog::color_start(bool color)
{
    if (!color)
        return "";

    switch (m_level) {
        case fatal:
            return ANSI_COLOR_FATAL;
        case alert:
            return ANSI_COLOR_ALERT;
        case crit:
            return ANSI_COLOR_CRITIC;
        case error:
            return ANSI_COLOR_ERROR;
        case warn:
            return ANSI_COLOR_WARNING;
        case notice:
            return ANSI_COLOR_NOTICE;
        case info:
            return ANSI_COLOR_INFORMATION;
        case debug:
            return ANSI_COLOR_DEBUG;
        case trace:
            return ANSI_COLOR_TRACE;
        default:
            return "";
    }
}

const char *InternalLog::color_end(bool color)
{
    if (color)
        return ANSI_COLOR_RESET;
    else
        return "";
}
