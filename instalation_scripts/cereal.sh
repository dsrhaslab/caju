#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./cereal-1.3.2 ]; then

    if [ ! -f ./cereal-1.3.2.tar.gz ]; then
        wget https://github.com/USCiLab/cereal/archive/v1.3.2.tar.gz
        mv v1.3.2.tar.gz cereal-1.3.2.tar.gz
    fi

    tar -xzvf ./cereal-1.3.2.tar.gz
fi

cd ./cereal-1.3.2

if [ -d ./build ]; then
    rm -rf build
fi

mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
     -DSKIP_PERFORMANCE_COMPARISON=ON \
     -DBUILD_DOC=OFF \
     -DBUILD_SANDBOX=OFF \
     -DBUILD_TESTS=OFF \
     -DCEREAL_INSTALL=ON ..

make
make install

cp -r $INSTALL_PREFIX/lib64/cmake/cereal $INSTALL_PREFIX/share/cmake

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed cereal"
echo "-------------------------------------------------------"
echo ""
