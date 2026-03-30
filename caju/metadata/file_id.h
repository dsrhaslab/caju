#pragma once

#include <cstdio>

class StorageDriver;

class FileId {
public:
StorageDriver& tier;

    virtual ~FileId() {}
    FileId()                      = delete;
    FileId(const FileId&)         = delete;
    void operator=(const FileId&) = delete;
    FileId(StorageDriver& tier_arg) : tier(tier_arg) {}

};

class FileIdInt : public FileId {
public:
    int fd;
    ~FileIdInt() = default;
    FileIdInt(StorageDriver& tier_arg, int fd_arg) : FileId(tier_arg), fd(fd_arg) {}
};

class FileIdFILE : public FileId {
public:
    FILE *stream;
    ~FileIdFILE() = default;
    FileIdFILE(StorageDriver& tier_arg, FILE *stream_arg) : FileId(tier_arg), stream(stream_arg) {}
};
