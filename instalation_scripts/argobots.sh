#!/bin/bash

SOURCE_FILE_DIR=$2
cd $SOURCE_FILE_DIR

WD=$(pwd)

if [ -z $1 ]; then
    echo "usage: <cmd> <isntall location>"
    exit 0
fi

INSTALL_PREFIX=$1

if [ ! -d ./argobots-1.2/ ]; then

    if [ ! -f ./argobots-1.2.tar.gz ]; then
        wget https://github.com/pmodels/argobots/releases/download/v1.2/argobots-1.2.tar.gz
    fi

    tar -xzvf ./argobots-1.2.tar.gz
fi

cd ./argobots-1.2

./configure --prefix=$INSTALL_PREFIX

make 

make install

cd $WD

echo ""
echo "-------------------------------------------------------"
echo "Installed argobots"
echo "-------------------------------------------------------"
echo ""

