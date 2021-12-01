/*
#######################################
#                                     #
# File System Base Struct             #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/
#ifndef __FS_H
#define __FS_H
#include <stdint.h>
#include <stddef.h>
#include "../../ahci/ahci.h"


#if defined( __cplusplus )
#endif

struct FileSystem;

struct File{
    File(const char* path, FileSystem* fs);

public:
    const char* Name;
    const char* Extension;
    uint64_t Size;

public:
    void Read(size_t amount);
    void Write(size_t amount);
    void Write(size_t amount, void* dataBuffer);

    char* contents;
    FileSystem* FileSys;
    const char* path;

public:
    inline void SetContents(char* newContents) { this->contents = newContents; }

    inline char* GetContents() { return this->contents; }

    inline uint64_t GetSectorOnDisk(void) { return this->SectorOnDisk; }

    // WARNING: DO NOT DO THIS UNLESS YOU KNOW THE REAL SECTOR OR YOU COULD GET GARBAGE!
    inline void SetSectorOnDisk(uint64_t sector) { this->SectorOnDisk = sector; }

private:
    uint64_t SectorOnDisk;
};

struct Directory{
    File* GetFile(const char* name);
    Directory* GetDirectory(const char* name);
    bool CreateFile(const char* name);
    bool CreateDirectory(const char* name);

    File* files;
    Directory* directories;

private:
    
};

struct FileSystem{
    FileSystem(AHCI::Port* foo);
    ~FileSystem();

    Directory* GetDirectory(const char* path);
    File* GetFile(const char* path);

    void Read(size_t sector, size_t amount, void* dataBuffer);
    void Write(size_t sector, size_t amount, void* dataBuffer);

    uint64_t GetSector(const char* path);

protected:
    AHCI::Port* port;
    Directory* FS_Root;
};


#if defined( __cplusplus )
#endif


#endif