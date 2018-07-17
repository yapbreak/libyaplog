#include "dump.h"

#include <sstream>
#include <iomanip>

using namespace logger;

dump::dump(const void *data, const size_t size) : m_data(data)
                                                , m_size(size)
{ }

dump::~dump()
{ }

/**
* @brief Retrieve human readable version of buffer.
*
* @return Human readable string.
*/
std::string dump::get_formatted_string() const
{
    const unsigned char *data_ptr = static_cast<const unsigned char *>(m_data);

    std::stringstream output;
    output << "Dump " << m_size
           << " byte(s) starting at " << m_data << ":";

    std::stringstream offset;
    std::stringstream hexa;
    std::stringstream ascii;

    size_t i = 0;

    offset.str("");
    offset << "\n";
    offset << std::setw(8) << std::setfill('0')
           << std::hex << (i);
    offset << " ";
    hexa.str("");
    ascii.str("");
    for (i = 0; i < m_size; i++) {
        // Add one extra space after 8 bytes.
        if (i % 16 == 8) {
            ascii << " ";
            hexa << " ";
        }

        hexa << std::hex << std::setfill('0') << std::setw(2)
             << static_cast<unsigned int>(*data_ptr);
        hexa << " ";

        if (isprint(*data_ptr))
            ascii << (*data_ptr);
        else
            ascii << ".";

        data_ptr++;

        if (i % 16 == 15) {
            output << offset.str() << hexa.str()
                   << "|" << ascii.str() << "|";

            offset.str("");
            offset << "\n";
            offset << std::setw(8) << std::setfill('0')
                   << std::hex << (i + 1);
            offset << " ";
            hexa.str("");
            ascii.str("");
        }
    }

    if (i % 16 != 0) {
        output << offset.str();
        output << std::setw(49) << std::setfill(' ') << std::left << hexa.str();
        output << "|";
        output << std::setw(17) << std::setfill(' ') << std::left << ascii.str();
        output << "|";
    }

    return output.str();
}
