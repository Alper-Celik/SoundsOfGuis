{
  description = "experimental accessiblity project (deneysel erişilebilirlik projesi)";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
    flake-utils.url = "github:numtide/flake-utils";
    pre-commit-hooks = {
      url = "github:cachix/pre-commit-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };

  };

  outputs = { self, nixpkgs, flake-utils, pre-commit-hooks, ... }:
    flake-utils.lib.eachSystem (with flake-utils.lib ;[ system.x86_64-linux system.aarch64-linux ])
      (system:
        let
          pkgs = (import nixpkgs
            {
              inherit system;
              overlays = [
                (final: prev: {
                  ccacheWrapper = prev.ccacheWrapper.override {
                    # from https://nixos.wiki/wiki/CCache#Non-NixOS
                    # and some modifications
                    extraConfig = ''
                      export CCACHE_COMPRESS=1
                      old_ccache_dir=$CCACHE_DIR
                      export CCACHE_DIR="/var/cache/ccache"
                      export CCACHE_UMASK=007
                      if [ ! -d "$CCACHE_DIR" ]; then
                        # echo "====="
                        # echo "Directory '$CCACHE_DIR' does not exist"
                        # echo "Please create it with:"
                        # echo "  sudo mkdir -m0770 '$CCACHE_DIR'"
                        # echo "  sudo chown root:nixbld '$CCACHE_DIR'"
                        # echo "defaulting to previus ccache_dir"
                        # echo "====="
                        CCACHE_DIR=$old_ccache_dir
                      fi
                      if [ ! -w "$CCACHE_DIR" ]; then
                        # echo "====="
                        # echo "Directory '$CCACHE_DIR' is not accessible for user $(whoami)"
                        # echo "Please verify its access permissions"
                        # echo "defaulting to previus ccache_dir"
                        # echo "====="
                        CCACHE_DIR=$old_ccache_dir
                      fi
                    '';
                  };
                })
              ];
            });
        in

        {
          packages.default = (pkgs.qt6Packages.callPackage ./default.nix {
            src = self;
            stdenv = pkgs.ccacheStdenv;
          });
          checks = {
            pre-commit-check = pre-commit-hooks.lib.${system}.run {
              src = ./.;
              hooks = {
                nixpkgs-fmt.enable = true;
                clang-format.enable = true;
                taplo.enable = true;
                prettier.enable = true;
              };
            };
          };
          devShells =
            {
              default = (pkgs.qt6Packages.callPackage ./default.nix {
                src = self;
                # mkDerivation = pkgs.mkShell;
                stdenv = pkgs.ccacheStdenv;
              }).overrideAttrs (
                oldAttrs: {
                  QT_LINUX_ACCESSIBILITY_ALWAYS_ON = 1;
                  QT_ACCESSIBILITY = 1;
                  # QT_PLUGIN_PATH = "${pkgs.qt6.qtdeclarative.bin}/lib/qt-${pkgs.qt6.qtbase.version}/plugins";
                  inherit (self.checks.${system}.pre-commit-check) shellHook;

                }
              );
            };
        }
      );
}
