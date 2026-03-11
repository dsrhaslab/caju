#pragma once

#include <caju/hierarchy/tiers/storage_tier_interface.h>
#include <caju/interface/native/native.h>

class PosixFileSystemStorageTier : public StorageTier {
    Status<FileId&> open(OpenCall& open_call);
    //Status<FileId>  open(const char* pathname, int flags, mode_t mode);
    //Status<FileId>  fopen(const char* pathname, int flags, mode_t mode);
    //Status<FileId>  open64(const char* pathname, int flags, mode_t mode);
    //Status<FileId>  fopen64(const char* pathname, int flags, mode_t mode);
    
    Status<int>     close(FileId& file_id);

    Status<ssize_t> read(ReadCall& read_call);
    //Status<ssize_t> read(FileId& file_id, void* result, size_t n);
    //Status<ssize_t> read(FileId& file_id, void* result, uint64_t offset, size_t n);
    //Status<size_t>  fread(FileId& file_id, void* result, size_t size, size_t n);

    Status<ssize_t> write(WriteCall& write_call);
    //Status<ssize_t> write(FileId& file_id, const void* buf, size_t count);
    //Status<size_t>  fwrite(FileId& file_id, const void* ptr, size_t size, size_t n);

    Status<int>     remove(FileId& file_id);
};
