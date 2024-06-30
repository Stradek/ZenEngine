# Zen Engine
[![license](https://badgen.net/github/license/stradek/ZenEngine?color=blue)](https://github.com/Stradek/ZenEngine/blob/main/LICENSE)

**NOTE**: This repository has been archived. I fell into the same rabbit hole as other starting core tech engineers - I did not set up realistic goal. Don't be like me in the past. I also changed my interest a little bit and started new game engine project which should be highlighted on my Github profile. Cheers!

# Description
Zen Engine is my hobbyist long-term C++ game engine project, a testament to my passion for creating exceptional high-performance, real-time game engines. In this iteration, I'm focused on building a robust foundation for my future, more advanced iterations on this game engine.

All systems are subject to change in the future.

# Key Features
  - custom memory allocators
  - decoupled game and editor projects, as well as engine and it's systems
  - custom, in-engine runtime performance measurement system
  - simple cmake setup
  - tracy integration
  - spdlog integration

# Project Objectives
  - (In Progress) Memory Management: Implement memory management with custom memory allocators: GeneralAllocator, SlabAllocator, PoolAllocator...
  - (In Progress) Multithreading: Develop simple job system. NOTE: Would like to integrate the one I developed in CoreMatrixToolkit.
  - Game Genre: Create a 2D platformer game.
  - Core Game Mechanics: Implement jumping, running at constant speed, and collecting points.
  - Game Level Design: Design levels with straightforward platform layouts, combining horizontal and vertical segments. Emulate classic arcade gaming simplicity.

# Prerequisities
1. Visual Studio 2022
2. CMake (look for proper version in CMakeLists.txt)

# Configuration
1. $ git clone https://github.com/Stradek/ZenEngine.git
2. $ cd .\ZenEngine\
3. $ .\BuildSolution-VS2022.bat
4. $ .\OpenSolution-VS2022.bat
5. Build & Run **Game** project
6. Enjoy!

# Repositiory Directory Structure
* Binaries/ - compilation artifacts(libraries and symbolos) and executables
* Build/ - project build directory
* Development/ - Zen Engine and Game development related directory
* Development/External - external libraries
* Development/Internal - internal libraries and tools
* Development/Scripts - automation scripts supporting development process
* Development/Source - Zen Engine and Game source code

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
