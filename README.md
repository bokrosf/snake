# Getting started

The project uses [CMake](https://cmake.org/) as a project and build system generator.

1. Clone the repositoty ```git clone https://github.com/bokrosf/snake```

2. Setup the project with the platform specific init script. It generates a Debug mode build system with CMake and obtains the 3rd party libraries, copies their headers to the newly created lib folder.
    - Linux: [```scripts/linux/init.sh```](scripts/linux/init.sh) uses the default CMake generator.
    - Windows: [```scripts/windows/init.ps1```](scripts/windows/init.ps1) uses **MinGW MakeFiles** generator but it can be modified by editing the **init.ps1** file. [MinGW releases](https://github.com/niXman/mingw-builds-binaries/releases)

3. Build the project
   1. ```cd build/debug```
   2. ```cmake --build .```

4. Create Release mode build system
   1. ```mkdir -p build/release```
   2. ```cd build/release```
   3. ```cmake -DCMAKE_BUILD_TYPE=Release ..``` If necessary specify the generator. For example to use **MinGW** on Windows: ```cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release```
