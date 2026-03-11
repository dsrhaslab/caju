#pragma once

class OpenCall {

};

class FOpenCall : public OpenCall {

};

template <class R>
class Call {
    virtual R call(FileId& file_id) = 0;
};

class ReadCall : public Call<ssize_t> {
    ssize_t call (FileId& file_id);
};

class FReadCall : public Call<size_t> {
    size_t call (FileId& file_id);
};

class WriteCall {

};

class FWriteCall : public WriteCall {

};