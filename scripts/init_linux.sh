#!/bin/sh

echo "Initializing project..."
script_path=$(pwd)
cd ..
project_path=$(pwd)
echo "Creating directories..."
mkdir build
mkdir -p lib/SDL/include/SDL2
mkdir dependencies
echo "Finished creating directories."

echo "Obtaining dependencies..."
cd dependencies
$script_path/obtain_dependency.sh "SDL" "release-2.30.2" "https://github.com/libsdl-org/SDL" "$project_path/lib/SDL/" "$project_path/lib/SDL/include/SDL2/"
$script_path/obtain_dependency.sh "SDL_image" "release-2.8.2" "https://github.com/libsdl-org/SDL_image" "$project_path/lib/SDL/" "$project_path/lib/SDL/include/SDL2/"
cd $project_path
echo "Finished obtaining dependencies."

echo "Creating build system..."
cd build
cmake ..
cd $project_path
echo "Finished creating build system."

rm -rf $project_path/dependencies
echo "Finished project initialization."