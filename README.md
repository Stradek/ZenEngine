# DX12EngineTest
This game engine is still work in progress. Name of this software still haven't been determined and will change in the future.

# Repositiory Directory Structure
* Binaries/ - Build artifacts(files like .lib, .pdb) and executable(.exe)
* Build/ - CMake related artifacts(in .\CMake-* directory), shared CMake configuration and functions(CMakeShared.cmake) and CMake related batch scripts.
* Development/ - Source code related to the engine
* Development/External - external libraries
* Development/Include - project headers code
* Development/Scripts - automation scripts supporting development process
* Development/Source - project source code

# Prerequisities
1. Visual Studio 2022
2. CMake (look for proper version in CMakeLists.txt)
3. Windows SDK

# Building
1. $ git clone --recursive https://github.com/Stradek/DX12EngineTest.git
2. $ cd .\DX12EngineTest\
3. $ .\BuildSolution-VS2022.bat
4. $ .\OpenSolution-VS2022.bat
5. Build & Run solution
6. Enjoy!

# License
MIT License

Copyright (c) 2023 Piotr Stradowski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.