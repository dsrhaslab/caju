#pragma once

#include <caju/hierarchy/tiers/storage_driver_interface.h>
#include <caju/interface/native/native.h>

class PosixFileSystemStorageDriver : public StorageDriver {
public:
    std::unique_ptr<FileId> open(const char* path, int flags);
    std::unique_ptr<FileId> open(const char* path, int flags, mode_t mode);
    std::unique_ptr<FileId> open64(const char* path, int flags);
    std::unique_ptr<FileId> open64(const char* path, int flags, mode_t mode);
    std::unique_ptr<FileId> fopen(const char* pathname, const char* mode);
    std::unique_ptr<FileId> fopen64(const char* pathname, const char* mode);

    ssize_t read(void* buf, size_t count, FileId& file_id);
    ssize_t write(const void* buf, size_t count, FileId& file_id);
    ssize_t writev(const struct iovec* iov, int iovcnt, FileId& file_id);
    size_t  fread(void* ptr, size_t size, size_t nmemb, FileId& file_id);
    size_t  fwrite(const void* ptr, size_t size, size_t nmemb, FileId& file_id);

    int     close(FileId& file_id);
    int     fclose(FileId& file_id);

    PosixFileSystemStorageDriver() {}
    PosixFileSystemStorageDriver(std::string tier_dir) : tier_dir(tier_dir) {}

private:
    std::string tier_dir = "";
    std::unique_ptr<FileId> create_fileid_from_fd(int fd);
    std::unique_ptr<FileId> create_fileid_from_stream(FILE *stream);
};
