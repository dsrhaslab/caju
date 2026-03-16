#include <caju/hierarchy/tiers/posix_filesystem_storage_tier.h>

Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::open(const char* path, int flags) {
    int fd = Native::open(path, flags);
    std::shared_ptr<FileIdInt> file_id = std::make_shared<FileIdInt>(fd);
    return Status<std::shared_ptr<FileId>>(SUCCESS, std::dynamic_pointer_cast<FileId>(file_id));
}

Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::open(const char* path, int flags, mode_t mode) {
    int fd = Native::open(path, flags, mode);
    return FileIdInt(fd);
    std::shared_ptr<FileIdInt> file_id = std::make_shared<FileIdInt>(fd);
    return Status<std::shared_ptr<FileId>>(SUCCESS, std::dynamic_pointer_cast<FileId>(file_id));
}

Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::open64(const char* path, int flags) {}
Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::open64(const char* path, int flags, mode_t mode) {}
Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::fopen(const char* pathname, const char* mode) {}
Status<std::shared_ptr<FileId>> PosixFileSystemStorageTier::fopen64(const char* pathname, const char* mode) {}

Status<ssize_t> PosixFileSystemStorageTier::read(void* buf, size_t count, FileId& file_id) {}
Status<size_t> PosixFileSystemStorageTier:: fread(void* ptr, size_t size, size_t nmemb, FileId& file_id) {}
Status<size_t> PosixFileSystemStorageTier:: fwrite(const void* ptr, size_t size, size_t nmemb, FileId& file_id) {}
Status<ssize_t> PosixFileSystemStorageTier::write(const void* buf, size_t count, FileId& file_id) {}

Status<ssize_t> PosixFileSystemStorageTier::writev(const struct iovec* iov, int iovcnt, FileId& file_id) {}
Status<int>     PosixFileSystemStorageTier::close(FileId& file_id) {}
Status<int>     PosixFileSystemStorageTier::fclose(FileId& file_id) {}