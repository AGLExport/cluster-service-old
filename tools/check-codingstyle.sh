#!/bin/sh

clang-format --dry-run src/*.c
clang-format --dry-run src/*.h
clang-format --dry-run lib/*.c
clang-format --dry-run lib/*.h
clang-format --dry-run example/*.c
clang-format --dry-run example/*.h
clang-format --dry-run include/*.h
