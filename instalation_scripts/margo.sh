#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./mochi-margo-0.23.0 ]; then

    if [ ! -f ./mochi-margo-0.23.0.tar.gz ]; then
        wget https://github.com/mochi-hpc/mochi-margo/archive/refs/tags/v0.23.0.tar.gz
        mv v0.23.0.tar.gz mochi-margo-0.23.0.tar.gz
    fi

    tar -xzvf ./mochi-margo-0.23.0.tar.gz
fi

cd mochi-margo-0.23.0

if [ -d ./build ]; then
    rm -rf build
fi

mkdir build
cd build


cmake --debug-find \
    -DCMAKE_PREFIX_PATH=$INSTALL_PREFIX \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
    ..
    # -DPKG_CONFIG_PATH=$INSTALL_PREFIX/lib/pkg \

make
make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed margo"
echo "-------------------------------------------------------"
echo ""
