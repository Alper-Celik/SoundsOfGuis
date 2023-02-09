{
  description = "experimental accessiblity project (deneysel erişilebilirlik projesi)";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-22.11";
    flake-utils.url = "github:numtide/flake-utils";

  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {

          devShell = (pkgs.libsForQt5.callPackage ./default.nix {
            src = self;
            mkDerivation = pkgs.mkShell;
          }).overrideAttrs (
            oldAttrs: {
              QT_LINUX_ACCESSIBILITY_ALWAYS_ON = 1;
              QT_ACCESSIBILITY = 1;
            }
          );
          packages.default = (pkgs.libsForQt5.callPackage ./default.nix {
            src = self;
          });


        }
      );
}
