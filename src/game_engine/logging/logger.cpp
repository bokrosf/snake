#include <sstream>
#include "logger.h"

logger *logger::_instance = nullptr;

logger::logger()
    : _destination(nullptr)
{
}

logger &logger::instance()
{
    if (!_instance)
    {
        _instance = new logger();
    }
    
    return *_instance;
}

void logger::change_destination(std::ostream &destination)
{
    _destination = &destination;
}

std::ostream &logger::debug()
{
    return write(log_level::debug);
}

std::ostream &logger::information()
{
    return write(log_level::information);
}

std::ostream &logger::warning()
{
    return write(log_level::warning);
}

std::ostream &logger::error()
{
    return write(log_level::error);
}

inline std::string logger::level_name(log_level level)
{
    switch (level)
    {
        case log_level::debug:
            return "DEBUG";
        case log_level::information:
            return "INFO";
        case log_level::warning:
            return "WARNING";
        case log_level::error:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

std::ostream &logger::write(log_level level)
{
    // TODO 2024-04-12 TimeStamp part needed.
    return *_destination << "<TimeStamp>|" << level_name(level) << "|";
}
