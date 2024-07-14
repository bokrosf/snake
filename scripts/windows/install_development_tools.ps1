Set-ExecutionPolicy Bypass -Scope Process -Force; iwr https://community.chocolatey.org/install.ps1 -UseBasicParsing | iex

choco install mingw -y
choco install git -y
choco install cmake -y
