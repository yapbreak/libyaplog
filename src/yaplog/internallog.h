#ifndef YAPLOG_INTERNALLOG_H_6RMYFK5I
#define YAPLOG_INTERNALLOG_H_6RMYFK5I

#include <yaplog/level.h>
#include <yaplog/loglocation.h>
#include <yaplog/conf.h>

#include <ostream>

#define YAPLOG_LEVEL_DEFAULT "LOGLEVEL"
#define YAPLOG_DEST_DEFAULT  "LOGDESTINATION"
#define YAPLOG_COLOR_DEFAULT "LOGCOLOR"
#define YAPLOG_INFO_DEFAULT  "LOGINFO"

namespace logger {

    /**
    * @brief Main class that allow logging to a given ostream destination.
    */
    class InternalLog
    {
        public:
            /**
            * @brief Contructor of a simple logger, linked to any standard
            *        output stream.
            *
            * @param level The log level of the given logger.
            * @param loc Information of location of log in code base.
            * @param c Logger configuration
            */
            InternalLog(log_level level,
                        const log_location &loc,
                        const conf &c);

            virtual ~InternalLog();

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T &);

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T *);

            friend const InternalLog &operator<<(const InternalLog &out,
                                                 std::ostream &(*f)(std::ostream &));

        private:
            /**
            * @brief Convert a log level to a single character.
            *
            * @param l Loglevel to convert.
            *
            * @return Single character symbolizes log level.
            */
            char char_from_level(enum log_level l);

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
            void print_header();
            /**
            * @brief Depending on color configuration flag, get ANSI escape
            *        code of current log level.
            *
            * @param color Color configuration flag.
            *
            * @return ANSI escape sequence.
            */
            const char *color_start(bool color);
            /**
            * @brief Depending on color configuration flag, get ANSI escape
            *        code to reset color.
            *
            * @param color Color configuration flag.
            *
            * @return ANSI escape reset sequence.
            */
            const char *color_end(bool color);

        protected:
            /**
            * @brief Log level.
            */
            log_level m_level;
            /**
            * @brief Log location.
            */
            log_location m_location;
            /**
            * @brief Log configuration.
            */
            const conf &m_conf;
    };

    /**
    * @brief Print any type to an internal logger instance.
    *
    * @tparam T Typename of data to print
    * @param out Internal logger instance where data will be printed
    * @param value Data to print
    *
    * @return Internal logger instance used.
    */
    template<typename T>
    inline const InternalLog &operator<<(const InternalLog &out, const T &value)
    {
        if (out.m_level <= out.m_conf.getSystemLevel())
            (*out.m_conf.getOutput()) << value;
        return out;
    }
    /**
    * @brief Print any type to an internal logger instance.
    *
    * @tparam T Typename of data to print
    * @param out Internal logger instance where data will be printed
    * @param value Pointer to data to print
    *
    * @return Internal logger instance used.
    */
    template<typename T>
    inline const InternalLog &operator<<(const InternalLog &out, const T *value)
    {
        if (out.m_level <= out.m_conf.getSystemLevel())
            (*out.m_conf.getOutput()) << value;
        return out;
    }

    /**
    * @brief Additional overload to handle ostream specific IO
    *         manipulators
    *
    * @param out Internal logger where IO manipulators must aplly.
    * @param f IO function manipulators.
    *
    * @return Internal logger instance.
    */
    inline const InternalLog &operator<<(const InternalLog &out,
                                         std::ostream &(*f)(std::ostream &))
    {
        if (out.m_level <= out.m_conf.getSystemLevel())
            (*out.m_conf.getOutput()) << f;
        return out;
    }

};

#endif /* end of include guard: YAPLOG_INTERNALLOG_H_6RMYFK5I */
