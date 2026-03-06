#include "logger.h"
#include "spdlog/cfg/env.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

Logger::Logger() {

    //make sure Logger never exists if SPDLOG_ACTIVE_LEVEL is set to SPDLOG_LEVEL_OFF
    assert(SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF);

    spdlog::cfg::load_env_levels();
}

Logger::~Logger() {
}

Logger& Logger::getInstance() {

    static Logger instance; // Guaranteed to be destroyed.
                            // Instantiated on first use.
    return instance;
}

std::shared_ptr<spdlog::logger> Logger::make_logger(const std::basic_string<char> logger_name) {

    return logger = spdlog::stdout_color_mt(logger_name);
}
