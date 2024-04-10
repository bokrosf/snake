#ifndef SNAKE_GAMEENGINE_LOGGING_CONSOLELOGGER_H
#define SNAKE_GAMEENGINE_LOGGING_CONSOLELOGGER_H

#include "logger.h"

class console_logger : public logger
{
public:
    static void initialize();
protected:
    console_logger() = default;
    void write_to_output(const std::string &message) override;
};

#endif
