#ifndef YAPLOG_INTERNALLOG_H_6RMYFK5I
#define YAPLOG_INTERNALLOG_H_6RMYFK5I

#include <yaplog/level.h>
#include <yaplog/loglocation.h>

#include <ostream>

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
            * @param destination Standard output stream to be used.
            * @param system_level System log level.
            */
            InternalLog(log_level level, const log_location &loc,
                        std::ostream *destination,
                        log_level system_level = log_level::trace);

            virtual ~InternalLog();

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T &);

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T *);

            /**
            * @brief Additional overload to handle ostream specific IO
            *         manipulators
            *
            * @param out Internal logger where IO manipulators must aplly.
            * @param f IO function manipulators.
            *
            * @return Internal logger instance.
            */
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

        public:
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
            static std::ostream *getOstream();

            /**
            * @brief Close the given output stream properly.
            *
            * @param os Output stream to close.
            */
            static void closeOstream(std::ostream *os);

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
            static log_level getSystemLevel();

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
            * @brief Linked output stream.
            */
            std::ostream *m_output;
            /**
            * @brief System log level.
            */
            log_level m_systemlevel;
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
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << value;
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
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << value;
        return out;
    }

    inline const InternalLog &operator<<(const InternalLog &out,
                                         std::ostream &(*f)(std::ostream &))
    {
        if (out.m_level <= out.m_systemlevel)
            (*out.m_output) << f;
        return out;
    }

};

#endif /* end of include guard: YAPLOG_INTERNALLOG_H_6RMYFK5I */
