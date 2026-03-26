#include <caju/hierarchy/tiers/posix_filesystem_storage_driver.h>
#include <caju/logger/logger.h>
#include <caju/metadata/file_id.h>
#include <memory>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("posix_filesystem_test");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF

int main(int argc, char* argv[]) {
    PosixFileSystemStorageDriver posix_tier{};
    StorageDriver&               tier = posix_tier;

    std::unique_ptr<FileId> file_id = tier.open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    SPDLOG_LOGGER_INFO(logger, "open(\"file.txt\", O_CREAT | O_WRONLY | O_TRUNC, 0666) -> File_Id fd: {}", static_cast<FileIdInt*>(file_id.get())->fd);

    ///*
    ssize_t out_write = tier.write("lmao", 4, *file_id);
    SPDLOG_LOGGER_INFO(logger, "write(\"lmao\", 4, {}) -> Return: {}", static_cast<FileIdInt*>(file_id.get())->fd, out_write);
    //*/

    int out_close = tier.close(*file_id);
    SPDLOG_LOGGER_INFO(logger, "close(File_Id fd: {}) -> Return: {}", static_cast<FileIdInt*>(file_id.get())->fd, out_close);

    std::unique_ptr<FileId> file_id2 = tier.open("file.txt", O_CREAT | O_RDONLY, 0666);
    SPDLOG_LOGGER_INFO(logger, "open(\"file.txt\", O_CREAT | O_RDONLY, 0666) -> File_Id fd: {}", static_cast<FileIdInt*>(file_id2.get())->fd);

    char    buf[5]   = "";
    ssize_t out_read = tier.read(buf, 4, *file_id2);
    buf[4]           = '\0';
    SPDLOG_LOGGER_INFO(logger, "read(Count: {}, File_id fd: {}) -> Return: {}, Buf: {}", 4, static_cast<FileIdInt*>(file_id.get())->fd, out_read, buf);

    int out_close2 = tier.close(*file_id2);
    SPDLOG_LOGGER_INFO(logger, "close(File_Id fd: {}) -> Return: {}", static_cast<FileIdInt*>(file_id2.get())->fd, out_close2);

    return 0;
}
