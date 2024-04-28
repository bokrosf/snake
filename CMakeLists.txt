cmake_minimum_required(VERSION 3.29.0)
project(snake)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(snake
  src/main.cpp
  src/engine/activatable.cpp
  src/engine/app.cpp
  src/engine/entity.cpp
  src/engine/game_time.cpp
  src/engine/input.cpp
  src/engine/scene_traversal.cpp
  src/engine/scene.cpp
  src/engine/subsystem_initialization_failed.cpp
  src/engine/vector2.cpp
  src/engine/collision/box_collider.cpp
  src/engine/collision/box_collider_renderer.cpp
  src/engine/collision/collision_engine.cpp
  src/engine/component/behavior.cpp
  src/engine/component/component.cpp
  src/engine/component/component_not_found.cpp
  src/engine/component/renderer.cpp  
  src/engine/logging/logger.cpp
  src/engine/messaging/messenger.cpp
  src/game/food/food.cpp
  src/game/food/food_renderer.cpp
  src/game/snake_app.cpp
  src/game/snake/movement_system.cpp
  src/game/snake/snake.cpp
  src/game/snake/snake_controller.cpp
  src/game/snake/snake_renderer.cpp
  src/game/snake/tiled_movement_system.cpp
  src/game/special_ability/snake_special_ability.cpp
  src/game/special_ability/special_ability_slot.cpp
  src/game/scene/test_scene.cpp
  src/game/terrain/tile_renderer.cpp
  src/game/wall/wall.cpp
  src/game/wall/wall_renderer.cpp)

target_link_directories(snake
  PRIVATE "lib/SDL2-2.30.2")

target_link_libraries(snake
  PRIVATE "mingw32"
  PRIVATE "SDL2main"
  PRIVATE "SDL2")

target_include_directories(snake
  PRIVATE "src"
  PRIVATE "lib/SDL2-2.30.2/include")

file(COPY "lib/SDL2-2.30.2/bin/SDL2.dll" DESTINATION "${PROJECT_BINARY_DIR}")
