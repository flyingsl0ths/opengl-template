{ pkgs ? import <nixpkgs> { } }:
with pkgs; mkShell {
  nativeBuildInputs = [
    clang-tools_14
    cmake
    cmake-format
    cmake-language-server
    extra-cmake-modules
    git
    glfw
    lldb_14
    llvmPackages_14.clang
    llvmPackages_14.libcxxStdenv
    ninja
    nixpkgs-fmt
    pkg-config
    shellcheck
    shfmt
  ];
}
