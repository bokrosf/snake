cmake_minimum_required(VERSION 3.29.0)
project(snake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(BUILD_RPATH "${CMAKE_SOURCE_DIR}/lib/SDL")

add_executable("${PROJECT_NAME}"
  src/main.cpp
  src/engine/activatable.cpp
  src/engine/app.cpp
  src/engine/collision/box_collider.cpp
  src/engine/collision/box_collider_renderer.cpp
  src/engine/collision/collision_engine.cpp
  src/engine/component/behavior.cpp
  src/engine/component/component.cpp
  src/engine/component/component_not_found.cpp
  src/engine/component/transformation.cpp
  src/engine/display.cpp
  src/engine/entity.cpp
  src/engine/entity_name_collision.cpp
  src/engine/gameplay_engine.cpp
  src/engine/game_time.cpp
  src/engine/input.cpp
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/engine/object_initializer.cpp
  src/engine/rendering/image_renderer.cpp
  src/engine/rendering/renderer.cpp
  src/engine/rendering/rendering_engine.cpp
  src/engine/scene.cpp
  src/engine/scene_traversal.cpp
  src/engine/scene_loader.cpp
  src/engine/subsystem_initialization_failed.cpp
  src/engine/vector2.cpp
  src/game/food/food.cpp
  src/game/food/food_renderer.cpp
  src/game/food/food_spawner.cpp
  src/game/game_coordinator.cpp
  src/game/scene/classic_scene.cpp
  src/game/scene/game_ending_scene.cpp
  src/game/scene/magic_food_scene.cpp
  src/game/scene/main_scene.cpp
  src/game/scene/pause_scene.cpp
  src/game/scene/scene_navigator.cpp
  src/game/snake_app.cpp
  src/game/snake/movement_system.cpp
  src/game/snake/snake.cpp
  src/game/snake/snake_controller.cpp
  src/game/snake/snake_renderer.cpp
  src/game/snake/tiled_movement_system.cpp
  src/game/special_ability/snake_special_ability.cpp
  src/game/special_ability/special_ability_slot.cpp
  src/game/tile_maze/tile_maze.cpp
  src/game/tile_maze/tile_maze_renderer.cpp
  src/game/ui/border.cpp
  src/game/ui/border_renderer.cpp
  src/game/ui/screen/game_ending_screen.cpp
  src/game/ui/screen/main_screen.cpp
  src/game/ui/screen/menu_screen.cpp
  src/game/ui/screen/pause_screen.cpp
  src/game/wall/wall.cpp
  src/game/wall/wall_renderer.cpp)

target_link_directories("${PROJECT_NAME}"
  PRIVATE "lib/SDL")

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
  PRIVATE "lib/SDL/include")

if(CMAKE_HOST_SYSTEM MATCHES Windows)
  file(COPY "lib/SDL/bin/SDL2.dll" DESTINATION "${PROJECT_BINARY_DIR}")
  file(COPY "lib/SDL/bin/SDL2_image.dll" DESTINATION "${PROJECT_BINARY_DIR}")
endif()

file(COPY "src/game/assets" DESTINATION "${PROJECT_BINARY_DIR}")
