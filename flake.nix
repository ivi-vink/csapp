{
  inputs = {
    nixpkgs.url = "nixpkgs";
    nix-filter.url = "github:numtide/nix-filter";
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs-terraform-providers-bin.url = "github:nix-community/nixpkgs-terraform-providers-bin";
    nixpkgs-terraform-providers-bin.inputs.nixpkgs.follows = "nixpkgs";
    poetry2nix = {
      url = "github:nix-community/poetry2nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = {
    self,
    flake-utils,
    ...
  } @ inputs:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs =
        import inputs.nixpkgs
          {
            # config.replaceStdenv = { pkgs, ... }: pkgs.gccMultiStdenv;
            inherit system;
          };
    in {
      # devShells.default = pkgs.mkShell {
      #   name = "multi-stdenv-gcc";
      #   nativeBuildInputs = with pkgs; [pkgsi686Linux.glibc];
      # };
      # devShells.default = pkgs.gccMultiStdenv {
      #   name = "gcc-test";
      # };
      devShells.default = pkgs.mkShell {
        name = "dev";
        buildInputs = with pkgs; [
          bashInteractive
        ];
      };
    });
}
