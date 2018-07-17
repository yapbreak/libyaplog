/**
 * This is a simple yaplog sample.
 *
 * To compile this sample, use the following commands:
 *
 * g++ -o sample.o -c sample.cpp $(pkg-config --cflags yaplog)
 * g++ -o sample sample.o $(pkg-config --libs yaplog)
 *
 * Then, set variable LOGLEVEL and LOGDESTINATION to control logs output:
 */
#include <iostream>
#include <yaplog.h>

int main(int argc, const char *argv[])
{
    int value = 42;
    const char *cstring = "<Works with cstring>";
    char test[225];

    FLOG() << "This is a fatal message.";
    ALOG() << "Alert triggered by " << value;
    CLOG() << "Critical error detected in C string " << cstring;
    ELOG() << "Even buffer could be logged";
    WLOG() << "See this dump if you set LOGLEVEL=6";
    NLOG() << logger::dump(test, sizeof(test));
    ILOG() << "Information message";
    DLOG() << "Not many people will read this as this is debug";
    TLOG() << "Do not know why I have another level below debug...";

    return EXIT_SUCCESS;
}
