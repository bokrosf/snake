#ifndef SNAKE_GAME_ASSETS_ASSETPATHS_H
#define SNAKE_GAME_ASSETS_ASSETPATHS_H

#include <string>
#include <filesystem>

namespace asset_paths
{
    const std::string root = std::filesystem::path("assets").string();
    const std::string main_menu_image = std::filesystem::path(root).append("ui/main_menu.png").string();
    const std::string exit_image = std::filesystem::path(root).append("ui/exit.png").string();
    
    const std::string main_title_image = std::filesystem::path(root).append("ui/main_screen/title.png").string();
    const std::string classic_image = std::filesystem::path(root).append("ui/main_screen/classic.png").string();
    const std::string magic_food_image = std::filesystem::path(root).append("ui/main_screen/magic_food.png").string();
    
    const std::string pause_title_image = std::filesystem::path(root).append("ui/pause_screen/title.png").string();
    const std::string resume_image = std::filesystem::path(root).append("ui/pause_screen/resume.png").string();
}

#endif
