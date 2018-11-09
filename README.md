# metaxxa
C++ header-only library for meta programming

## Getting library header
See [releases](https://github.com/MrShiposha/metaxxa/releases)

## Tested compilers
 * **Visual Studio 2017** -- works ✔️
 * **Apple LLVM version 10.0.0 (clang-1000.11.54.4)** -- works ✔️
 * **MinGW** -- unsupported ❌ 

## How to build tests
**CMake minimum version 3.12 is required**

`git clone https://github.com/MrShiposha/metaxxa.git`

`cd metaxxa`

`mkdir build`

`cd build`

----
### Platform dependent
#### Windows
`cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 2017 Win64"`

#### macOS
`cmake .. -DCMAKE_BUILD_TYPE=Debug -GXcode`

----
`cmake --build .`

## Run tests
`{metaxxa_directory}/build/tests/Debug/metaxxa-tests`

OR `{metaxxa_directory}/build/tests/Release/metaxxa-tests`

OR `{metaxxa_directory}/build/tests/metaxxa-tests`

Actual path depends on CMake generator and CMAKE_BUILD_TYPE value
