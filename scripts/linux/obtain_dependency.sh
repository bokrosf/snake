#!/bin/bash

original_path=$(pwd)
directory_name=$1
version_tag=$2
url=$3
binary_destination_path=$4
header_destination_path=$5
info_text="$directory_name $version_tag"

echo "Obtaining | $info_text"
git clone --branch $version_tag --single-branch $url $directory_name
cd $directory_name
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

echo "Copying binaries | $info_text"
cp lib* $binary_destination_path
echo "Copying headers | $info_text"
cp ../include/*.h $header_destination_path

echo "Finished obtaining | $info_text"
cd $original_path