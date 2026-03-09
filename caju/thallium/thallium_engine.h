#pragma once

#include <vector> //this is here because it does not compile without it, idk why

#include "caju/logger/logger.h"
#include <cstddef>
#include <string>
#include <thallium/endpoint.hpp>
#include <thallium/engine.hpp>
#include <thallium/managed.hpp>
#include <thallium/remote_procedure.hpp>
#include <thallium/serialization/stl/string.hpp>
#include <thallium/task.hpp>
#include <thallium/thread.hpp>

class ThalliumEngine {
  public:
    ThalliumEngine(std::string& local_address, int mode);
    ~ThalliumEngine();

    int run_persistance_RPC(
        std::string   server_address_string,
        std::string   file_path,
        void**        buffers,
        hg_size_t*    sizes,
        int           buffer_count,
        int           original_fd,
        int           node_id,
        int           flags,
        std::string   mode,
        int           shard_id,
        bool          is_synchronous = true);

    void persistanceRPC(
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
        int                      optype);

    int run_persistance_RPC_synch(
        thallium::endpoint& server,
        size_t&             total_size,
        std::string         file_path,
        void**              buffers,
        hg_size_t*          sizes,
        int                 buffer_count,
        int                 original_fd,
        int                 node_id,
        int                 flags,
        std::string         mode,
        int                 shard_id);

    int run_persistance_RPC_asynch(
        thallium::endpoint& server,
        size_t&             total_size,
        std::string         file_path,
        void**              buffers,
        hg_size_t*          sizes,
        int                 buffer_count,
        int                 original_fd,
        int                 node_id,
        int                 flags,
        std::string         mode,
        int                 shard_id);

    static void CloseFDOnTargetRPC(thallium::request& request, int original_fd, std::string& path);
    thallium::engine           engine;

  private:
    thallium::remote_procedure persistanceRPC_remote_procedure;
};
