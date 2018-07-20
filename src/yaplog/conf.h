#ifndef CONF_H_ESGKSFA9
#define CONF_H_ESGKSFA9

#include <ostream>
#include <fstream>

#include <yaplog/level.h>

namespace logger {

    class InternalLog;

    /**
    * @brief Hold configuration of logger.
    */
    class conf {
        public:
            /**
            * @brief Constructor of conf logger object.
            *
            * @param destination Environment variable name where log
            *                    destination will be set.
            * @param level Environment variable name where log level will be
            *              set.
            * @param color Environment variable name where log color will be
            *              set.
            * @param info Environment variable name where log info will be set.
            */
            conf(const char *destination,
                 const char *level,
                 const char *color,
                 const char *info);
            ~conf();

            /**
            * @brief Main logger class defined in internallog.h
            */
            friend class InternalLog;

            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T &);
            template<typename T>
            friend const InternalLog &operator<<(const InternalLog &, const T *);
            friend const InternalLog &operator<<(const InternalLog &out,
                                                 std::ostream &(*f)(std::ostream &));
        protected:

            /**
            * @brief Get log level required by system configuration, as read
            *        in environment variable.
            *
            * @return System log level.
            */
            const log_level &getSystemLevel() const;
            /**
            * @brief Get output stream where log needs to be written.
            *
            * @return Output stream pointer.
            */
            std::ostream *getOutput() const;
            /**
            * @brief Color flag
            *
            * @return True if color is enabled.
            */
            bool getColor() const;
            /**
            * @brief Info flag
            *
            * @return True if file, line and function information are enabled.
            */
            bool getInfo() const;

        private:
            /**
            * @brief Read `destination` environment variable and store
            *        corresponding output stream in object instance.
            *
            * @param destination Environment variable name to read.
            */
            void parse_destination(const char *destination);
            /**
            * @brief Read `level` environment variable and store corresponding
            *        system log level in object instance.
            *
            * @param level Environment variable name to read.
            */
            void parse_level(const char *level);
            /**
            * @brief Read `color` environment variable and store corresponding
            *        color flag in object instance.
            *
            * @param color Environment variable name to read.
            */
            void parse_color(const char *color);
            /**
            * @brief Read `info` environment variable and store corresponding
            *        info flag in object instance.
            *
            * @param info Environment variable name to read.
            */
            void parse_info(const char *info);

        private:
            /**
            * @brief System log level.
            */
            log_level m_systemlevel;
            /**
            * @brief Pointer to output stream to use.
            */
            std::ostream *m_output;
            /**
            * @brief Repplication of stderr output stream.
            */
            std::ostream m_err;
            /**
            * @brief Repplication of stdout output stream.
            */
            std::ostream m_out;
            /**
            * @brief File output stream, valid if a file is given as
            *        destination.
            */
            std::ofstream m_file;
            /**
            * @brief Color flag.
            */
            bool m_color;
            /**
            * @brief Info flag.
            */
            bool m_info;
    };
};

#endif /* end of include guard: CONF_H_ESGKSFA9 */
