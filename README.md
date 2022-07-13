# OpenGL Starter Template

![Build Status](https://github.com/flyingsl0ths/opengl-template/actions/workflows/ci.yaml/badge.svg)

A simple OpenGL (3.3.0) template used to get something up
and running on most Linux distros as well as NixOs using C++17

## Setup

### NixOs

If creating a new preset or building manually omit the `-DFETCH_GLFW` flag
_(this is optional and can be arbitrarily set)_ when running `cmake`;
However the `-DFETCH_GLM` flag is required to be set to `TRUE` as `glm` when specified
as a `nativeBuildInput` in `shell.nix` results in a **linker error** when the project is built

_**Note**_

It is important to not mix c/c++ compilers as clangd will not work properly:
e.g. if using `clang` `-DCMAKE_CXX_COMPILER` must be set to `clang++` and
`-DCMAKE_C_COMPILER` must be set to `clang`

## Running

A simple bash script `run.sh` is included (and meant to be run from the `build` directory)
in order to run the example code
