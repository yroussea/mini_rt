{
  description = "miniRT";

  inputs = {
    systems.url = "github:nix-systems/x86_64-linux";
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    systems,
  }@inputs:
    let
      supportedSystems = import systems;
      forAllSystems = f: nixpkgs.lib.genAttrs supportedSystems (system: f (import nixpkgs { inherit system; }));

      provideBuildInputs = pkgs: with pkgs; [
        SDL2
        vulkan-headers
        vulkan-loader
        vulkan-tools
        vulkan-validation-layers
      ];
      provideNativeBuildInputs = pkgs: with pkgs; [
        inotify-tools
        norminette
        valgrind
        gdb
      ];
    in
    {
      devShell = forAllSystems (pkgs: 
        let
          stdenv = pkgs.llvmPackages_19.stdenv;
        in
          pkgs.mkShell.override { inherit stdenv; } {
            nativeBuildInputs = provideNativeBuildInputs pkgs;
            buildInputs = provideBuildInputs pkgs;
            LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib";
          }
        );
      # packages = forAllSystems (pkgs:
      #   let
      #     inherit (pkgs) lib;
      #
      #     stdenv = pkgs.llvmPackages_19.stdenv;
      #     pkg = stdenv.mkDerivation {
      #       name = "miniRT";
      #       version = "0.1";
      #       src = ./.;
      #       nativeBuildInputs = provideNativeBuildInputs pkgs;
      #       buildInputs = provideBuildInputs pkgs;
      #     };
      #   in
      #   {
      #     default = pkg;
      #   }
      # );
    };
}
# vim: ts=2 sw=2 et

