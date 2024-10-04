#ifndef ENGINE_LOGGING_LOGGER_H
#define ENGINE_LOGGING_LOGGER_H

#include <chrono>
#include <ostream>

class logger
{  
public:
    ~logger() = default;
    static logger &instance();
    void change_destination(std::ostream &destination);
    
    template<typename... Args>
    void debug(Args &&...args);
    
    template<typename... Args>
    void information(Args &&...args);

    template<typename... Args>
    void warning(Args &&...args);

    template<typename... Args>
    void error(Args &&...args);
private:
    enum class log_level
    {
        debug,
        information,
        warning,
        error
    };

    logger();
    std::string level_name(log_level level);
    
    template<typename... Args>
    void write(log_level level, Args &&...args);

    static logger *_instance;
    std::ostream *_destination;
};

template<typename... Args>
void logger::debug(Args &&...args)
{
    write(log_level::debug, args...);
}

template<typename... Args>
void logger::information(Args &&...args)
{
    write(log_level::information, args...);
}

template<typename... Args>
void logger::warning(Args &&...args)
{
    write(log_level::warning, args...);
}

template<typename... Args>
void logger::error(Args &&...args)
{
    write(log_level::error, args...);
}

template<typename... Args>
void logger::write(log_level level, Args &&...args)
{
    *_destination << std::format("{:%H:%M:%S}", std::chrono::system_clock::now());
    *_destination << "|" << level_name(level) << "|";
    (*_destination << ... << args) << std::endl;
}

#endif
