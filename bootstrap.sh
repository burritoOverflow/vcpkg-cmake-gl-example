#!/usr/bin/env bash

echo "Cloning submodule"
git submodule update --init

echo "Bootstrapping vcpkg"
./vcpkg/bootstrap-vcpkg.sh -disableMetrics