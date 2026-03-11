#pragma once

#include "caju/interface/native/native.h"
#include "caju/metadata/file_id.h"
#include <cstddef>
#include <cstdio>

class OpenCall {
};

class FOpenCall : public OpenCall {
};

template <class R>
class Call {
    virtual R call(FileId& file_id) = 0;
};

class Generic_fd_call {
  public:
    void*  buff;
    size_t count;

    Generic_fd_call(void* buff, size_t count) : buff{buff}, count{count} {};
};

class Generic_stream_call {
  public:
    void*  ptr;
    size_t size;
    size_t nmemb;

    Generic_stream_call(void* ptr, size_t size, size_t nmemb) : ptr{ptr}, size{size}, nmemb{nmemb} {}
};

class ReadCall : public Call<ssize_t>,
                 Generic_fd_call {

    ssize_t call(FileId& file_id) {
        int fd = (dynamic_cast<FileId_int>(file_id)).fd;

        return Native::read(fd, this->buff, this->count);
    }
};

class FReadCall : public Call<size_t>, Generic_stream_call {

    size_t call(FileId& file_id) {
        FILE* stream = (dynamic_cast<FileId_FILE>(file_id)).stream;

        return Native::fread(this->ptr, this->size, this->nmemb, stream);
    }
};

class WriteCall : public Call<ssize_t>, Generic_fd_call {
    ssize_t call(FileId& file_id) {
        int fd = (dynamic_cast<FileId_int>(file_id)).fd;

        return Native::write(fd, this->buff, this->count);
    }
};

class FWriteCall : Call<size_t>, Generic_stream_call {
    size_t call(FileId& file_id) {
        FILE* stream = (dynamic_cast<FileId_FILE>(file_id)).stream;

        return Native::fwrite(this->ptr, this->size, this->nmemb, stream);
    }
};
