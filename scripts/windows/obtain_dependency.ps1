param(
    [Parameter(Mandatory)]
    $DirectoryName,

    [Parameter(Mandatory)]
    $VersionTag,

    [Parameter(Mandatory)]
    $Url,

    [Parameter(Mandatory)]
    $LibraryDestinationPath,

    [Parameter()]
    $DependencyLibraryName
)

$originalPath = $pwd.Path
$infoText = "$DirectoryName $VersionTag"

echo "Obtaining | $infoText"
git clone --branch $VersionTag --single-branch $Url $DirectoryName
cd $DirectoryName

$cmakeEnvironmentVariables = @("-DCMAKE_BUILD_TYPE=Release")

if ($DependencyLibraryName -ne $null)
{
    $cmakeEnvironmentVariables += "-DCMAKE_PREFIX_PATH=$(Resolve-Path ../$DependencyLibraryName/build/install/)"
}

mkdir build
cd build
cmake -G "MinGW Makefiles" @cmakeEnvironmentVariables ..
cmake --build .
mkdir install
cmake --install . --prefix install/

echo "Copying binaries | $infoText"
cp install/bin $LibraryDestinationPath -Recurse -Force
echo "Copying libs | $infoText"
cp install/lib/lib* $LibraryDestinationPath
echo "Copying headers | $infoText"
cp install/include $LibraryDestinationPath -Recurse -Force

echo "Finished obtaining | $infoText"
cd $originalPath