#!/bin/sh

SRC_DIR=$(dirname "$0")
SRC_DIR=$(cd "$SRC_DIR" && pwd -P)

BUILD_DIR="$SRC_DIR/build_ct"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" && rm -rf *

unset CC CXX

export CC=clang-3.9
export CXX=clang++-3.9

cmake -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DBUILD_DOC=off -DUSE_IWYU=off ../ && \
make -j9 && make test && run-clang-tidy-3.9.py -header-filter=.* -fix -format
