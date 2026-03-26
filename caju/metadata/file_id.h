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
    FileId(StorageDriver& tier_) : tier(tier_) {}

};

class FileIdInt : public FileId {
public:
    int fd;
    ~FileIdInt() = default;
    FileIdInt(StorageDriver& tier_, int fd) : FileId(tier_), fd(fd) {}
};

class FileIdFILE : public FileId {
public:
    FILE *stream;
    ~FileIdFILE() = default;
    FileIdFILE(StorageDriver& tier_, FILE *stream) : FileId(tier_), stream(stream) {}
};
