#include <exception>
#include <iostream>
#include <game_engine/app.h>
#include <game_engine/logging/logger.h>
#include <game/snake_app.h>

int main(int argc, char *argv[])
{
    logger::instance().change_destination(std::cout);
    
    try
    {
        app *app = new snake_app();
        app->run();

        return 0;
    }
    catch (const std::exception &ex)
    {
        logger::instance().error(ex.what());
        return 1;
    }
}
