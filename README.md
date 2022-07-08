# OpenGL Starter Template

A simple OpenGL (3.3.0) template used to get something up
and running on most Linux distros as well as NixOs using C++17

## Setup

Run `nix-shell` beforehand unless the project is being loaded in
vscode/vscodium and the [Nix Extension Pack](https://marketplace.visualstudio.com/items?itemName=pinage404.nix-extension-pack)
extension is installed, then this will be done automatically

If on NixOs omit the `-DFETCH_GLFW` flag _(this is optional and can be arbitrarily set)_ when running `cmake`;
However the `-DFETCH_GLM` flag is required to be set to `TRUE` as `glm` when specified
as a `nativeBuildInput` in `shell.nix` results in a **linker error** when the project is built

## Running

A simple bash script `run.sh` is also included (and meant to be run from the `build` directory)
in order to run the example code

_**Note**_

It is important to not mix c/c++ compilers as clangd will not work properly:
e.g. if using `clang` `-DCMAKE_CXX_COMPILER` must be set to `clang++` and
`-DCMAKE_C_COMPILER` must be set to `clang`

```bash
mkdir -p build && cd build

cmake -G <CMAKE-SUPPORTED-BUILD-TOOL> -DCMAKE_CXX_COMPILER=<CMAKE-COMPILER-ID> -DCMAKE_C_COMPILER=<CMAKE-COMPILER-ID> -DFETCH_GLM=TRUE/FALSE -DFETCH_GLFW=TRUE/FALSE

cmake --build .

ln -s app/<PROJECT-NAME> exe && cd .. && ln -s build/compile_commands.json .
```
