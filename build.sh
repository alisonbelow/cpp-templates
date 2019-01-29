#!/bin/bash

# Build function
function build() {
    echo -e "\n*****************************************"
    echo "Building cpp-templates"
    echo -e "*****************************************"

    mkdir -p build
    cd build
    cmake ..
    make clean
    make
    cd ..
}

build
exit