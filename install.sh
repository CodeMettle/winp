#!/bin/bash -ex
mkdir -p src/main/resources
cp -v native/Release/winp.dll src/main/resources/winp.dll
cp -v native/x64/Release/winp.dll src/main/resources/winp.x64.dll
mkdir -p src/main/executables
cp -v native/Release/winpkill.exe src/main/executables/winpkill.exe
cp -v native/x64/Release/winpkill.exe src/main/executables/winpkill64.exe
