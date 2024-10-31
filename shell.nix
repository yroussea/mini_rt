{ pkgs ? import <nixpkgs> {} }:

let
  stdenv = pkgs.llvmPackages_19.stdenv;
in
  pkgs.mkShell.override { inherit stdenv; } {
    buildInputs = with pkgs; [
      SDL2
      vulkan-headers
      vulkan-loader
      vulkan-tools
      vulkan-validation-layers
    ];

    LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib";

    nativeBuildInputs = with pkgs; [
      norminette
      valgrind
      gdb
      tmux
    ];
  }
