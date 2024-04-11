#include <iostream>
#include "console_logger.h"

void console_logger::initialize()
{
    delete _instance;
    _instance = new console_logger();
}

void console_logger::write_to_output(const std::string &message)
{
    std::cout << message << std::endl;
}
