#include <exception>
#include <iostream>
#include <engine/app_configuration.h>
#include <engine/logging/logger.h>
#include <game/snake_app.h>

int main(int argc, char *argv[])
{
    logger::instance().change_destination(std::cout);
    snake_app *app = nullptr;

    try
    {
        app = new snake_app(app_configuration{"Snake SDL"});
        app->run();
    }
    catch (const std::exception &ex)
    {
        logger::instance().error(ex.what());
    }

    delete app;

    return 0;
}
