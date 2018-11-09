# metaxxa
C++ header-only library for meta programming

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
