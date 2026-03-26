


#include "caju/hierarchy/tiers/neighboring_node_storage_tier.h"

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("neighboring_node_storage_tier_test");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF


int main (int argc, char *argv[]) {

    NeighboringNodeStorageTier neighbouring_tier{argv[1]};
    StorageTier& tier = neighbouring_tier;

    Status<std::unique_ptr<FileId>> out_open = tier.open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    std::unique_ptr<FileId> file_id = std::move(out_open.return_value);
    SPDLOG_LOGGER_INFO(logger, "open(\"file.txt\", O_CREAT | O_WRONLY | O_TRUNC, 0666) -> Status: {}, File_Id fd: {}", (int) out_open.state, ((FileIdInt*) file_id.get())->fd);

    ///*
    Status<ssize_t> out_write = tier.write("lmao", 4, *file_id);
    SPDLOG_LOGGER_INFO(logger, "write(\"lmao\", 4, {}) -> Status: {}, Return: {}", ((FileIdInt*) file_id.get())->fd, (int) out_write.state, out_write.return_value);
    //*/

    Status<int> out_close = tier.close(*file_id);
    SPDLOG_LOGGER_INFO(logger, "close(File_Id fd: {}) -> Status: {}, Return: {}", ((FileIdInt*) file_id.get())->fd, (int) out_close.state, out_close.return_value);

    Status<std::unique_ptr<FileId>> out_open2 = tier.open("file.txt", O_CREAT | O_RDONLY, 0666);
    std::unique_ptr<FileId> file_id2 = std::move(out_open2.return_value);
    SPDLOG_LOGGER_INFO(logger, "open(\"file.txt\", O_CREAT | O_RDONLY, 0666) -> Status: {}, File_Id fd: {}", (int) out_open2.state, ((FileIdInt*) file_id2.get())->fd);

    char buf[5] = "";
    Status<ssize_t> out_read = tier.read(buf, 4, *file_id2);
    buf[4] = '\0';
    SPDLOG_LOGGER_INFO(logger, "read(Count: {}) -> Status: {}, Return: {}, Buf: {}", 4, (int) out_read.state, out_read.return_value, buf);

    Status<int> out_close2 = tier.close(*file_id2);
    SPDLOG_LOGGER_INFO(logger, "close(File_Id fd: {}) -> Status: {}, Return: {}", ((FileIdInt*) file_id2.get())->fd, (int) out_close2.state, out_close2.return_value);

    return 0;

    
    
    return 0;
}
