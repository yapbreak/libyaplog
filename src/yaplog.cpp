#include "yaplog.h"

__attribute__((constructor)) static void yaplog_static_init()
{
    logger::setDestinationVariable(YAPLOG_DEST_DEFAULT);
    logger::setLevelVariable(YAPLOG_LEVEL_DEFAULT);
}

__attribute__((destructor)) static void yaplog_static_deinit()
{
    logger::unsetDestinationVariable();
    logger::unsetLevelVariable();
}


void logger::setDestinationVariable(const char *dest)
{
    InternalLog::setDestinationVariable(dest);
}

void logger::setLevelVariable(const char *level)
{
    InternalLog::setLevelVariable(level);
}

void logger::unsetDestinationVariable()
{
    InternalLog::unsetDestinationVariable();
}

void logger::unsetLevelVariable()
{
    InternalLog::unsetLevelVariable();
}
