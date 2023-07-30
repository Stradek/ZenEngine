@echo off
setlocal

rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

set buildDir="CMake-VS2022-x64"

if not exist %buildDir% (
    goto :Error_CMakeDirectoryNotExist
)

echo ---- Removing build directory...

rd /s /q %buildDir%

if %ERRORLEVEL% NEQ 0 (
    pause
    exit
)

pause
exit

:Error_CMakeDirectoryNotExist
echo "Could not find CMake directory."
pause
goto:eof