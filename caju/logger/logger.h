#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/logger.h>

class Logger {
  public:
    static Logger& getInstance();

    std::shared_ptr<spdlog::logger> make_logger(const std::basic_string<char> logger_name);

    ~Logger();

  private:
    std::shared_ptr<spdlog::logger> logger;

    Logger();

    Logger(const Logger&)         = delete;
    void operator=(const Logger&) = delete;
};

