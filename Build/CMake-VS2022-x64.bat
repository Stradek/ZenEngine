@echo off
setlocal

rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

set inputDir=%1
set outputDir=%2
set arch=%3

if [%inputDir%] == [] set inputDir="../."
if [%outputDir%] == [] set outputDir="CMake-VS2022-x64"
if [%arch%] == [] set arch=x64

echo ---- Preparing build directory...
mkdir %outputDir% >nul 2>&1
cd %outputDir%

where /q cmake.exe
if %ERRORLEVEL% EQU 1 (
    goto Error_CMakeNotInstalled
)

echo ---- Generating CMake project for Visual Studio 2022...

set archArg=-A %arch%
cmake.exe -G "Visual Studio 17" %archArg% "../%inputDir%"

if %ERRORLEVEL% NEQ 0 (
    pause
    exit
)

pause
exit

:Error_CMakeNotInstalled
echo "CMake is not installed or not in environmental path."
goto:eof