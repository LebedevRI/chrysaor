#!/bin/sh

SRC_DIR=$(dirname "$0")
SRC_DIR=$(cd "$SRC_DIR" && pwd -P)

CLANG_FORMAT=clang-format-3.9

SOURCES=$(find $SRC_DIR | egrep -v "\.git" | egrep "\.hpp$|\.cpp$")

for FILE in $SOURCES
do
  ${CLANG_FORMAT} -i $FILE
done
