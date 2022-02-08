{ lib
, pkgs ? import <nixpkgs> {}
, stdenv ? pkgs.stdenv
, cmake
, cmake-utils
, git
, llvmPackages_13
, pdf2svg
}:

with pkgs;

let
  texlive = pkgs.texlive.combine {
    inherit (pkgs.texlive) scheme-small standalone pgfplots;
  };

in stdenv.mkDerivation {
  name = "raisin";
  version = "0.0.0";

  src = ./.;

  nativeBuildInputs = [
    cmake
    cmake-utils
    git
    llvmPackages_13.libclang
    llvmPackages_13.llvm
    pdf2svg
    texlive
  ];

  meta = {
    homepage = "https://github.com/conformism/raisin";
    description = "Control flow -grape- graph";
    license = lib.licenses.gpl3;
    maintainers = [
      {
        email = "thomas.lepoix@protonmail.ch";
        github = "thomaslepoix";
        githubId = 26417323;
        name = "Thomas Lepoix";
      }
    ];
  };
}
