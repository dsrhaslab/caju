#pragma once

#include <memory>
#include <unistd.h>
#include <iostream>

#include <caju/metadata/file_id.h>
#include <caju/metadata/call_wrappers.h>
#include <caju/hierarchy/utils/status.h>

class StorageTier {

public:
    virtual Status<FileId&> open(OpenCall& open_call) = 0;
    virtual Status<int>     close(FileId& file_id) = 0;
    virtual Status<ssize_t> read(ReadCall& read_call) = 0;
    virtual Status<ssize_t> write(WriteCall& write_call) = 0;
    virtual Status<int>     remove(FileId& file_id) = 0;
    //virtual Status<FileId&> has_file(???) = 0;

};
