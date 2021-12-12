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

uint8_t randomPattern[] = {
  0x0f, 0xff, 0x0f, 0xff, 0xcc, 0x03, 0xcc, 0x03, 0xcf, 0x03, 0xcf, 0x30, 0xc3, 0x30, 0xc3, 0x3c, 
  0xf3, 0x3c, 0xf3, 0x0c, 0xf3, 0xcc, 0xf3, 0xcc, 0xc0, 0x0c, 0xc0, 0x0c, 0xff, 0xfc, 0xff, 0xfc
};

uint8_t miniRobotThing[] = {
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x20, 0x08, 0x28, 0x48, 0x20, 0x08, 0x28, 0x48, 0x2f, 0xc8, 
  0x20, 0x08, 0x1f, 0xf0, 0x04, 0x40, 0x04, 0x40, 0x04, 0x40, 0x04, 0x40, 0x00, 0x00, 0x00, 0x00
};

uint8_t idk[] = {
  0xf0, 0x00, 0xc0, 0x00, 0xa5, 0x75, 0x95, 0x55, 0x02, 0x52, 0x02, 0x6a, 0x00, 0x00, 0xfe, 0xfe, 
  0x82, 0x82, 0xaa, 0xaa, 0x82, 0x82, 0xfe, 0xfe, 0x28, 0x28, 0x28, 0x28, 0xff, 0xff, 0xff, 0xff
};

uint8_t Folder1[] = {
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x20, 0x40, 0x20, 0x7c, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 
  0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x20, 0x04, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uint8_t Folder2[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void VFS::NewFile(const char* Fname, const char* Fextension, const char* Fcontents, File* NewFile, const char* Fpath){
  if(!isFileExist(Fname)){
    NewFile->name = Fname;
    NewFile->extension = Fextension;
    NewFile->contents = Fcontents;
    NewFile->size = strlen(Fcontents);
    NewFile->path = Fpath;
    NewFile->index = totalFiles + 1;
    SelectedFile = NewFile;
    totalFiles++;
  }else{
    GlobalRenderer->Print("A File already Exist with the name:");
    GlobalRenderer->Print(Fname);
    GlobalRenderer->Next();
  }
}
/*
void VFS::NewFolder(const char* Dname, Directory* NewFolder, const char* Dpath, bool Dread, bool Dwrite){
  if(!isFileExist(Fname)){
    NewFolder->name = Fname;
    NewFolder->path = Fpath;
    NewFolder->read = Dread;
    NewFolder->write = Dwrite;
    SelectedDir = NewFile;
  }else{
    GlobalRenderer->Print("A Folder already Exist with the name:");
    GlobalRenderer->Print(Fname);
    GlobalRenderer->Next();
  }
}*/

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

/*void VFS::listFolder(){
  if(SelectedDir->read == true){
    GlobalRenderer->LoadIcon(Folder1, GlobalRenderer->CursorPosition, 0x00ffffff);
    GlobalRenderer->LoadIcon(Folder2, GlobalRenderer->CursorPosition, 0x009e9e9e);
    GlobalRenderer->PutChar(' ');
    GlobalRenderer->PutChar(' ');
    GlobalRenderer->Print(SelectedDir->name);
    GlobalRenderer->PutChar(' ');
    GlobalRenderer->Print(SelectedFile->path);
    GlobalRenderer->Next();
  }else{

  }
}*/

/*void NewFileInDir(Directory* NewFolder, const char* name, const char* extension, const char* contents){
  
}*/

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
