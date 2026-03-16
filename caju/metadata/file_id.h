#pragma once

#include <cstdio>

class FileId {

};

class FileIdInt : public FileId {
    int fd;
};

class FileIdFILE : public FileId {
    FILE *stream;
};