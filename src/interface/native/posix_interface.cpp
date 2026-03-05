#include "native.h"
#include <cstdarg>

Caju caju = new Caju();

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

        if (!caju)
            return Native::open(path, flags, mode);

        return 0; // TODO
    } else {

        if (!caju)
            return Native::open(path, flags);

        return 0; // TODO
    }
}

int open64(const char* path, int flags, ...) {
    if (flags & O_CREAT) {
        va_list args;

        va_start(args, flags);
        mode_t mode = va_arg(args, int);
        va_end(args);

        if (!caju)
            return Native::open64(path, flags, mode);

        return 0; // TODO
    } else {

        if (!caju)
            return Native::open64(path, flags);

        return 0; // TODO
    }
}

ssize_t read(int fd, void* buf, size_t count) {
    if (!caju) {
        return Native::read(fd, buf, count);
    }
    if (fd == 0 || fd == 1 || fd == 2) {
        return Native::read(fd, buf, count);
    }
    return 0; // TODO
}
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    if (!caju) {
        return Native::fread(ptr, size, nmemb, stream);
    }
    return 0; // TODO
}

FILE* fopen(const char* pathname, const char* mode) {
    if (!caju)
        return Native::fopen(pathname, mode);
    return 0; // TODO
}

FILE* fopen64(const char* pathname, const char* mode) {
    if (!caju)
        return Native::fopen(pathname, mode);
    return 0; // TODO
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream) {
    if (!caju)
        return Native::fwrite(ptr, size, nmemb, stream);
    // check for writes to stdin/out/err

    return 0; // TODO
}

ssize_t write(int fd, const void* buf, size_t count) {
    if (!caju)
        return Native::write(fd, buf, count);
    // check for writes to stdin/out/err
    if (fd == 0 || fd == 1 || fd == 2) {
        return Native::write(fd, buf, count);
    }

    return 0; // TODO
}

ssize_t writev(int fd, const struct iovec* iov, int iovcnt) {
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

    if (!caju)
        return Native::close(fd);

    return 0; // TODO
}

int fclose(FILE* stream) {

    if (!caju)
        return Native::fclose(stream);

    return 0; // TODO
}
}
