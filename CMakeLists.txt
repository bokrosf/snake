cmake_minimum_required(VERSION 3.29.0)
project(snake)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(snake
  src/main.cpp
  src/game_engine/activatable.cpp
  src/game_engine/app.cpp
  src/game_engine/game_object.cpp
  src/game_engine/game_time.cpp
  src/game_engine/input.cpp
  src/game_engine/scene.cpp
  src/game_engine/subsystem_initialization_failed.cpp
  src/game_engine/vector2.cpp
  src/game_engine/collision/box_collider.cpp
  src/game_engine/collision/box_collider_renderer.cpp
  src/game_engine/collision/collision_engine.cpp
  src/game_engine/component/behavior.cpp
  src/game_engine/component/component.cpp
  src/game_engine/component/component_not_found.cpp
  src/game_engine/component/renderer.cpp  
  src/game_engine/logging/logger.cpp
  src/game_engine/messaging/messenger.cpp
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
