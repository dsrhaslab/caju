/**
 * @file posix_interface.cpp
 * @author Andre Lucena | Fabio Souza | Goncalo Sousa
 * @brief Implementation of the POSIX interface functions
 * @version 0.1
 * @date 2026-03-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 
#include "native.h"
#include "spdlog/spdlog.h"
#include "caju/caju.h"
#include "caju/logger/logger.h"
#include <cstdarg>
#include <spdlog/common.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
static auto logger = Logger::getInstance().make_logger("posix_operations");
#endif // SPDLOG_ACTIVE_LEVEL |= SPD_LEVEL_OFF

Caju* caju = new Caju();

extern "C" {

static __attribute__((constructor)) void init_method() {
}

static __attribute__((destructor)) void destroy_method() {
}

int open(const char* path, int flags, ...) {
    if (flags & O_CREAT) {
        va_list args;

        va_start(args, flags);
        mode_t mode = va_arg(args, int);
        va_end(args);

        SPDLOG_LOGGER_TRACE(logger, "open({}, {}, {})", path, flags, mode);

        if (!caju)
            return Native::open(path, flags, mode);

        return 0; // TODO
    } else {

        if (!caju)
            return Native::open(path, flags);

        SPDLOG_LOGGER_TRACE(logger, "open({}, {})", path, flags);
        return 0; // TODO
    }
}

int open64(const char* path, int flags, ...) {
    if (flags & O_CREAT) {
        va_list args;

        va_start(args, flags);
        mode_t mode = va_arg(args, int);
        va_end(args);

        SPDLOG_LOGGER_TRACE(logger, "open64({}, {}, {})", path, flags, mode);
        if (!caju)
            return Native::open64(path, flags, mode);

        return 0; // TODO
    } else {

        SPDLOG_LOGGER_TRACE(logger, "open64({}, {})", path, flags);
        if (!caju)
            return Native::open64(path, flags);

        return 0; // TODO
    }
}

FILE* fopen(const char* pathname, const char* mode) {
    SPDLOG_LOGGER_TRACE(logger, "fopen({}, {})", pathname, mode);
    if (!caju)
        return Native::fopen(pathname, mode);
    return 0; // TODO
}

FILE* fopen64(const char* pathname, const char* mode) {

    SPDLOG_LOGGER_TRACE(logger, "fopen64({}, {})", pathname, mode);

    if (!caju)
        return Native::fopen(pathname, mode);
    return 0; // TODO
}

ssize_t read(int fd, void* buf, size_t count) {
    SPDLOG_LOGGER_TRACE(logger, "read({}, {}, {})", fd, buf, count);
    if (!caju) {
        return Native::read(fd, buf, count);
    }
    if (fd == 0 || fd == 1 || fd == 2) {
        return Native::read(fd, buf, count);
    }
    return 0; // TODO
}
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    SPDLOG_LOGGER_TRACE(logger, "read({}, {}, {}, stream*)", ptr, size, nmemb);
    if (!caju) {
        return Native::fread(ptr, size, nmemb, stream);
    }
    return 0; // TODO
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream) {

    SPDLOG_LOGGER_TRACE(logger, "fwrite({}, {}, {}, stream*)", ptr, size, nmemb);

    if (!caju)
        return Native::fwrite(ptr, size, nmemb, stream);
    // check for writes to stdin/out/err

    return 0; // TODO
}

ssize_t write(int fd, const void* buf, size_t count) {

    SPDLOG_LOGGER_TRACE(logger, "write({}, {}, {})", fd, buf, count);

    if (!caju)
        return Native::write(fd, buf, count);
    // check for writes to stdin/out/err
    if (fd == 0 || fd == 1 || fd == 2) {
        return Native::write(fd, buf, count);
    }

    return 0; // TODO
}

ssize_t writev(int fd, const struct iovec* iov, int iovcnt) {

    SPDLOG_LOGGER_TRACE(logger, "writev({}, iov*, {})", fd, iovcnt);

    if (!caju)
        return Native::writev(fd, iov, iovcnt);
    // check for writes to stdin/out/err
    if (fd == 0 || fd == 1 || fd == 2) {
        return Native::writev(fd, iov, iovcnt);
    }
    // return ((libc_writev_t)dlsym(RTLD_NEXT, "writev"))(fd, iov, iovcnt);
    return 0; // TODO
}

int close(int fd) {

    SPDLOG_LOGGER_TRACE(logger, "close({})", fd);

    if (!caju)
        return Native::close(fd);

    return 0; // TODO
}

int fclose(FILE* stream) {

    SPDLOG_LOGGER_TRACE(logger, "fclose(stream*)");
    if (!caju)
        return Native::fclose(stream);

    return 0; // TODO
}
}
