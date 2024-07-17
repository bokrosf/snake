echo "Initializing project..."

$originalPath = $pwd.Path
cd $PSScriptRoot
cd ../..
$projectPath = $pwd.Path
echo "Creating directories..."
mkdir build
mkdir -p lib/SDL
mkdir dependencies
echo "Finished creating directories."

echo "Obtaining dependencies..."
cd dependencies
& $PSScriptRoot/obtain_dependency.ps1 `
  -DirectoryName "SDL" `
  -VersionTag "release-2.30.2" `
  -Url "https://github.com/libsdl-org/SDL" `
  -LibraryDestinationPath "$projectPath/lib/SDL/"

& $PSScriptRoot/obtain_dependency.ps1 `
  -DirectoryName "SDL_image" `
  -VersionTag "release-2.8.2" `
  -Url "https://github.com/libsdl-org/SDL_image" `
  -LibraryDestinationPath "$projectPath/lib/SDL/" `
  -DependencyLibraryName "SDL"

cd $projectPath
echo "Finished obtaining dependencies."

echo "Creating build system..."
cd build
cmake -G "MinGW Makefiles" ..
cd $projectPath
echo "Finished creating build system."

rm -Recurse -Force $projectPath/dependencies
cd $originalPath
echo "Finished project initialization."