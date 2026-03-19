#pragma once

#include <memory>
#include <unistd.h>
#include <iostream>

#include <caju/metadata/file_id.h>
#include <caju/hierarchy/utils/status.h>
#include <caju/logger/logger.h>

class StorageTier {

public:
    virtual Status<std::unique_ptr<FileId>> open(const char* path, int flags) = 0;
    virtual Status<std::unique_ptr<FileId>> open(const char* path, int flags, mode_t mode) = 0;
    virtual Status<std::unique_ptr<FileId>> open64(const char* path, int flags) = 0;
    virtual Status<std::unique_ptr<FileId>> open64(const char* path, int flags, mode_t mode) = 0;
    virtual Status<std::unique_ptr<FileId>> fopen(const char* pathname, const char* mode) = 0;
    virtual Status<std::unique_ptr<FileId>> fopen64(const char* pathname, const char* mode) = 0;

    virtual Status<ssize_t> read(void* buf, size_t count, FileId& file_id) = 0;
    virtual Status<size_t>  fread(void* ptr, size_t size, size_t nmemb, FileId& file_id) = 0;
    virtual Status<size_t>  fwrite(const void* ptr, size_t size, size_t nmemb, FileId& file_id) = 0;
    virtual Status<ssize_t> write(const void* buf, size_t count, FileId& file_id) = 0;
    virtual Status<ssize_t> writev(const struct iovec* iov, int iovcnt, FileId& file_id) = 0;

    virtual Status<int>     close(FileId& file_id) = 0;
    virtual Status<int>     fclose(FileId& file_id) = 0;
    virtual ~StorageTier() = default;
};
