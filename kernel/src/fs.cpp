#include "fs.h"
#include "MemoryMgmt.h"
#include "malloc.h"
#include "cstr.h"
#include "addons.h"

VFS* vFileSystem;

File* SelectedFile;
File* SelectedDir;

int totalFiles;

uint8_t FileIcon[] = {
  0b00111111, 0b11100000, 
  0b00100000, 0b00010000, 
  0b00100000, 0b00001000, 
  0b00100000, 0b00001000, 
  0b00101111, 0b11101000, 
  0b00100000, 0b00001000, 
  0b00101111, 0b11101000, 
  0b00100000, 0b00001000, 
  0b00101111, 0b11101000, 
  0b00100000, 0b00001000, 
  0b00101111, 0b11101000, 
  0b00111111, 0b11111000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
  0b00000000, 0b00000000, 
};

void VFS::NewFile(const char* Fname, const char* Fextension, const char* Fcontents, File* NewFile){
  if(!isFileExist(Fname)){
    NewFile->name = Fname;
    NewFile->extension = Fextension;
    NewFile->contents = Fcontents;
    NewFile->size = strlen(Fcontents);
    NewFile->index = totalFiles + 1;
    SelectedFile = NewFile;
    totalFiles++;
  }else{
    GlobalRenderer->Print("A File already Exist with the name:");
    GlobalRenderer->Print(Fname);
    GlobalRenderer->Next();
  }
}

void VFS::DeleteFileOnSelected(const char* Fname){
  if(isFileExist(Fname)){
    SelectedFile->name = NULL;
    SelectedFile->extension = NULL;
    SelectedFile->contents = NULL;
    SelectedFile->index = NULL;
    SelectedFile->size = 0;
    totalFiles--;
  }else{
    GlobalRenderer->Print("No Files Exist with the name:");
    GlobalRenderer->Print(Fname);
    GlobalRenderer->Next();
  }
}

bool VFS::isFileExist(const char* Fname){
  if(SelectedFile->name == Fname){
    return true;
  }else{
    return false;
  }
}

const char* VFS::GetContents(File* File){
  return File->contents;
}

void VFS::EditContentsOnSelect(const char* Fcontents){
  SelectedFile->contents = Fcontents;
}

void VFS::SelectFile(File* file){
  file = SelectedFile;
}

void VFS::list(){
  GlobalRenderer->LoadIcon(FileIcon, GlobalRenderer->CursorPosition, 0x00ffffff);
  GlobalRenderer->PutChar(' ');
  GlobalRenderer->PutChar(' ');
  GlobalRenderer->Print(SelectedFile->name);
  GlobalRenderer->PutChar('.');
  GlobalRenderer->Print(SelectedFile->extension);
  GlobalRenderer->PutChar(' ');
  GlobalRenderer->Print(to_string((long int)SelectedFile->size));
  GlobalRenderer->Print(" Bytes");
  GlobalRenderer->Next();
}

void VFS::MakeDir(const char* Dname, const char* path, bool Dread, bool Dwrite){
  Directory* newDir;
  newDir->name = Dname;
  if(path == "$root"){
    newDir->path = "/";
  }else{
    newDir->path = path;
  }
  newDir->read = Dread;
  newDir->write = Dwrite;
}

void VFS::renameOnSelected(const char* newName){
  SelectedFile->name = newName;
}

void VFS::changeExtension(const char* newExtension){
  SelectedFile->extension = newExtension;
}

int length(const char* abc)
{
	for (int i = 0;; i++)
		if (abc[i] == '\0')
			return i;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
int equal(const char* a, const char* b)
{
	for (int i = 0; i < max(length(a), length(b)); i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}
void set(int *a, int *b)
{
	for (int i = 0; b[i] != 0; i++)
	{
		a[i] = b[i];
	}
}
