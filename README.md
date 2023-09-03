# SDLEngineTest
This game engine is still work in progress. Name of this software still haven't been determined and will change in the future.

# Project Short-Term Goals
- Finishing custom memory allocation systems which includes:
- Finishing GeneralAllocator
- Finishing Handles implementationand other interfaces for managing allocated memory and pointers
- Finishing SlabAllocator implementation
- Figuring out a way to implement allocators with dynamic memory allocations like PoolAllocator or ResizablePoolAllocator
- Moveing all heap allocated data to custom allocators
- Ensuring that custom allocation is "working"(tbd)

# Project Long-Term Goals
1. Game Genre: I want to develop a simple 2D platformer game.
2. Game Mechanics: I want to implement core mechanics such as jumping, running with one default speed, collecting points. I would like to have also moving platforms that maintain the player's relative position while standing on them.
3. Level Design: I want to create levels without organic elements, hazards, puzzles, secrets, or checkpoints. The levels will consist of both horizontal and vertical parts, with a simplified layout and clear path indicators. I want to keep it simple as in old days.
4. Engine main goals: memory management with custom allocators and multithreaded job system.

# Repositiory Directory Structure
* Binaries/ - compilation artifacts(libraries and symbolos) and executables
* Build/CMake-*/ - project build directory
* Development/ - engine and game development related directory
* Development/External - external libraries
* Development/Internal - internal libraries and tools
* Development/Include - project headers code
* Development/Scripts - automation scripts supporting development process
* Development/Source - project source code

# Prerequisities
1. Visual Studio 2022
2. CMake (look for proper version in CMakeLists.txt)

# Building
1. $ git clone --recursive https://github.com/Stradek/DX12EngineTest.git
2. $ cd .\DX12EngineTest\
3. $ .\BuildSolution-VS2022.bat
4. $ .\OpenSolution-VS2022.bat
5. Build & Run Game project
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
