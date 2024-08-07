#!/bin/sh

echo "Initializing project..."
original_path=$(pwd)
script_path="$(dirname "$(realpath "$0")")"
cd $script_path;
cd ../..
project_path=$(pwd)
echo "Creating directories..."
mkdir build
mkdir -p lib/SDL
mkdir dependencies
echo "Finished creating directories."

echo "Obtaining dependencies..."
cd dependencies

$script_path/obtain_dependency.sh \
  "SDL" \
  "release-2.30.2" \
  "https://github.com/libsdl-org/SDL" \
  "$project_path/lib/SDL/" \

$script_path/obtain_dependency.sh \
  "SDL_image" \
  "release-2.8.2" \
  "https://github.com/libsdl-org/SDL_image" \
  "$project_path/lib/SDL/" \
  "SDL"

cd $project_path
echo "Finished obtaining dependencies."

echo "Creating build system..."
cd build
cmake ..
cd $project_path
echo "Finished creating build system."

rm -rf $project_path/dependencies
cd $original_path
echo "Finished project initialization."