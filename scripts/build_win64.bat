@echo off
setlocal enabledelayedexpansion

where cmake >nul 2>nul
if errorlevel 1 (
    echo CMake was not found. Please install CMake for Windows first.
    exit /b 1
)

if "%CMAKE_GENERATOR%"=="" (
    set "CMAKE_GENERATOR=Visual Studio 17 2022"
)

cmake -S . -B build-win64 -G "%CMAKE_GENERATOR%" -A x64 -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 exit /b %errorlevel%

cmake --build build-win64 --config Release
if errorlevel 1 exit /b %errorlevel%

if exist build-win64\Release\guemu.exe (
    echo Built build-win64\Release\guemu.exe
) else if exist build-win64\guemu.exe (
    echo Built build-win64\guemu.exe
) else (
    echo Build completed, but guemu.exe was not found in the expected location.
    exit /b 1
)
