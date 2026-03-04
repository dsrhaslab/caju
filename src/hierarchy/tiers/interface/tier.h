#ifndef CAJU_STORAGE_TIER_H
#define CAJU_STORAGE_TIER_H

#include <memory>
#include <unistd.h>
#include "utils/status.h"

class StorageTier {
    virtual Status<ssize_t> read (FileInfo& fd, char* result, size_t n) = 0;
    virtual Status<ssize_t> read (FileInfo& fd, char* result, uint64_t offset, size_t n) = 0;
    virtual Status<ssize_t> write(FileInfo& fd, ) = 0;
    virtual Status<ssize_t> close(FileInfo& fd) = 0;
    
};

#endif // CAJU_STORAGE_TIER_H