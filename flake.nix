{
  description = "dev-env for 42 projects";

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
    in
    {
      devShell = forAllSystems (pkgs: import ./shell.nix { inherit pkgs; });
    };
}
# vim: ts=2 sw=2 et

