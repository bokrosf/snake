#!/bin/sh

echo "Initializing project..."
script_path="$(dirname "$(realpath "$0")")"
cd "$script_path"
cd ../..
project_path=$(pwd)

echo "Creating build system..."
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug "$project_path"
echo "Finished creating build system."
echo "Finished project initialization."