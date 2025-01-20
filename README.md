# micrograd.cpp
A reimplementation of [Microcgrad](https://github.com/karpathy/micrograd) in c++ for educational purposes

## Prerequisites
- >= cmake3(.14)

## Development
- Building. First create the cmake build dir: `cmake3 -S . -B build`. Next run the build itself: `cmake3 --build build`
- Running tests `cmake3 --build build && CTEST_OUTPUT_ON_FAILURE=1 cmake3 --build build --target test`
