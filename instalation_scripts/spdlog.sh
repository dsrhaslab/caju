#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location> <source_file_location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./spdlog1.17.0 ]; then

    if [ ! -f ./spdlog1.17.0.tar.gz ]; then
        wget https://github.com/gabime/spdlog/archive/refs/tags/v1.17.0.tar.gz
        mv v1.17.0.tar.gz spdlog-1.17.0.tar.gz
    fi

    tar -xzvf ./spdlog-1.17.0.tar.gz
fi

cd spdlog-1.17.0

if [ -d ./build ]; then
    rm -rf build
fi

mkdir build
cd build

cmake \
-DSPDLOG_BUILD_PIC=ON \
-DCMAKE_PREFIX_PATH=$INSTALL_PREFIX \
-DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX ..

make
make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed spdlog"
echo "-------------------------------------------------------"
echo ""

