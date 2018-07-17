#include "yaplog.h"

#include <iostream>
#include <cstring>
#include <fstream>

using namespace logger;

char *InternalLog::s_destination = NULL;
char *InternalLog::s_level = NULL;

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
    (*m_output) << "[" << char_from_level(m_level) << "] "
                << m_location.m_file << ":"
                << m_location.m_line << "("
                << m_location.m_function << ") ";
}

std::ostream *InternalLog::getOstream(const char *destination)
{
    if (destination == NULL) {
        return new std::ostream(std::cerr.rdbuf());
    } else {
        if (strcmp(destination, "stderr") == 0) {
            return new std::ostream(std::cerr.rdbuf());
        } else if (strcmp(destination, "stdout") == 0) {
            return new std::ostream(std::cout.rdbuf());
        } else {
            std::ofstream *ofs;
            ofs = new std::ofstream(destination, std::ofstream::app);
            if (ofs != NULL && ofs->is_open()) {
                return ofs;
            } else {
                std::cerr << "Fail to open " << destination << std::endl;
                delete ofs;
                return new std::ostream(std::cerr.rdbuf());
            }
        }
    }
    return new std::ostream(std::cerr.rdbuf());
}

std::ostream *InternalLog::getOstream()
{
    const char *logdestination = std::getenv(getDestinationVariable());
    return getOstream(logdestination);
}

void InternalLog::closeOstream(std::ostream *os)
{
    delete os;
}

log_level InternalLog::getSystemLevel()
{
    const char *cser_loglevel = std::getenv(getLevelVariable());
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

const char *InternalLog::getDestinationVariable()
{
    return s_destination ? s_destination : YAPLOG_DEST_DEFAULT;
}

const char *InternalLog::getLevelVariable()
{
    return s_level ? s_level : YAPLOG_LEVEL_DEFAULT;
}

void InternalLog::setDestinationVariable(const char *dest)
{
    unsetDestinationVariable();
    s_destination = strdup(dest);
}

void InternalLog::setLevelVariable(const char *level)
{
    unsetLevelVariable();
    s_level = strdup(level);
}

void InternalLog::unsetDestinationVariable()
{
    if (s_destination != NULL)
        free(static_cast<void *>(s_destination));
    s_destination = NULL;
}

void InternalLog::unsetLevelVariable()
{
    if (s_level != NULL)
        free(static_cast<void *>(s_level));
    s_level = NULL;
}
