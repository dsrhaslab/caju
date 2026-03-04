#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./libfabric-1.22.0 ]; then

    if [ ! -f ./libfabric-1.22.0.tar.bz2 ]; then
        wget https://github.com/ofiwg/libfabric/releases/download/v1.22.0/libfabric-1.22.0.tar.bz2
    fi

    tar -xjvf ./libfabric-1.22.0.tar.bz2
fi

cd libfabric-1.22.0

./configure --prefix=$INSTALL_PREFIX
make -j 32
make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed libfabric"
echo "-------------------------------------------------------"
echo ""

