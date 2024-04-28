# Getting started

1. Install the tools used for development. They are not mandatory just what I preferer to work with. Run the [```install_development_tools.ps1```](scripts/install_development_tools.ps1) file found in ```scripts``` folder.
2. Create the build system used by CMake. 
   1. Create a folder for the build system. ```mkdir build```
   2. Navigate to the folder. ```cd build```
   3. Generate a build system. For example using MinGW. ```cmake -G "MinGW Makefiles" <path_to_CMakeLists.txt>```
3. Build the project using the generated build system. Navigate to the build system's folder and build the project. ```cmake --build .```
