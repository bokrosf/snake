#ifndef SNAKE_GAME_ASSETS_ASSETPATH_H
#define SNAKE_GAME_ASSETS_ASSETPATH_H

#include <string>
#include <filesystem>

namespace asset_path
{
    const std::string root = std::filesystem::path("assets").string();
    const std::string main_menu_image = std::filesystem::path(root).append("ui/main_menu.png").string();
    const std::string exit_image = std::filesystem::path(root).append("ui/exit.png").string();
    
    const std::string main_title_image = std::filesystem::path(root).append("ui/main_screen/title.png").string();
    const std::string classic_image = std::filesystem::path(root).append("ui/main_screen/classic.png").string();
    const std::string magic_food_image = std::filesystem::path(root).append("ui/main_screen/magic_food.png").string();
    
    const std::string pause_title_image = std::filesystem::path(root).append("ui/pause_screen/title.png").string();
    const std::string resume_image = std::filesystem::path(root).append("ui/pause_screen/resume.png").string();

    const std::string game_won_title = std::filesystem::path(root).append("ui/game_ending/game_won_title.png").string();
    const std::string game_lost_title = std::filesystem::path(root).append("ui/game_ending/game_lost_title.png").string();
    const std::string restart_image = std::filesystem::path(root).append("ui/game_ending/restart.png").string();
}

#endif
