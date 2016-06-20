#!/bin/sh

CLANG_FORMAT=clang-format-3.9

SOURCES=$(find | egrep -v "\.git" | egrep "\.hpp$|\.cpp$")

for FILE in $SOURCES
do
  ${CLANG_FORMAT} -i $FILE
done
