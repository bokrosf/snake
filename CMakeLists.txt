cmake_minimum_required(VERSION 3.29.0)
project(snake)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SDL_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lib/SDL")

FetchContent_Declare(
  sdl2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG f461d91cd265d7b9a44b4d472b1df0c0ad2855a0 # release-2.30.2
)

FetchContent_Declare(
  sdl2_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
  GIT_TAG abcf63aa71b4e3ac32120fa9870a6500ddcdcc89 # release-2.8.2
)

FetchContent_MakeAvailable(sdl2 sdl2_image)
file(COPY "${sdl2_SOURCE_DIR}/include/" DESTINATION "${SDL_LIBRARY_PATH}/include/SDL2")
file(COPY "${sdl2_image_SOURCE_DIR}/include/" DESTINATION "${SDL_LIBRARY_PATH}/include/SDL2")

add_executable("${PROJECT_NAME}"
  src/engine/activatable.cpp
  src/engine/app.cpp
  src/engine/collision/box_collider.cpp
  src/engine/collision/box_collider_renderer.cpp
  src/engine/collision/collision_engine.cpp
  src/engine/component/component.cpp
  src/engine/component/component_not_found.cpp
  src/engine/component/transform.cpp
  src/engine/component/updatable.cpp
  src/engine/display.cpp
  src/engine/entity.cpp
  src/engine/entity_name_collision.cpp
  src/engine/gameplay_engine.cpp
  src/engine/input.cpp
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/engine/object_initializer.cpp
  src/engine/rendering/image_renderer.cpp
  src/engine/rendering/renderer.cpp
  src/engine/rendering/rendering_engine.cpp
  src/engine/scene.cpp
  src/engine/scene_loader.cpp
  src/engine/subsystem_initialization_failed.cpp
  src/engine/time/game_time.cpp
  src/engine/time/time_point.cpp
  src/game/ability/ability.cpp
  src/game/ability/ability_indicator.cpp
  src/game/ability/ability_indicator_renderer.cpp
  src/game/ability/ability_slot.cpp
  src/game/ability/inverted_snake_controller.cpp
  src/game/ability/slow_down.cpp
  src/game/ability/speed_boost.cpp
  src/game/ability/wall_bouncing.cpp
  src/game/bouncing_collision_handler.cpp
  src/game/fatal_collision_handler.cpp
  src/game/food/food.cpp
  src/game/food/food_renderer.cpp
  src/game/food/food_spawner.cpp
  src/game/food/magic_food_factory.cpp
  src/game/food/normal_food_factory.cpp
  src/game/food/reverter_food.cpp
  src/game/game_coordinator.cpp
  src/game/main.cpp
  src/game/scene/classic_scene.cpp
  src/game/scene/game_ending_scene.cpp
  src/game/scene/magic_food_scene.cpp
  src/game/scene/main_scene.cpp
  src/game/scene/pause_scene.cpp
  src/game/scene/scene_navigator.cpp
  src/game/snake_app.cpp
  src/game/snake/snake.cpp
  src/game/snake/snake_controller.cpp
  src/game/snake/snake_renderer.cpp
  src/game/tile_maze/tile_maze.cpp
  src/game/tile_maze/tile_maze_renderer.cpp
  src/game/ui/border.cpp
  src/game/ui/border_renderer.cpp
  src/game/ui/screen/game_ending_screen.cpp
  src/game/ui/screen/main_screen.cpp
  src/game/ui/screen/menu_screen.cpp
  src/game/ui/screen/pause_screen.cpp
  src/game/wall/wall_renderer.cpp)

if(CMAKE_HOST_SYSTEM MATCHES Windows)
  target_link_libraries("${PROJECT_NAME}"
    PRIVATE "mingw32")
endif()

target_link_libraries("${PROJECT_NAME}"
  PRIVATE "SDL2main"
  PRIVATE "SDL2"
  PRIVATE "SDL2_image")

target_include_directories("${PROJECT_NAME}"
  PRIVATE "src"
  PRIVATE "${SDL_LIBRARY_PATH}/include"
)

set(SDL2_DLL "${sdl2_BINARY_DIR}/SDL2.dll")
set(SDL2_IMAGE_DLL "${sdl2_image_BINARY_DIR}/SDL2_image.dll")

if(CMAKE_HOST_SYSTEM MATCHES Windows)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(SDL2_DLL "${sdl2_BINARY_DIR}/SDL2d.dll")
    set(SDL2_IMAGE_DLL "${sdl2_image_BINARY_DIR}/SDL2_imaged.dll")
  endif()

  add_custom_command(
    TARGET "${PROJECT_NAME}"
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_DLL}" "${PROJECT_BINARY_DIR}/"
    COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_IMAGE_DLL}" "${PROJECT_BINARY_DIR}/"
    VERBATIM)
endif()

file(COPY "src/game/assets" DESTINATION "${PROJECT_BINARY_DIR}")
