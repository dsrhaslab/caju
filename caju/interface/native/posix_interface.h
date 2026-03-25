/**
 * @file posix_interface.h
 * @author Andre Lucena | Fabio Souza | Goncalo Sousa
 * @brief Declaration of the POSIX interface functions
 * @version 0.1
 * @date 2026-03-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 
#pragma once

#include <cstdio>

/**
 * @brief POSIX interface functions
 * 
 */
extern "C" {

int   open(const char* path, int flags, ...);
int   open64(const char* path, int flags, ...);
FILE* fopen(const char* pathname, const char* mode);
FILE* fopen64(const char* pathname, const char* mode);

ssize_t read(int fd, void* buf, size_t count);
size_t  fread(void* ptr, size_t size, size_t nmemb, FILE* stream);

size_t  fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
ssize_t write(int fd, const void* buf, size_t count);
ssize_t writev(int fd, const struct iovec* iov, int iovcnt);

int close(int fd);
int fclose(FILE* stream);
}
