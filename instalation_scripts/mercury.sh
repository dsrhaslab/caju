#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

echo $INSTALL_PREFIX

if [ ! -d ./mercury-2.4.1 ]; then

    if [ ! -f ./mercury-2.4.1.tar.bz2 ]; then
        wget https://github.com/mercury-hpc/mercury/releases/download/v2.4.1/mercury-2.4.1.tar.bz2
    fi

    tar -xjvf ./mercury-2.4.1.tar.bz2
fi

cd mercury-2.4.1

if [ -d ./build ]; then
    rm -rf build
fi

mkdir build
cd build

export LD_LIBRARY_PATH=$INSTALL_PREFIX/lib:$LD_LIBRARY_PATH
cmake \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
    -DMERCURY_USE_BOOST_PP=ON \
    -DMERCURY_ENABLE_DEBUG=ON \
    -DNA_USE_OFI=ON ..
make
make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed mercury"
echo "-------------------------------------------------------"
echo ""
