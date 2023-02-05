{
  description = "experimental accessiblity project (deneysel erişilebilirlik projesi)";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/22.11";
    flake-utils.url = "github:numtide/flake-utils";

    # c++ libs
    magic-enum-repo = {
      url = "github:Neargye/magic_enum/v0.8.2";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, flake-utils, magic-enum-repo, ... }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
          magic-enum = pkgs.stdenv.mkDerivation
            {
              pname = "magic-enum";
              version = "0.8.2";
              src = magic-enum-repo;
              doCheck = true;
              nativeBuildInputs = with pkgs; [ cmake ];
            };

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            pkg-config
            libsForQt5.qt5.wrapQtAppsHook
          ];
          buildInputs = with pkgs; [
            nlohmann_json
            magic-enum

            libsndfile
            openal

            catch2_3

            boost180
            libbacktrace
            microsoft_gsl

            fmt_9
            spdlog

            at-spi2-core
            xdotool

            libsForQt5.qt5.qtbase
          ];
          baseDerivation =
            {
              pname = "SoundsOfGuis";
              version = "0.0.0";
              src = self;
              inherit buildInputs nativeBuildInputs;

              libbacktrace_header = "${pkgs.libbacktrace}/include/backtrace.h";
              QT_LINUX_ACCESSIBILITY_ALWAYS_ON = 1;
              QT_ACCESSIBILITY = 1;
            };

        in
        {

          devShell = pkgs.mkShell baseDerivation;
          packages.default = pkgs.stdenv.mkDerivation (baseDerivation // { });


        });
}
