#include <memory>
#include <caju/hierarchy/tiers/posix_filesystem_storage_tier.h>
#include <caju/metadata/file_id.h>
#include <caju/logger/logger.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("posix_filesystem_test");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF

int main(int argc, char* argv[]) {
    PosixFileSystemStorageTier posix_tier{};
    StorageTier& tier = posix_tier;

    Status<std::unique_ptr<FileId>> out_open = tier.open("file.txt", O_CREAT | O_RDWR, 0666);
    std::unique_ptr<FileId> file_id = std::move(out_open.return_value);
    SPDLOG_LOGGER_TRACE(logger, "open(\"file.txt\") -> Status: {}, File_Id fd: {}", (int) out_open.state, ((FileIdInt*) file_id.get())->fd);

    Status<ssize_t> out_write = tier.write("lmao", 4, *file_id);
    SPDLOG_LOGGER_TRACE(logger, "write(\"lmao\") -> Status: {}, Return: {}", (int) out_write.state, out_write.return_value);

    char buf[5] = "";
    Status<ssize_t> out_read = tier.read(buf, 4, *file_id);
    buf[4] = '\0';
    SPDLOG_LOGGER_TRACE(logger, "read() -> Status: {}, Return: {}, Buf: {}", (int) out_read.state, out_read.return_value, buf);

    Status<int> out_close = tier.close(*file_id);
    SPDLOG_LOGGER_TRACE(logger, "close() -> Status: {}, Return: {}", (int) out_close.state, out_close.return_value);

    return 0;
}
