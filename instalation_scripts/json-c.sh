


#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./json-c-0.18-20240915 ]; then

    if [ ! -f ./json-c-0.18-20240915.tar.gz ]; then
        wget https://github.com/json-c/json-c/archive/refs/tags/json-c-0.18-20240915.tar.gz
    fi

    tar -xzvf ./json-c-0.18-20240915.tar.gz
fi

cd json-c-json-c-0.18-20240915

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
echo "Installed jsonc"
echo "-------------------------------------------------------"
echo ""

