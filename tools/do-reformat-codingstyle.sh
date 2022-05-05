#!/bin/sh

clang-format -i src/*.c
clang-format -i src/*.h
clang-format -i lib/*.c
clang-format -i lib/*.h
clang-format -i example/*.c
clang-format -i example/*.h
clang-format -i include/*.h
