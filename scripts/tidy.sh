#!/bin/sh
# assumes source is defined as CMAKE_SOURCE_DIR
# assumes build is defined as CMAKE_BINARY_DIR

echo "Running clang-tidy assuming source path =" ${source} " and build path =" ${build}

clang-tidy -p=${build} --header-filter=${source} ${source}/*.cpp  -config="{Checks: '-*,readability-*', CheckOptions: [{key: readability-function-size.LineThreshold, value: 60}]}"
