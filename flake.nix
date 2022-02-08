{
  description = "Control flow -grape- graph.";

  nixConfig.bash-prompt-suffix = "(raisin) ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/8cec3cc";

    utils.url = "github:numtide/flake-utils";
    utils.inputs.nixpkgs.follows = "nixpkgs";

    cmake-utils-src.url = "github:conformism/cmake-utils";
  };

  outputs = { self
    , nixpkgs
    , cmake-utils-src
    , ...
    }@inputs:
    inputs.utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };

      cmake-utils = import cmake-utils-src {
        inherit pkgs;
      };

      cmake-utils-dev = import cmake-utils-src {
        inherit pkgs;
        need-all = true;
      };

      this-package = pkgs.callPackage ./default.nix {
        inherit pkgs cmake-utils;
      };

    in {
      devShell = pkgs.mkShell rec {
        inputsFrom = [
          this-package
          cmake-utils-dev
        ];
      };

      defaultPackage = this-package;
    });
}
