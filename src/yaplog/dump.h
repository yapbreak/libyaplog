#ifndef YAPLOG_DUMP_H_9LPSDK6A
#define YAPLOG_DUMP_H_9LPSDK6A

#include <cstdlib>
#include <string>
#include <ostream>

namespace logger {

    /**
    * @brief Allow a human readable representation of a data buffer
    *
    * The purpose of this class is to format a given buffer into a string
    * similar to the output of `hexdump -Cv`, with data offset, hexadecimal
    * representation and ascii representation.
    */
    class dump {
        public:
            /**
            * @brief Create a human readable representation of a given buffer.
            *
            * @param data Object based buffer.
            * @param size Size of data buffer.
            */
            dump(const void *data, const size_t size);
            ~dump();

            /**
            * @brief Retrieve human readable version of buffer.
            *
            * @return Human readable string.
            */
            std::string get_formatted_string() const;

        private:
            /**
            * @brief Pointer to linked data in instance.
            */
            const void *m_data;
            /**
            * @brief Size of buffer.
            */
            const size_t m_size;
    };

    /**
    * @brief Allow to print a dump object instance through std::ostream
    *        instance.
    *
    * @param out Stream where object will be printed.
    * @param data Data to print.
    *
    * @return Reference to the used output stream.
    */
    inline std::ostream &operator<<(std::ostream &out, const dump &data)
    {
        out << data.get_formatted_string();
        return out;
    }
};

#endif /* end of include guard: YAPLOG_DUMP_H_9LPSDK6A */
