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

class FdCallArguments {
  public:
    void*  buff;
    size_t count;

    FdCallArguments(void* buff, size_t count) : buff{buff}, count{count} {};
};

class StreamCallArguments {
  public:
    void*  ptr;
    size_t size;
    size_t nmemb;

    StreamCallArguments(void* ptr, size_t size, size_t nmemb) : ptr{ptr}, size{size}, nmemb{nmemb} {}
};

class ReadCall : public Call<ssize_t>,
                 FdCallArguments {

    ssize_t call(FileId* file_id) {
        int fd = (dynamic_cast<FileIdInt*>(file_id)).fd;

        return Native::read(fd, this->buff, this->count);
    }
};

class FReadCall : public Call<size_t>, StreamCallArguments {

    size_t call(FileId* file_id) {
        FILE* stream = (dynamic_cast<FileIdFILE*>(file_id)).stream;

        return Native::fread(this->ptr, this->size, this->nmemb, stream);
    }
};

class WriteCall : public Call<ssize_t>, FdCallArguments {
    ssize_t call(FileId* file_id) {
        int fd = (dynamic_cast<FileIdInt*>(file_id)).fd;

        return Native::write(fd, this->buff, this->count);
    }
};

class FWriteCall : Call<size_t>, StreamCallArguments {
    size_t call(FileId* file_id) {
        FILE* stream = (dynamic_cast<FileIdFILE*>(file_id)).stream;

        return Native::fwrite(this->ptr, this->size, this->nmemb, stream);
    }
};
