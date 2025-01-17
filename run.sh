#!/usr/bin/env bash

BIN_DIR=build/default/bin
EXECUTABLE=OGLvcpkgExample

if [ ! -d "$BIN_DIR" ]; then
    # check if executable exists
    echo "Error: $BIN_DIR does not exist. Build the project first."
    exit 1
fi

pushd $BIN_DIR || exit

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: execuutable $BIN_DIR/$EXECUTABLE does not exist. Project must be built first."
    exit 1
fi

./$EXECUTABLE

popd || exit
