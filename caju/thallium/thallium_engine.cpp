#include "thallium_engine.h"
#include "caju/logger/logger.h"
#include <abt.h>
#include <cstdlib>
#include <dlfcn.h>
#include <fcntl.h>
#include <spdlog/spdlog.h>
#include <string>
#include <thallium/anonymous.hpp>
#include <thallium/async_response.hpp>
#include <thallium/bulk.hpp>
#include <thallium/bulk_mode.hpp>
#include <thallium/endpoint.hpp>
#include <thallium/engine.hpp>
#include <thallium/managed.hpp>
#include <thallium/pool.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/task.hpp>
#include <thallium/thread.hpp>
#include <unistd.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("thallium_engine");
#endif

ThalliumEngine& ThalliumEngine::getInstance() {

    // Hard coding this for now
    static ThalliumEngine instance(
        "ofi+tcp",
        THALLIUM_SERVER_MODE,
        true,
        2);
    // Guaranteed to be destroyed.
    // Instantiated on first use.
    return instance;
}

ThalliumEngine::ThalliumEngine(const std::string& local_address, int mode, bool use_progress_thread, int rpc_thread_count) {

    this->engine = thallium::engine{local_address, mode, use_progress_thread, rpc_thread_count};

    SPDLOG_LOGGER_TRACE(logger, "Constructor: ThalliumEngine({}, {}, {}, {})", local_address, mode, use_progress_thread, rpc_thread_count);

    SPDLOG_LOGGER_DEBUG(logger, "ThalliumEngine constructed with address: {}", std::string(this->engine.self()));

    this->open_rpc_handler = this->engine.define(
        "open_rpc",
        [this](
            const thallium::request& req,
            const std::string        path,
            int                      flags) {
            open_rpc(req, path, flags);
        });

    this->open_variadic_rpc_handler = this->engine.define(
        "open_rpc",
        [this](
            const thallium::request& req,
            const std::string        path,
            int                      flags,
            unsigned int             mode) {
            open_rpc(req, path, flags, mode);
        });

    this->write_rpc_handler = this->engine.define(
        "write_rpc",
        [this](
            const thallium::request& req,
            const thallium::bulk     remote_bulk_handler,
            size_t                   count,
            int                      metadata_map_key) {
            write_rpc(req, remote_bulk_handler, count, metadata_map_key);
        });
}

void ThalliumEngine::open_rpc(const thallium::request& req, const std::string& path, int flags) {

    // TODO access the correct handler and get an fd back
    int fd = rand();

    SPDLOG_LOGGER_TRACE(logger, "open_rpc(req, path:{}, flags:{}) -> fd:{}", path, flags, fd);

    req.respond(fd);
}

void ThalliumEngine::open_rpc(const thallium::request& req, const std::string& path, int flags, mode_t mode) {

    // TODO access the correct handler and get an fd back
    int fd = rand();
    SPDLOG_LOGGER_TRACE(logger, "open_rpc(req, path:{}, flags:{}, mode:{}) -> fd:{}", path, flags, mode, fd);

    req.respond(fd);
}

void ThalliumEngine::close_rpc(const thallium::request& req, int metadata_map_key) {

    // TODO deffer close to the handler
    SPDLOG_LOGGER_TRACE(logger, "close(req, metadata_map_key:{})", metadata_map_key);

    req.respond(0);
}

void ThalliumEngine::write_rpc(const thallium::request& req, const thallium::bulk remote_bulk_handler, size_t count, int metadata_map_key) {

    thallium::endpoint client = req.get_endpoint();

    std::vector<std::pair<void*, std::size_t>> segments(1);

    char buffer[count];

    segments[0].first  = (void*)buffer;
    segments[0].second = count;

    thallium::bulk local_bulk_handle = this->engine.expose(segments, thallium::bulk_mode::write_only);

    SPDLOG_LOGGER_DEBUG(logger, "write_rpc(..., count:{}, metadata_map_key:{}) starting bulk transfer", count, metadata_map_key);

    remote_bulk_handler.on(client) >> local_bulk_handle;

    SPDLOG_LOGGER_DEBUG(logger, "write_rpc(..., count:{}, metadata_map_key:{}) bulk transfer completed", count, metadata_map_key);

    // TODO deffer next steps to handler and return bytes written
    size_t bytes_written = rand();

    SPDLOG_LOGGER_TRACE(logger, "write_rpc(req, remote_bulk_handler, count:{}, metadata_map_key:{}) -> bytes_written:{}", count, metadata_map_key, bytes_written);

    req.respond(bytes_written);
}

void ThalliumEngine::read_rpc(const thallium::request& req, const thallium::bulk remote_bulk_handler, size_t count, int metadata_map_key) {

    thallium::endpoint client = req.get_endpoint();

    std::vector<std::pair<void*, std::size_t>> segments(1);

    char buffer[count];

    segments[0].first  = (void*)buffer;
    segments[0].second = count;

    thallium::bulk local_bulk_handle = this->engine.expose(segments, thallium::bulk_mode::read_only);

    SPDLOG_LOGGER_DEBUG(logger, "read_rpc(..., count:{}, metadata_map_key:{}) starting bulk transfer", count, metadata_map_key);

    local_bulk_handle >> remote_bulk_handler.on(client);

    SPDLOG_LOGGER_DEBUG(logger, "read_rpc(..., count:{}, metadata_map_key:{}) bulk transfer completed", count, metadata_map_key);

    // TODO deffer next steps to handler and return bytes written
    size_t bytes_written = rand();

    SPDLOG_LOGGER_TRACE(logger, "read_rpc(req, remote_bulk_handler, count:{}, metadata_map_key:{}) -> bytes_written:{}", count, metadata_map_key, bytes_written);

    req.respond(bytes_written);
}

ThalliumEngine::~ThalliumEngine() {
    SPDLOG_LOGGER_TRACE(logger, "Destructor waiting for finalize");
    this->engine.finalize_and_wait();
    SPDLOG_LOGGER_TRACE(logger, "Destructor finalized");
}
