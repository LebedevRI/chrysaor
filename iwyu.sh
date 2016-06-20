#!/bin/sh

SRC_DIR=$(dirname "$0")
SRC_DIR=$(cd "$SRC_DIR" && pwd -P)

BUILD_DIR="$SRC_DIR/build_iwyu"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" && rm -rf *

unset CC CXX

export CC=clang-3.8
export CXX=clang++-3.8

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_DOC=off -DUSE_IWYU=on ../ && \
make -j9 && make test && make iwyu && make iwyu_fix
