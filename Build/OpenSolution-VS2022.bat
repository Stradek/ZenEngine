@echo off
setlocal

rem Copyright (c) 2023 Piotr Stradowski. All rights reserved.
rem Software distributed under the permissive MIT License.

echo ---- Opening project solution...
for /f %%f in ('dir /s /b "*.sln"') do (
    set solution=%%f
    goto SolutionFound
)
pause
exit

:SolutionFound
start "" "%solution%"
goto:eof