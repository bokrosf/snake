#ifndef SNAKE_GAMEENGINE_LOGGING_LOGGER_H
#define SNAKE_GAMEENGINE_LOGGING_LOGGER_H

#include <string>

class logger
{
private:
    enum class log_level
    {
        debug,
        information,
        warning,
        error
    };
public:
    virtual ~logger() = default;
    static logger &instance();
    void debug(const std::string &message);
    void information(const std::string &message);
    void warning(const std::string &message);
    void error(const std::string &message);
protected:
    logger() = default;
    static logger *_instance;
    virtual void write_to_output(const std::string &message) = 0;
private:
    inline std::string level_name(log_level level);
    void write(log_level level, const std::string &message);
};

#endif
