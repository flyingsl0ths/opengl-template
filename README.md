# OpenGL Starter Template

<p align="center">
  <img src="github-res/opengl.svg" width="100%" height="144">
</p>

A simple OpenGL (3.3.0) template used to get something up
and running on most Linux distros using C++20

## Setup

## Usage

In the root of the directory

```bash
cmake --preset=<preset-name>

cmake --build build/<preset-binary-dir>

ln -s build/<preset-binary-dir>/compile_commands.json

# See CmakePresets.json for possible values of <preset-binary-dir>
```

## Running

A simple bash script `run.sh` is included (and meant to be run from the `build` directory)
in order to run the built executable
