#include <caju/hierarchy/tiers/posix_filesystem_storage_driver.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("posix_filesystem_storage_driver");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF

std::unique_ptr<FileId> PosixFileSystemStorageDriver::create_fileid_from_fd(int fd)
{
    std::unique_ptr<FileIdInt> file_id = std::make_unique<FileIdInt>(*this, fd);
    return file_id;
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::create_fileid_from_stream(FILE *stream)
{
    std::unique_ptr<FileIdFILE> file_id = std::make_unique<FileIdFILE>(*this, stream);
    return file_id;
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::open(const char *path, int flags)
{
    int fd = Native::open((tier_dir + path).c_str(), flags);
    return create_fileid_from_fd(fd);
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::open(const char *path, int flags, mode_t mode)
{
    int fd = Native::open((tier_dir + path).c_str(), flags, mode);
    return create_fileid_from_fd(fd);
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::open64(const char *path, int flags)
{
    int fd = Native::open64((tier_dir + path).c_str(), flags);
    return create_fileid_from_fd(fd);
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::open64(const char *path, int flags, mode_t mode)
{
    int fd = Native::open64((tier_dir + path).c_str(), flags, mode);
    return create_fileid_from_fd(fd);
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::fopen(const char *pathname, const char *mode)
{
    FILE *stream = Native::fopen((tier_dir + pathname).c_str(), mode);
    return create_fileid_from_stream(stream);
}

std::unique_ptr<FileId> PosixFileSystemStorageDriver::fopen64(const char *pathname, const char *mode)
{
    FILE *stream = Native::fopen64((tier_dir + pathname).c_str(), mode);
    return create_fileid_from_stream(stream);
}

ssize_t PosixFileSystemStorageDriver::read(void *buf, size_t count, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    SPDLOG_LOGGER_TRACE(logger, "read(count: {}, fd: {})", count, file_id_int.fd);
    ssize_t ret = Native::read(file_id_int.fd, buf, count);
    SPDLOG_LOGGER_TRACE(logger, "read result -> ret: {}, buf: {}", ret, static_cast<char *>(buf));
    return ret;
}

ssize_t PosixFileSystemStorageDriver::write(const void *buf, size_t count, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    ssize_t ret = Native::write(file_id_int.fd, buf, count);
    return ret;
}

ssize_t PosixFileSystemStorageDriver::writev(const struct iovec *iov, int iovcnt, FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    ssize_t ret = Native::writev(file_id_int.fd, iov, iovcnt);
    return ret;
}

size_t PosixFileSystemStorageDriver::fread(void *ptr, size_t size, size_t nmemb, FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    size_t ret = Native::fread(ptr, size, nmemb, file_id_stream.stream);
    return ret;
}

size_t PosixFileSystemStorageDriver::fwrite(const void *ptr, size_t size, size_t nmemb, FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    size_t ret = Native::fwrite(ptr, size, nmemb, file_id_stream.stream);
    return ret;
}

int PosixFileSystemStorageDriver::close(FileId &file_id)
{
    FileIdInt &file_id_int = dynamic_cast<FileIdInt &>(file_id);
    int ret = Native::close(file_id_int.fd);
    return ret;
}

int PosixFileSystemStorageDriver::fclose(FileId &file_id)
{
    FileIdFILE &file_id_stream = dynamic_cast<FileIdFILE &>(file_id);
    int ret = Native::fclose(file_id_stream.stream);
    return ret;
}
