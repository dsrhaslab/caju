#include "thallium_engine.h"
#include "caju/logger/logger.h"
#include <abt.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <fcntl.h>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <thallium/anonymous.hpp>
#include <thallium/async_response.hpp>
#include <thallium/bulk.hpp>
#include <thallium/endpoint.hpp>
#include <thallium/engine.hpp>
#include <thallium/managed.hpp>
#include <thallium/pool.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/task.hpp>
#include <thallium/thread.hpp>
#include <unistd.h>
#include <utility>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("thallium_engine");
#endif

ThalliumEngine::ThalliumEngine(std::string& local_address, int mode) {

    this->engine = thallium::engine{local_address, mode, true, 2};

    SPDLOG_LOGGER_TRACE(logger, "Constructor: ThalliumEngine({}, {}, {}, {})", local_address, mode, true, 2);

    SPDLOG_LOGGER_DEBUG(logger, "ThalliumEngine address: {}", std::string(this->engine.self()));

    this->persistanceRPC_remote_procedure = this->engine.define(
        "persistanceRPC",
        [this](
            const thallium::request& req,
            thallium::bulk&          remote_bulk_handle,
            int                      size,
            int                      shard_id,
            std::string              file_path,
            int                      original_fd,
            int                      node_id,
            int                      flags,
            std::string              mode,
            int                      optype) {
            this->persistanceRPC(
                this->engine,
                req,
                remote_bulk_handle,
                size,
                shard_id,
                file_path,
                original_fd,
                node_id,
                flags,
                mode,
                optype);
        });
}

ThalliumEngine::~ThalliumEngine() {
    SPDLOG_LOGGER_TRACE(logger, "Destructor waiting for finalize");
    this->engine.finalize_and_wait();
    SPDLOG_LOGGER_TRACE(logger, "Destructor finalized");
}

int ThalliumEngine::run_persistance_RPC(
    const std::string server_address_string,
    std::string       file_path,
    void**            buffers,
    hg_size_t*        sizes,
    int               buffer_count,
    int               original_fd,
    int               node_id,
    int               flags,
    std::string       mode,
    int               shard_id,
    bool              is_synchronous) {

    // LOG(LogLevel1, "(ThalliumEngine) run_persistance_RPC called");
    // SPDLOG_LOGGER_TRACE(logger, "run_persistance_RPC()")

    int size = 0;

    for (int i = 0; i < buffer_count; i++) {
        size += sizes[i];
    }

    thallium::endpoint server = this->engine.lookup(server_address_string);

    std::vector<std::pair<void*, std::size_t>> segments(buffer_count);

    // std::cout << this->engine.self() << std::endl;

    for (int i = 0; i < buffer_count; i++) {
        if (!is_synchronous) {

            // std::cout << "sizes[i]: " << std::endl;

            // there is probably a better way to do this with smart pointers but im not good enough at c++ to do it
            void* local_buffer = malloc(sizes[i]);
            memcpy(local_buffer, buffers[i], sizes[i]);

            segments[i].first = local_buffer;
        } else {
            segments[i].first = buffers[i];
        }
        segments[i].second = sizes[i];
    }

    thallium::bulk bulk_handler = this->engine.expose(segments, thallium::bulk_mode::read_only);

    int x = size;
    if (is_synchronous) {

        x = this->persistanceRPC_remote_procedure.on(server)(
            bulk_handler,
            size,
            shard_id,
            file_path,
            original_fd,
            node_id,
            flags,
            mode);
    } else {

        // LOG(LogLevel1, "(ThalliumEngine) asynch sending data")

        std::shared_ptr<thallium::async_response> request = std::make_shared<thallium::async_response>(this->persistanceRPC_remote_procedure.on(server).async(
            bulk_handler,
            size,
            shard_id,
            file_path,
            original_fd,
            node_id,
            flags,
            mode));

        // LOG(LogLevel1, "(ThalliumEngine) asynch sent data")

        this->engine.get_progress_pool().make_thread(
            [bulk_handler = std::move(bulk_handler), segments = std::move(segments), request]() {
                // auto result = static_cast<int>(request.wait());

                // LOG(LogLevel1, "(ThalliumEngine) asynch wainting")
                request->wait();
                // LOG(LogLevel1, "(ThalliumEngine) asynch received request")

                for (auto var : segments) {
                    free(var.first);
                }
            },
            thallium::anonymous{});
    }

    // LOG(LogLevel1, "(ThalliumEngine) completed run_persistance_RPC call")

    return x;
}

void ThalliumEngine::persistanceRPC(
    thallium::engine&        engine,
    const thallium::request& req,
    thallium::bulk&          remote_bulk_handle,
    int                      size,
    int                      shard_id,
    std::string              file_path,
    int                      original_fd,
    int                      node_id,
    int                      flags,
    std::string              mode,
    int                      optype) {

#ifdef DEBUG
    Log::log_message(LogLevel2, "(ThalliumEngine) Got RPC request with file path: %s, size %lu", file_path.c_str(), size);

    if (optype == FOPEN) {
        Log::log_message(LogLevel3, "(ThalliumEngine) Got RPC request with optype fopen");
    } else if (optype == OPEN) {
        Log::log_message(LogLevel3, "(ThalliumEngine) Got RPC request with optype open");
    }
#endif // DEBUG

    thallium::endpoint endpoint = req.get_endpoint();

    std::vector<char> buffer_vector(size);

    std::vector<std::pair<void*, std::size_t>> segments(1);
    segments[0].first  = (void*)(&buffer_vector[0]);
    segments[0].second = buffer_vector.size();

    thallium::bulk local_bulk_handle = engine.expose(segments, thallium::bulk_mode::write_only);

    remote_bulk_handle.on(endpoint) >> local_bulk_handle;

#ifdef DEBUG
    Log::log_message(LogLevel1, "(ThalliumEngine) received buffer");
    Log::log_message(LogLevel1, "(ThalliumEngine) buffer_vector: %s", segments[0].first);
#endif // DEBUG

    // std::string rank = getenv("TASK_ID");
    // int fd = ((libc_open_variadic_t)dlsym(RTLD_NEXT, "open"))((rank + "_data").c_str(), O_WRONLY | O_CREAT, 0644);
    // size_t bytes_writen = ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd, segments[0].first, SIZE);

    /*
    StorageHierarchy::getInstance().store(
        (void**)&buffer_vector[0],
        (size_t*)&size,
        1,
        original_fd,
        node_id,
        file_path.c_str(),
        flags,
        mode.c_str(),
        OperationType(optype),
        shard_id);

    LOG(LogLevel1, "(ThalliumEngine) RPC responding to client");
    //*/

    // sleep(5);

    req.respond(12);

    // return hg_return(0);
}

void ThalliumEngine::CloseFDOnTargetRPC(thallium::request& request, int original_fd, std::string& path) {

    // LOG(LogLevel1, "(CloseFDOnTargetRPC) Got close RPC request with original_fd: %d, and path: %s", original_fd, path.c_str());

    // LOG(LogLevel2, "(CloseFDOnTargetRPC) executing close RPC for path: %s", path.c_str())

    // int close_return = StorageHierarchy::getInstance().close_checkpoint_fd(original_fd, path);

    request.respond(0);
}
