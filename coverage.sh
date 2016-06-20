#!/bin/sh

SRC_DIR=$(dirname "$0")
SRC_DIR=$(cd "$SRC_DIR" && pwd -P)

BUILD_DIR="$SRC_DIR/build_coverage"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" && rm -rf *

# coverage only really works with GNU gcc
unset CC CXX

export CC=gcc
export CXX=g++

cmake -DCMAKE_BUILD_TYPE=Coverage -DBUILD_DOC=off -DUSE_IWYU=off ../ && \
make -j9 && make test && make coverage && sensible-browser ./coverage/index.html
