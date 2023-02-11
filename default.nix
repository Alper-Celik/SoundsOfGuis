{ stdenv
, cmake
, ninja
, pkg-config
, wrapQtAppsHook

, tomlplusplus
, cli11
, magic-enum
, libsndfile
, openal
, catch2_3
, boost180
, libbacktrace
, microsoft_gsl
, fmt_9
, spdlog
, at-spi2-core
, xdotool
, qtbase

, src
, breakpointHook
}: stdenv.mkDerivation {
  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
    wrapQtAppsHook
    # breakpointHook
  ];
  buildInputs = [
    tomlplusplus
    cli11
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

    qtbase
  ];
  patchPhase = ''
    export CCACHE_DIR="`pwd`/.ccache"
  '';

  libbacktrace_header = "${libbacktrace}/include/backtrace.h";

  src = src;

  pname = "SoundsOfGuis";
  version = "0.0.0";

}