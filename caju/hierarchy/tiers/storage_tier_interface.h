#ifndef CAJU_STORAGE_TIER_H
#define CAJU_STORAGE_TIER_H

#include <memory>
#include <unistd.h>

#include <caju/src/metadata/file_id.h>
#include <caju/src/hierarchy/utils/status.h>

class StorageTier {
    virtual Status<ssize_t> read (FileId& file_info, char* result, size_t n) = 0;
    virtual Status<ssize_t> read (FileId& file_info, char* result, uint64_t offset, size_t n) = 0;
    virtual Status<ssize_t> write(FileId& file_info, ) = 0;
    virtual Status<ssize_t> close(FileId& file_info, ) = 0;
    
};

#endif // CAJU_STORAGE_TIER_H