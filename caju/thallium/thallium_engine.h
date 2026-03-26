#pragma once

#include <cstdio>
#include <thallium/bulk_mode.hpp>
#include <utility>
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
    static ThalliumEngine& getInstance();

    ~ThalliumEngine();

    inline thallium::bulk expose(const std::vector<std::pair<void*, size_t>>& segments, thallium::bulk_mode flag) {
        return this->engine.expose(segments, flag);
    }
    inline thallium::endpoint lookup(const std::string& server_address){
        return this->engine.lookup(server_address);
    }

    thallium::remote_procedure open_rpc_handler;
    thallium::remote_procedure open_variadic_rpc_handler;
    thallium::remote_procedure write_rpc_handler;
    thallium::remote_procedure read_rpc_handler;
    thallium::remote_procedure close_rpc_handler;

  private:
    ThalliumEngine(const std::string& local_address, int mode, bool use_progress_thread, int rpc_thread_count);
    ThalliumEngine()                       = delete;
    ThalliumEngine(const ThalliumEngine&&) = delete;
    void operator=(const Logger&)          = delete;

    void open_rpc(const thallium::request& req, const std::string& path, int flags, mode_t mode);
    void open_rpc(const thallium::request& req, const std::string& path, int flags);
    void write_rpc(const thallium::request& req, const thallium::bulk remote_bulk_handler, size_t count, int metadata_map_key);
    void read_rpc(const thallium::request& req, const thallium::bulk remote_bulk_handler, size_t count, int metadata_map_key);
    void close_rpc(const thallium::request& req, int metadata_map_key);

    thallium::engine engine;
};
