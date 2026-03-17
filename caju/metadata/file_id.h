#pragma once

#include <cstdio>
#include <caju/hierarchy/tiers/storage_tier_interface.h>

class FileId {
public:
    StorageTier& tier;

    virtual ~FileId();
    FileId()                      = delete;
    FileId(const FileId&)         = delete;
    void operator=(const FileId&) = delete;
    FileId(StorageTier& tier) : tier(tier) {}

};

class FileIdInt : public FileId {
public:
    int fd;
    FileIdInt(StorageTier& tier, int fd) : FileId(tier), fd(fd) {}
};

class FileIdFILE : public FileId {
public:
    FILE *stream;
    FileIdFILE(StorageTier& tier, FILE *stream) : FileId(tier), stream(stream) {}
};