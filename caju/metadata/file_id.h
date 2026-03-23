#pragma once

#include <cstdio>
#include <caju/hierarchy/tiers/storage_driver_interface.h>

class StorageDriver;

class FileId {
public:
StorageDriver& tier;

    virtual ~FileId() {}
    FileId()                      = delete;
    FileId(const FileId&)         = delete;
    void operator=(const FileId&) = delete;
    FileId(StorageDriver& tier) : tier(tier) {}

};

class FileIdInt : public FileId {
public:
    int fd;
    ~FileIdInt() = default;
    FileIdInt(StorageDriver& tier, int fd) : FileId(tier), fd(fd) {}
};

class FileIdFILE : public FileId {
public:
    FILE *stream;
    ~FileIdFILE() = default;
    FileIdFILE(StorageDriver& tier, FILE *stream) : FileId(tier), stream(stream) {}
};