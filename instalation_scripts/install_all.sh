#!/bin/bash

SOURCE_FILE_DIR=$2

if [ -z $1 ]; then
    echo "usage: <cmd> <install location(must be full path)>"
    exit 0
fi

INSTALL_PREFIX=$1

#DO NOT CHANGE ORDER
./libfabric.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
./cereal.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
./argobots.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
./mercury.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
./margo.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
./thallium.sh $INSTALL_PREFIX $SOURCE_FILE_DIR
