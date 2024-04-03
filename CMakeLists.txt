cmake_minimum_required(VERSION 3.29.0)
project(snake)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(snake
  src/main.cpp
  src/game_engine/activatable.cpp
  src/game_engine/game_object.cpp
  src/game_engine/time.cpp
  src/game_engine/vector2.cpp
  src/game_engine/component/behavior.cpp
  src/game_engine/component/component.cpp
  src/game_engine/component/component_not_found.cpp
  src/game_engine/messaging/messenger.cpp
  src/game/gameplay/snake/movement_system.cpp
  src/game/gameplay/snake/snake.cpp
  src/game/gameplay/snake/tiled_movement_system.cpp)

target_include_directories(snake
  PRIVATE "src")
