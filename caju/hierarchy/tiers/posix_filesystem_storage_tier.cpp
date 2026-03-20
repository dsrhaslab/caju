#include <caju/hierarchy/tiers/posix_filesystem_storage_tier.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("posix_filesystem_storage_tier");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::create_fileid_from_fd(int fd)
{
    std::unique_ptr<FileIdInt> file_id = std::make_unique<FileIdInt>(*this, fd);
    return Status<std::unique_ptr<FileId>>(SUCCESS, std::move(file_id));
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::create_fileid_from_stream(FILE *stream)
{
    std::unique_ptr<FileIdFILE> file_id = std::make_unique<FileIdFILE>(*this, stream);
    return Status<std::unique_ptr<FileId>>(SUCCESS, std::move(file_id));
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::open(const char *path, int flags)
{
    int fd = Native::open(path, flags);
    return create_fileid_from_fd(fd);
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::open(const char *path, int flags, mode_t mode)
{
    int fd = Native::open(path, flags, mode);
    return create_fileid_from_fd(fd);
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::open64(const char *path, int flags)
{
    int fd = Native::open64(path, flags);
    return create_fileid_from_fd(fd);
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::open64(const char *path, int flags, mode_t mode)
{
    int fd = Native::open64(path, flags, mode);
    return create_fileid_from_fd(fd);
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::fopen(const char *pathname, const char *mode)
{
    FILE *stream = Native::fopen(pathname, mode);
    return create_fileid_from_stream(stream);
}

Status<std::unique_ptr<FileId>> PosixFileSystemStorageTier::fopen64(const char *pathname, const char *mode)
{
    FILE *stream = Native::fopen64(pathname, mode);
    return create_fileid_from_stream(stream);
}

Status<ssize_t> PosixFileSystemStorageTier::read(void *buf, size_t count, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    SPDLOG_LOGGER_TRACE(logger, "read(count: {}, fd: {})", count, file_id_int.fd);
    ssize_t ret = Native::read(file_id_int.fd, buf, count);
    SPDLOG_LOGGER_TRACE(logger, "read result -> ret: {}, buf: {}", ret, (char *)buf);
    return Status<ssize_t>(ret);
}

Status<ssize_t> PosixFileSystemStorageTier::write(const void *buf, size_t count, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    ssize_t ret = Native::write(file_id_int.fd, buf, count);
    return Status<ssize_t>(ret);
}

Status<ssize_t> PosixFileSystemStorageTier::writev(const struct iovec *iov, int iovcnt, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    ssize_t ret = Native::writev(file_id_int.fd, iov, iovcnt);
    return Status<ssize_t>(ret);
}

Status<size_t> PosixFileSystemStorageTier::fread(void *ptr, size_t size, size_t nmemb, FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    size_t ret = Native::fread(ptr, size, nmemb, file_id_stream.stream);
    return Status<size_t>(ret);
}

Status<size_t> PosixFileSystemStorageTier::fwrite(const void *ptr, size_t size, size_t nmemb, FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    size_t ret = Native::fwrite(ptr, size, nmemb, file_id_stream.stream);
    return Status<size_t>(ret);
}

Status<int> PosixFileSystemStorageTier::close(FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    int ret = Native::close(file_id_int.fd);
    return Status<int>(ret);
}

Status<int> PosixFileSystemStorageTier::fclose(FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    int ret = Native::fclose(file_id_stream.stream);
    return Status<int>(ret);
}