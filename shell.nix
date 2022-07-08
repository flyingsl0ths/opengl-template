{ pkgs ? import <nixpkgs> { } }:
with pkgs; mkShell {
  nativeBuildInputs = [
    cmake
    clang-tools_14
    clang_14
    cmake-format
    extra-cmake-modules
    glfw
    ninja
    pkg-config
    # OPTIONAL
    nixpkgs-fmt
    shfmt
  ];
}
