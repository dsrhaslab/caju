#include "native.h"
#include <dlfcn.h>
#include <fcntl.h>

int Native::open(const char* path, int flags, mode_t mode) {
    return ((libc_open_variadic_t)dlsym(RTLD_NEXT, "open"))(path, flags, mode);
}

int Native::open(const char* path, int flags) {
    return ((libc_open_t)dlsym(RTLD_NEXT, "open"))(path, flags);
}

int Native::open64(const char* path, int flags, mode_t mode) {
    return ((libc_open64_variadic_t)dlsym(RTLD_NEXT, "close"))(path, flags, mode);
}

int Native::open64(const char* path, int flags) {
    return ((libc_open64_t)dlsym(RTLD_NEXT, "close"))(path, flags);
}

FILE* Native::fopen(const char* pathname, const char* mode) {
    return ((libc_fopen_t)dlsym(RTLD_NEXT, "fopen"))(pathname, mode);
}

FILE* Native::fopen64(const char* pathname, const char* mode) {
    return ((libc_fopen64_t)dlsym(RTLD_NEXT, "fopen64"))(pathname, mode);
}

ssize_t Native::read(int fd, void* buf, size_t count) {
    return ((libc_read_t)dlsym(RTLD_NEXT, "read"))(fd, buf, count);
}
size_t Native::fread(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return ((libc_fread_t)dlsym(RTLD_NEXT, "fread"))(ptr, size, nmemb, stream);
}

size_t Native::fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return ((libc_fwrite_t)dlsym(RTLD_NEXT, "fwrite"))(ptr, size, nmemb, stream);
}

ssize_t Native::write(int fd, const void* buf, size_t count) {
    return ((libc_write_t)dlsym(RTLD_NEXT, "write"))(fd, buf, count);
}

ssize_t Native::writev(int fd, const struct iovec* iov, int iovcnt) {
    return ((libc_writev_t)dlsym(RTLD_NEXT, "writev"))(fd, iov, iovcnt);
}

int Native::close(int fd) {
    return ((libc_close_t)dlsym(RTLD_NEXT, "close"))(fd);
}

int Native::fclose(FILE* stream) {
    return ((libc_fclose_t)dlsym(RTLD_NEXT, "fclose"))(stream);
}
