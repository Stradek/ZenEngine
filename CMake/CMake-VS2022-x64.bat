@echo off
setlocal

rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

set myPath=%~dp0
set sourceDir=%1
set buildDir=%2
set arch=%3
set presetsFile=%4

if [%sourceDir%] == [] set sourceDir="%myPath%\.."
if [%buildDir%] == [] set buildDir="%sourceDir%\Build\CMake-VS2022-x64"
if [%arch%] == [] set arch="x64"

echo ---- Preparing build directory...
mkdir %buildDir% >nul 2>&1

where /q cmake.exe
if %ERRORLEVEL% NEQ 0 (
    goto Error_CMakeNotInstalled
)

echo ---- Generating CMake project for Visual Studio 2022...

cmake.exe -G "Visual Studio 17" -S %sourceDir% -B %buildDir% -A %arch%

if %ERRORLEVEL% NEQ 0 (
    goto Error_CMakeBuildingProjectFailed
)

pause
exit

:Error_CMakeNotInstalled
echo "CMake is not installed or not in environmental path."
goto:eof

:Error_CMakeBuildingProjectFailed
echo "CMake failed to build the project for Visual Studio 2022."
goto:eof
