{
  description = "experimental accessiblity project (deneysel erişilebilirlik projesi)";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/22.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      rec {
        BuildTools = with pkgs; [ cmake ninja ];
        RuntimeDeps = with pkgs; [ nlohmann_json libsndfile openal catch2_3 boost180 at-spi2-core ];

        devShell = pkgs.mkShell {
          buildInputs = RuntimeDeps;
          nativeBuildInputs = BuildTools;
        };
        packages.default = pkgs.stdenv.mkDerivation
          rec
          {
            pname = "SoundsOfGuis";
            version = "0.0.0";
            src = ./.;
            nativeBuildInputs = BuildTools;
            BuildInputs = RuntimeDeps;
          };

      });
}
