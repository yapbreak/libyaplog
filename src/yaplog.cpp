#include "yaplog.h"

__attribute__((destructor)) static void yaplog_static_deinit()
{
    logger::unsetDestinationVariable();
    logger::unsetLevelVariable();
    logger::unsetColorVariable();
}


void logger::setDestinationVariable(const char *dest)
{
    InternalLog::setDestinationVariable(dest);
}

void logger::setLevelVariable(const char *level)
{
    InternalLog::setLevelVariable(level);
}

void logger::setColorVariable(const char *color)
{
    InternalLog::setColorVariable(color);
}

void logger::unsetDestinationVariable()
{
    InternalLog::unsetDestinationVariable();
}

void logger::unsetLevelVariable()
{
    InternalLog::unsetLevelVariable();
}

void logger::unsetColorVariable()
{
    InternalLog::unsetColorVariable();
}
