#include "neighboring_node_storage_tier.h"
#include "caju/logger/logger.h"
#include "caju/metadata/file_id.h"
#include "caju/thallium/thallium_engine.h"
#include <cstddef>
#include <cstdio>
#include <fcntl.h>
#include <spdlog/spdlog.h>
#include <string>
#include <utility>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("neighboring_node_storage_tier");
#endif


NeighboringNodeStorageTier::NeighboringNodeStorageTier(const std::string address) : address{address} {
    SPDLOG_LOGGER_TRACE(logger, "NeighboringNodeStorageTier({})", address);
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::open(const char* path, int flags) {

    thallium::endpoint server_endpoint = ThalliumEngine::getInstance().lookup(this->address);

    int metadata_map_key = ThalliumEngine::getInstance().open_rpc_handler.on(server_endpoint)(std::string(path), flags);

    SPDLOG_LOGGER_TRACE(logger, "open(path:{}, flags:{}) -> metadata_map_key:{}", path, flags, metadata_map_key);

    return std::make_unique<FileIdInt>(*this, metadata_map_key);
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::open(const char* path, int flags, mode_t mode) {

    thallium::endpoint server_endpoint = ThalliumEngine::getInstance().lookup(this->address);

    int metadata_map_key = ThalliumEngine::getInstance().open_variadic_rpc_handler.on(server_endpoint)(std::string(path), flags, mode);

    SPDLOG_LOGGER_TRACE(logger, "open(path:{}, flags:{}, mode:{}) -> metadata_map_key:{}", path, flags, mode, metadata_map_key);

    return std::make_unique<FileIdInt>(*this, std::move(metadata_map_key));
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::open64(const char* path, int flags) {
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::open64(const char* path, int flags, mode_t mode) {
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::fopen(const char* pathname, const char* mode) {
}

std::unique_ptr<FileId> NeighboringNodeStorageTier::fopen64(const char* pathname, const char* mode) {
}

ssize_t NeighboringNodeStorageTier::read(void* buf, size_t count, FileId& file_id) {

    std::vector<std::pair<void*, std::size_t>> segments(1);

    segments[0].first  = (void*)buf;
    segments[0].second = count;

    thallium::bulk bulk_handler = ThalliumEngine::getInstance().expose(segments, thallium::bulk_mode::write_only);

    thallium::endpoint remote_endpoint = ThalliumEngine::getInstance().lookup(this->address);

    FileIdInt& file_id_int = dynamic_cast<FileIdInt&>(file_id);

    ssize_t bytes_read = ThalliumEngine::getInstance().read_rpc_handler.on(remote_endpoint)(
        bulk_handler,
        count,
        file_id_int.fd);

    SPDLOG_LOGGER_TRACE(logger, "read(buf:{}, count:{}, metadata_map_key:{}) -> bytes_written:{}", buf, count, file_id_int.fd, bytes_read);;

    return bytes_read;

}

ssize_t NeighboringNodeStorageTier::write(const void* buf, size_t count, FileId& file_id) {

    std::vector<std::pair<void*, std::size_t>> segments(1);

    segments[0].first  = (void*)buf;
    segments[0].second = count;

    thallium::bulk bulk_handler = ThalliumEngine::getInstance().expose(segments, thallium::bulk_mode::read_only);

    thallium::endpoint remote_endpoint = ThalliumEngine::getInstance().lookup(this->address);

    FileIdInt& file_id_int = dynamic_cast<FileIdInt&>(file_id);

    ssize_t bytes_written = ThalliumEngine::getInstance().write_rpc_handler.on(remote_endpoint)(
        bulk_handler,
        count,
        file_id_int.fd);

    SPDLOG_LOGGER_TRACE(logger, "write(buf:{}, count:{}, metadata_map_key:{}) -> bytes_written:{}", buf, count, file_id_int.fd, bytes_written);;

    return bytes_written;
}

ssize_t NeighboringNodeStorageTier::writev(const struct iovec* iov, int iovcnt, FileId& file_id) {
}

size_t NeighboringNodeStorageTier::fread(void* ptr, size_t size, size_t nmemb, FileId& file_id) {
}

size_t NeighboringNodeStorageTier::fwrite(const void* ptr, size_t size, size_t nmemb, FileId& file_id) {
}

int NeighboringNodeStorageTier::close(FileId& file_id) {

    thallium::endpoint server_endpoint = ThalliumEngine::getInstance().lookup(this->address);

    FileIdInt& file_id_int = dynamic_cast<FileIdInt&>(file_id);

    int return_value = ThalliumEngine::getInstance().close_rpc_handler.on(server_endpoint)(file_id_int.fd);

    SPDLOG_LOGGER_TRACE(logger, "close(FileIdInt:{}) -> {}", file_id_int.fd, return_value);

    return return_value;

}

int NeighboringNodeStorageTier::fclose(FileId& file_id) {
}
