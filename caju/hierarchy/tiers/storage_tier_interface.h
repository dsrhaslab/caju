#pragma once

#include <memory>
#include <unistd.h>
#include <iostream>

#include <caju/metadata/file_id.h>
#include <caju/hierarchy/utils/status.h>

class StorageTier {
    virtual Status<ssize_t> read (FileId& file_id, char* result, size_t n) = 0;
    virtual Status<ssize_t> read (FileId& file_id, char* result, uint64_t offset, size_t n) = 0;
    virtual Status<ssize_t> write(FileId& file_id, ) = 0;
    virtual Status<ssize_t> close(FileId& file_id, ) = 0;
    
};
