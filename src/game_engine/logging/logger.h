#ifndef SNAKE_GAMEENGINE_LOGGING_LOGGER_H
#define SNAKE_GAMEENGINE_LOGGING_LOGGER_H

#include <ostream>

class logger
{  
public:
    virtual ~logger() = default;
    static logger &instance();
    void change_destination(std::ostream &destination);
    std::ostream &debug();
    std::ostream &information();
    std::ostream &warning();
    std::ostream &error();
private:
    enum class log_level
    {
        debug,
        information,
        warning,
        error
    };

    static logger *_instance;
    std::ostream *_destination;
    logger();
    inline std::string level_name(log_level level);
    std::ostream &write(log_level level);
};

#endif
