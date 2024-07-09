# OpenGL Starter Template

<p align="center">
  <img src="github-res/opengl.svg" width="100%" height="144">
</p>

![Build Status](https://github.com/flyingsl0ths/opengl-template/actions/workflows/ci.yaml/badge.svg)

A simple OpenGL (3.3.0) template used to get something up
and running on most Linux distros using C++17

## Setup

## Usage

In the root of the directory

```bash
cmake --preset=<preset-name>

cmake --build build/<preset-binary-dir>

ln -s build/<preset-binary-dir>/compile_commands.json

cd build && ln -s <preset-binary-dir>/app/hello-world exe && cd ..

# See CmakePresets.json for possible values of <preset-binary-dir>
```

## Running

A simple bash script `run.sh` is included (and meant to be run from the `build` directory)
in order to run the built executable
