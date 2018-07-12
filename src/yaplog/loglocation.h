#ifndef YAPLOG_LOGLOCATION_H_RANZIVOU
#define YAPLOG_LOGLOCATION_H_RANZIVOU

#include <cstddef>
#include <string>

namespace logger {

    /**
    * @brief Contains all information needed to localize a given point in
    *        codebase.
    *
    * This structure especially retains current function name, current file
    * and current line.
    */
    struct log_location {
        /**
        * @brief Build a location structure with function file and line
        *        information.
        *
        * @param function Function name.
        * @param file File name.
        * @param line Line number.
        */
        log_location(const char *function,
                     const char *file,
                     const size_t line) : m_function(function)
                                        , m_file(file)
                                        , m_line(line)
        { }

        /**
        * @brief Function name.
        */
        const std::string m_function;
        /**
        * @brief File name.
        */
        const std::string m_file;
        /**
        * @brief Line number.
        */
        const size_t m_line;
    };

};

#endif /* end of include guard: YAPLOG_LOGLOCATION_H_RANZIVOU */
