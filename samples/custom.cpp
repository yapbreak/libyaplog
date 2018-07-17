/**
 * This is a simple yaplog sample.
 *
 * To compile this sample, use the following commands:
 *
 * g++ -o custom.o -c custom.cpp $(pkg-config --cflags yaplog)
 * g++ -o custom custom.o $(pkg-config --libs yaplog)
 *
 * Then, set variable Customvariable and Customdestination to control logs
 * output.
 */
#include <iostream>
#include <yaplog.h>

int main(int argc, const char *argv[])
{
    logger::setLevelVariable("Customvariable");
    logger::setDestinationVariable("Customdestination");

    int value = 42;
    const char *cstring = "<Works with cstring>";
    char test[225];

    FLOG() << "This is a fatal message.";
    ALOG() << "Alert triggered by " << value;
    CLOG() << "Critical error detected in C string " << cstring;
    ELOG() << "Even buffer could be logged";
    WLOG() << "See this dump if you set Customvariable=6";
    NLOG() << logger::dump(test, sizeof(test));
    ILOG() << "Information message";
    DLOG() << "Not many people will read this as this is debug";
    TLOG() << "Do not know why I have another level below debug...";

    return EXIT_SUCCESS;
}
