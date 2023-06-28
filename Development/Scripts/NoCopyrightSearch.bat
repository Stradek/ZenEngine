@echo off
setlocal enabledelayedexpansion

rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

echo This is WIP...maybe some day I will finish it

exit /b 0


set PROJECT_ROOT_DIR="..\\..\\"

set CPP_COPYRIGHT_FORMAT=/*^

	Copyright (c) 2023 Piotr Stradowski. All rights reserved.^
	Software distributed under the permissive MIT License.^
*/

echo !CPP_COPYRIGHT_FORMAT!
pause

rem ^ Two empty lines are required here ^

rem dir "%PROJECT_ROOT_DIR%" /s /b 
rem dir "%PROJECT_ROOT_DIR%\\*.h" /s /b
rem dir "%PROJECT_ROOT_DIR%\\*.hpp" /s /b



call :SearchForFilesWithNoCopyrightRecursively "\\*.cpp" , "^!CPP_COPYRIGHT_FORMAT^!"
exit /b 0

rem #
rem # Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem # Software distributed under the permissive MIT License.
rem #

dir "%PROJECT_ROOT_DIR%\\*.txt" /s /b

rem @echo off
rem setlocal
rem 
rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

dir "%PROJECT_ROOT_DIR%\\*.bat" /s /b



rem     set /p texte=< file.txt  
rem     echo %texte%

:SearchForFilesWithNoCopyrightRecursively
set FILETYPE=%~1
set COPYRIGHT_FORMAT=%~2

echo %FILETYPE%
echo !COPYRIGHT_FORMAT!

rem dir "%PROJECT_ROOT_DIR%" /s /b 
pause
exit /b 0