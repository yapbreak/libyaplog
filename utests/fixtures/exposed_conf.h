#ifndef EXPOSED_CONF_H_HJFINT7T
#define EXPOSED_CONF_H_HJFINT7T

#include "yaplog/conf.h"

class exposed_conf : public logger::conf {
    public:
        exposed_conf(const char *d,
                     const char *l,
                     const char *c,
                     const char *i)
            : logger::conf(d, l, c, i) { }

        const logger::log_level &getSystemLevel() const
        {
            return logger::conf::getSystemLevel();
        }

        std::ostream *getOutput() const
        {
            return logger::conf::getOutput();
        }

        bool getColor() const
        {
            return logger::conf::getColor();
        }

        bool getInfo() const
        {
            return logger::conf::getInfo();
        }
};

#endif /* end of include guard: EXPOSED_CONF_H_HJFINT7T */
