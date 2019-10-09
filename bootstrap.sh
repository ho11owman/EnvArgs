#!/bin/sh

HOME=$(pwd)
BUILD_DIR=$HOME/build
BUILD_RELEASE_DIR=$BUILD_DIR/release

function build_dirs() {
    echo "make directory $1"
    mkdir -p $1

    echo "switch directory $1"
    cd $1
}

function default() {
    cmake ..
}

function release() {
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_CLANG_TIDY="/opt/rh/llvm-toolset-6.0/root/usr/bin/clang-tidy;-checks=*" \
        -DCMAKE_CXX_CPPCHECK="/usr/bin/cppcheck;--std=c++20" \
        ../..
}

function clean() {
    if [ -d "$BUILD_DIR" ]; then
        # Control will enter here if $DIRECTORY exists.
        echo "remove directory $BUILD_DIR"
        rm -rf "$BUILD_DIR"
    fi
}


case "$1" in
    "")
        clean;
        build_dirs $BUILD_DIR;
        default;;
    "r")
        clean;
        build_dirs $BUILD_RELEASE_DIR;
        release;;
    "clean")
        clean;;
     *)
        echo "Not supported"
        exit 1;;
esac

