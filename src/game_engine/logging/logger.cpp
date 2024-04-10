#include <sstream>
#include "logger.h"

logger *logger::_instance = nullptr;

logger &logger::instance()
{
    return *_instance;
}

void logger::debug(const std::string &message)
{
    write(log_level::debug, message);
}

void logger::information(const std::string &message)
{
    write(log_level::information, message);
}

void logger::warning(const std::string &message)
{
    write(log_level::warning, message);
}

void logger::error(const std::string &message)
{
    write(log_level::error, message);
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

void logger::write(log_level level, const std::string &message)
{
    std::ostringstream stream;
    stream << "<TimeStamp>|" << level_name(level) << "|" << message;
    write_to_output(stream.str());
}
