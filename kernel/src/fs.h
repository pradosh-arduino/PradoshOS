#pragma once

#include "BasicRenderer.h"

class File{
    public:
    const char* name;
    const char* extension;
    const char* contents;
    const char* path;
    long int size;
    int index;
    uint8_t* icon;
    File* metaDatas;
};

class Directory{
    public:
    const char* name;
    const char* path;
    int TotalFiles;
    int TotalFolder;
    bool read;
    bool write;

    File* File1;
    File* File2;
    File* File3;
    File* File4;
    File* File5;
};

class DirBackSlash{
    public:
    Directory* pradx_sys;
};

class VFS{
    public:
    void NewFile(const char* Fname, const char* Fextension, const char* Fcontents, File* NewFile, const char* Fpath);
    void DeleteFileOnSelected(const char* Fname);
    bool isFileExist(const char* Fname);
    const char* GetContents(File* File);
    void EditContentsOnSelect(const char* Fcontents);
    void SelectFile(File* file);
    void list();
    void MakeDir(const char* Dname, const char* path, bool Dread, bool Dwrite); // dont use this command it's under contruction
    void renameOnSelected(const char* newName);
    void changeExtension(const char* newExtension);
    long int GetFileSizeAt(int index);

    int totalFiles;
};
extern VFS* vFileSystem;

int length(const char* abc);
int equal(const char* a, const char* b);
void set(int *a, int *b);