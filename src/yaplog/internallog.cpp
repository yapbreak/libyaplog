#include "internallog.h"

#include <iostream>
#include <cstring>
#include <fstream>

using namespace logger;

InternalLog::InternalLog(log_level level, const log_location &loc,
                         std::ostream *destination,
                         log_level system_level)
    : m_level(level)
    , m_location(loc)
    , m_output(destination)
    , m_systemlevel(system_level)
{
    if (m_level <= m_systemlevel)
        print_header();
}

InternalLog::~InternalLog()
{
    if (m_level <= m_systemlevel) {
        (*this) << "\n";
    }
    closeOstream(m_output);
}

/**
* @brief Convert a log level to a single character.
*
* @param l Loglevel to convert.
*
* @return Single character symbolizes log level.
*/
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

/**
* @brief Prepare and print log prefix.
*
* Any log use the following prefix:
* - "[X] file:line(function) "
*
* where:
*   - X is one of the following character ('F' for fatal, 'A' for
*     alert, 'C' for critical, 'E' for error, 'W' for warning, 'N'
*     for notice, 'I' for information, 'D' for debug, 'T' for trace
*     or a space for any other level.
*   - file is the name of the file where log append.
*   - line is the line number where log append.
*   - function is the function name where log append.
*/
void InternalLog::print_header()
{
    (*m_output) << "[" << char_from_level(m_level) << "] "
                << m_location.m_file << ":"
                << m_location.m_line << "("
                << m_location.m_function << ") ";
}

/**
* @brief Get configured output stream where log are put.
*
* @return Output stream to be used by logger, depending on
*         `CSER_LOGDESTINATION` environment variable.
*
* If no environment variable is set, default is std::cerr.
* When `CSER_LOGDESTINATION` is set to `stdout` or `stderr`, stream
* is respectively redirected to std::cout or std::cerr, otherwise,
* logger considers variable content as a filename and try to open
* it in append mode. If file does not exists, logger create file.
* Upon failure, logger falls back to std::cerr.
*/
std::ostream *InternalLog::getOstream()
{
    const char *cser_logdestination = std::getenv("CSER_LOGDESTINATION");
    if (cser_logdestination == NULL) {
        return new std::ostream(std::cerr.rdbuf());
    } else {
        if (strcmp(cser_logdestination, "stderr") == 0) {
            return new std::ostream(std::cerr.rdbuf());
        } else if (strcmp(cser_logdestination, "stdout") == 0) {
            return new std::ostream(std::cout.rdbuf());
        } else {
            return new std::ofstream(cser_logdestination,
                                     std::ofstream::app);
        }
    }
    return new std::ostream(std::cerr.rdbuf());
}

/**
* @brief Close the given output stream properly.
*
* @param os Output stream to close.
*/
void InternalLog::closeOstream(std::ostream *os)
{
    delete os;
}

/**
* @brief Get configured logger level to show.
*
* @return Log level used by logger, depending on `CSER_LOGLEVEL`
*         environment variable.
*
* When `CSER_LOGLEVEL` is set to any number between 0 and 9, logger
* directly use the log level and print to output every log message
* with level lower or equal to the given system log level.
* If `CSER_LOGLEVEL` is set to a number lower than 0, 0 is used.
* If `CSER_LOGLEVEL` is set to a number higher than 9, 9 is used.
* If `CSER_LOGLEVEL` is not set to a number, 0 is used.
* If no environment variable is set, default is 0.
*/
log_level InternalLog::getSystemLevel()
{
    const char *cser_loglevel = std::getenv("CSER_LOGLEVEL");
    if (cser_loglevel == NULL) {
        return log_level::none;
    } else {
        try {
            int value = std::stoi(cser_loglevel);
            if (value < 0)
                return log_level::none;
            if (value > 9)
                return log_level::trace;
            return static_cast<log_level>(value);
        } catch (std::exception &) {
            return log_level::none;
        }
    }
}
