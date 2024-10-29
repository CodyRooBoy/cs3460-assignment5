# CS 3460 Assignment 5 - TypeAhead
## Included Files
### Source Files
- `main.cpp`
- `WordTree.cpp`
- `WordTree.hpp`
- `rlutil.h`
### CMake Build Files
- `CMakeLists.txt`
### Unit Test Files
- `TestWordTree.cpp`

## CMake Targets
- `TypeAhead.exe`
- `UnitTestRunner.exe`

## Run Instructions
Supported on both GCC (`gcc 13.2.0`) and MSVC

In the same folder where the program runs (typically `/build`), the program expects a file named `dictionary.txt` to be present. The CMake file also expects a Clang format file (`_clang-format`).