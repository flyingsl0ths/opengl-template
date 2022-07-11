{ pkgs ? import <nixpkgs> { } }:
with pkgs; mkShell {
  nativeBuildInputs = [
    clang_14
    clang-tools_14
    cmake
    cmake-format
    cmake-language-server # OPTIONAL
    extra-cmake-modules
    glfw
    ninja
    nixpkgs-fmt # OPTIONAL
    pkg-config
    shfmt # OPTIONAL
  ];
}
