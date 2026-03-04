#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./mochi-thallium-0.15.0 ]; then

    if [ ! -f ./mochi-thallium-0.15.0.tar.gz ]; then
        wget https://github.com/mochi-hpc/mochi-thallium/archive/refs/tags/v0.15.0.tar.gz
        mv v0.15.0.tar.gz mochi-thallium-0.15.0.tar.gz
    fi

    tar -xzvf ./mochi-thallium-0.15.0.tar.gz
fi

cd mochi-thallium-0.15.0

if [ -d ./build ]; then
    rm -rf build
fi

mkdir build
cd build

cmake -DCMAKE_PREFIX_PATH=$INSTALL_PREFIX \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX ..

make
make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed thallium"
echo "-------------------------------------------------------"
echo ""

