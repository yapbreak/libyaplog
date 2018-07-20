#ifndef YAPLOG_H_UGV90DZC
#define YAPLOG_H_UGV90DZC

#include <yaplog/internallog.h>
#include <yaplog/dump.h>

/**
 * @brief Fatal log macro utility to print a fatal message on stderr.
 */
#define FLOG() logger::InternalLog(logger::log_level::fatal, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())

/**
 * @brief Alert log macro utility to print an alert message on stderr.
 */
#define ALOG() logger::InternalLog(logger::log_level::alert, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Critical log macro utility to print a critical message on stderr.
 */
#define CLOG() logger::InternalLog(logger::log_level::crit, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Error log macro utility to print an error message on stderr.
 */
#define ELOG() logger::InternalLog(logger::log_level::error, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Warning log macro utility to print a warning message on stderr.
 */
#define WLOG() logger::InternalLog(logger::log_level::warn, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Notice log macro utility to print a notice message on stderr.
 */
#define NLOG() logger::InternalLog(logger::log_level::notice, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Information log macro utility to print an information message on
 *        stderr.
 */
#define ILOG() logger::InternalLog(logger::log_level::info, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Debug log macro utility to print a debug message on stderr.
 */
#define DLOG() logger::InternalLog(logger::log_level::debug, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())
/**
 * @brief Trace log macro utility to print a trace message on stderr.
 */
#define TLOG() logger::InternalLog(logger::log_level::trace, \
                                   logger::log_location(__func__, \
                                                        __FILE__, \
                                                        __LINE__), \
                                   logger::InternalLog::getOstream(), \
                                   logger::InternalLog::getSystemLevel())

namespace logger {
    /**
    * @brief Set environment variable to check for log file destination.
    *
    * @param dest New destination environement variable
    */
    void setDestinationVariable(const char *dest);
    void setLevelVariable(const char *level);
    void setColorVariable(const char *color);
    void setInfoVariable(const char *info);
    void unsetDestinationVariable();
    void unsetLevelVariable();
    void unsetColorVariable();
    void unsetInfoVariable();
};

#endif /* end of include guard: YAPLOG_H_UGV90DZC */
