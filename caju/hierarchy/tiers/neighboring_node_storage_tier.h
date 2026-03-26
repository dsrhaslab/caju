#pragma once

#include <caju/hierarchy/tiers/storage_tier_interface.h>
#include <caju/interface/native/native.h>
#include <string>

class NeighboringNodeStorageTier : public StorageTier {

  public:
    NeighboringNodeStorageTier(const std::string address);

    Status<std::unique_ptr<FileId>> open(const char* path, int flags);
    Status<std::unique_ptr<FileId>> open(const char* path, int flags, mode_t mode);
    Status<std::unique_ptr<FileId>> open64(const char* path, int flags);
    Status<std::unique_ptr<FileId>> open64(const char* path, int flags, mode_t mode);
    Status<std::unique_ptr<FileId>> fopen(const char* pathname, const char* mode);
    Status<std::unique_ptr<FileId>> fopen64(const char* pathname, const char* mode);

    Status<ssize_t> read(void* buf, size_t count, FileId& file_id);
    Status<ssize_t> write(const void* buf, size_t count, FileId& file_id);
    Status<ssize_t> writev(const struct iovec* iov, int iovcnt, FileId& file_id);
    Status<size_t>  fread(void* ptr, size_t size, size_t nmemb, FileId& file_id);
    Status<size_t>  fwrite(const void* ptr, size_t size, size_t nmemb, FileId& file_id);

    Status<int> close(FileId& file_id);
    Status<int> fclose(FileId& file_id);

  private:
    std::string address;

    Status<std::unique_ptr<FileId>> create_fileid_from_fd(int fd);
    Status<std::unique_ptr<FileId>> create_fileid_from_stream(FILE* stream);
};
