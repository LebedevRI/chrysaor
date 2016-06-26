#!/bin/sh

SRC_DIR=$(dirname "$0")
SRC_DIR=$(cd "$SRC_DIR" && pwd -P)

BUILD_DIR="$SRC_DIR/build_sb"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" && rm -rf *

unset CC CXX

export CC=clang-3.9
export CXX=clang++-3.9

SCAN_BUILD=scan-build-3.9

# --force-analyze-debug-code # <- 3.9-only flag

$SCAN_BUILD cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_DOC=off -DUSE_IWYU=off ../ \
&& $SCAN_BUILD --force-analyze-debug-code --status-bugs -maxloop 4096 make -j9
