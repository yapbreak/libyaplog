#ifndef YAPLOG_H_UGV90DZC
#define YAPLOG_H_UGV90DZC

#ifndef LOG_DEST
#   define LOG_DEST "LOGDESTINATION"
#endif
#ifndef LOG_LEVEL
#   define LOG_LEVEL "LOGLEVEL"
#endif
#ifndef LOG_COLOR
#   define LOG_COLOR "LOGCOLOR"
#endif
#ifndef LOG_INFO
#   define LOG_INFO "LOGINFO"
#endif

#include <yaplog/internallog.h>
#include <yaplog/dump.h>

#define yaplog_getlocation logger::log_location(__func__, \
                                                __FILE__, \
                                                __LINE__)
#define yaplog_getconf logger::conf(LOG_DEST, \
                                    LOG_LEVEL, \
                                    LOG_COLOR, \
                                    LOG_INFO)
#define getLogger(level) logger::InternalLog(logger::log_level::level, \
                                             yaplog_getlocation, \
                                             yaplog_getconf \
                                            )

/**
 * @brief Fatal log macro utility to print a fatal message on stderr.
 */
#define FLOG() getLogger(fatal)
/**
 * @brief Alert log macro utility to print an alert message on stderr.
 */
#define ALOG() getLogger(alert)
/**
 * @brief Critical log macro utility to print a critical message on stderr.
 */
#define CLOG() getLogger(crit)
/**
 * @brief Error log macro utility to print an error message on stderr.
 */
#define ELOG() getLogger(error)
/**
 * @brief Warning log macro utility to print a warning message on stderr.
 */
#define WLOG() getLogger(warn)
/**
 * @brief Notice log macro utility to print a notice message on stderr.
 */
#define NLOG() getLogger(notice)
/**
 * @brief Information log macro utility to print an information message on
 *        stderr.
 */
#define ILOG() getLogger(info)
/**
 * @brief Debug log macro utility to print a debug message on stderr.
 */
#define DLOG() getLogger(debug)
/**
 * @brief Trace log macro utility to print a trace message on stderr.
 */
#define TLOG() getLogger(trace)

#endif /* end of include guard: YAPLOG_H_UGV90DZC */
