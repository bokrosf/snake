#!/bin/bash

original_path="$(pwd)"
directory_name="$1"
version_tag="$2"
url="$3"
library_destination_path="$4"
dependency_library_name="$5"
info_text="$directory_name $version_tag"

echo "Obtaining | $info_text"
git clone --branch $version_tag --single-branch $url $directory_name
mkdir -p "$directory_name/build/install"
cmake_environment_variables="-DCMAKE_BUILD_TYPE=Release"

if [ -n "$dependency_library_name" ]
then
  cmake_environment_variables="$cmake_environment_variables -DCMAKE_PREFIX_PATH="$(realpath "$dependency_library_name/build/install/")""
fi

cd "$directory_name/build"
cmake $cmake_environment_variables ..
cmake --build .
cmake --install . --prefix install/

echo "Copying libraries | $info_text"
cp install/lib/lib* "$library_destination_path"
echo "Copying headers | $info_text"
cp -r install/include "$library_destination_path"

echo "Finished obtaining | $info_text"
cd "$original_path"