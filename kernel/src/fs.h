#pragma once

bool fs_init();
const char* getFileNameAt(int in);
const char* getFileContentAt(int in);
int getTotalFiles();
const char* readFile();
void createFile(const char* a,const char* b);
int length(const char* abc);
bool equal(const char* a,const char* b);
int getFileSizeOf(int in);
void deleteContent(const char* fn);
void deleteFile(int in);
int toInt(const char* abc);
bool _equalS(const char* a, const char* b,int till);
void deleteFileChar(const char* fileN);
bool _equal(const char* a,const char* b);
int max(int a,int b);

//char AHCIDatas[1000000];