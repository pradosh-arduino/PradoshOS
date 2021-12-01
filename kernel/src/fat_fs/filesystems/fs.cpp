/*
#######################################
#                                     #
# File System Basics                  #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/

#include "fs.h"
#include "../../malloc.h"

File::File(const char* path, FileSystem* fs) {
    this->FileSys = fs;
    this->path = path;
    this->SectorOnDisk = fs->GetSector(path);
}

void File::Read(size_t amount) {
    this->FileSys->Read(this->SectorOnDisk, amount, this->contents);
}

void File::Write(size_t amount) {
    this->FileSys->Write(this->SectorOnDisk, amount, this->contents);
}

void File::Write(size_t amount, void* dataBuffer) {
    _memcpy( dataBuffer, this->contents, amount );
    this->FileSys->Write(this->SectorOnDisk, amount, this->contents);
}

File* Directory::GetFile(const char* name) { return NULL; }

Directory* Directory::GetDirectory(const char* name) { return NULL; }

bool Directory::CreateFile(const char* name) { return true; }

bool Directory::CreateDirectory(const char* name) { return true; }


FileSystem::FileSystem(AHCI::Port* port) {
    this->port = port;
    this->FS_Root = NULL;
}

FileSystem::~FileSystem() {}

void FileSystem::Read(size_t sector, size_t amount, void* dataBuffer) { return; }

void FileSystem::Write(size_t sector, size_t amount, void* dataBuffer) { return; }

uint64_t FileSystem::GetSector(const char* path) { return 0; }

Directory* FileSystem::GetDirectory(const char* path) { return NULL; }

File* FileSystem::GetFile(const char* path) { return NULL; }