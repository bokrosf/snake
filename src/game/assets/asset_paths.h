#ifndef SNAKE_GAME_ASSETS_ASSETPATHS_H
#define SNAKE_GAME_ASSETS_ASSETPATHS_H

#include <string>
#include <filesystem>

namespace asset_paths
{
    const std::string root = std::filesystem::path("assets").string();
    const std::string exit_image = std::filesystem::path(root).append("ui/exit.png").string();
    const std::string pause_title_image = std::filesystem::path(root).append("ui/pause_screen/title.png").string();
    const std::string resume_image = std::filesystem::path(root).append("ui/pause_screen/resume.png").string();
}

#endif
