#pragma once

#include <cstdio>
#include <fcntl.h>

using libc_open_t            = int (*)(const char*, int);
using libc_open_variadic_t   = int (*)(const char*, int, ...);
using libc_open64_t          = int (*)(const char*, int);
using libc_open64_variadic_t = int (*)(const char*, int, ...);
using libc_fopen_t           = FILE* (*)(const char*, const char*);
using libc_fopen64_t         = FILE* (*)(const char*, const char*);

using libc_read_t   = ssize_t (*)(int fd, void* buf, size_t count);
using libc_fread_t  = size_t (*)(void* ptr, size_t size, size_t nmemb, FILE* stream);

using libc_fwrite_t = size_t (*)(const void* ptr, size_t size, size_t nmemb, FILE* stream);
using libc_write_t  = ssize_t (*)(int, const void*, size_t);
using libc_writev_t = ssize_t (*)(int, const struct iovec*, int);

using libc_close_t  = int (*)(int);
using libc_fclose_t = int (*)(FILE*);

class Native {
  public:
    Native()                         = delete;
    Native(Native&&)                 = delete;
    Native(const Native&)            = delete;
    Native& operator=(Native&&)      = delete;
    Native& operator=(const Native&) = delete;
    ~Native()                        = delete;

    static int   open(const char* path, int flags);
    static int   open(const char* path, int flags, mode_t mode);
    static int   open64(const char* path, int flags);
    static int   open64(const char* path, int flags, mode_t mode);
    static FILE* fopen(const char* pathname, const char* mode);
    static FILE* fopen64(const char* pathname, const char* mode);

    static ssize_t read(int fd, void* buf, size_t count);
    static size_t  fread(void* ptr, size_t size, size_t nmemb, FILE* stream);

    static size_t  fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
    static ssize_t write(int fd, const void* buf, size_t count);
    static ssize_t writev(int fd, const struct iovec* iov, int iovcnt);

    static int close(int fd);
    static int fclose(FILE* stream);

  private:
};

