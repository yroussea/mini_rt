{
  description = "dev-env for 42 projects";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils
  }: flake-utils.lib.eachDefaultSystem
    (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        stdenv = pkgs.llvmPackages_19.stdenv;
      in
      {
        devShell = (pkgs.mkShell.override { inherit stdenv; }) {
          buildInputs = with pkgs; [
            SDL2
          #   vulkan-headers
            vulkan-loader
          #   vulkan-tools
          #   vulkan-validation-layers
          ];

          LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib";

          nativeBuildInputs = with pkgs; [
            norminette
            valgrind
            gdb
            tmux
          ];
        };
      }
    );
}
# vim: ts=2 sw=2 et

