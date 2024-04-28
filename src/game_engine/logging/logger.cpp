#include <sstream>
#include <game_engine/logging/logger.h>

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

std::string logger::level_name(log_level level)
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
