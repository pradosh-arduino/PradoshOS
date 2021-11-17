#include "fs.h"

typedef char * File;
File files [100][2];
int index;
bool fs_init(){
   for(int e = 0;e<100;e++){
      for(int i = 0;i<1000;i++){
         files[e][0]=(const char*)"";
         files[e][0]=(const char*)"";
      }
   }
   return true;
}
const char* getFileNameAt(int in){
   const char* out=(const char*)"";
   return files[in][0];
}
const char* getFileContentAt(int in){
   const char* out=(const char*)"";
   return files[in][1];
}
int getFileSizeOf(int in){
  return length(files[in][1]);
}
int getTotalFiles(){
  return index;
}
void createFile(const char* a,const char* b){
    files[index][0]=(char*)a;
    files[index][1]=(char*)b;
    index++;
}
void deleteFile(int in){
   index -= in;
}
const char* readFile(const char* name){
  for(int i = 0;i<index;i++){
     if(equal(files[i][0],name)){
        return files[i][1];
     }
  }
  return 0;
}
int length(const char* abc){
  for(int i = 0;;i++)
  if(abc[i]=='\0')return i;
}
bool equal(const char* a,const char* b){
for(int i =0 ;i<(length(a)+length(b))/2;i++){
if(a[i]!=b[i])return 0;
}
return 1;
}

void deleteContent(const char* fn){
 for(int i = 0;i<index;i++){
  if(equal(files[i][0],fn)){
    files[i][1]="\n";
    return;
  }
 }
}

bool canExec(const char* ae){
    const char* in  = readFile(ae);
    in = readFile(ae);
    in = readFile(ae);
    if(in != 0){
      //runFile(ae);
      return true;
    }
    else{ return false; }
}

int toInt(const char* abc){
 int out = 0;
 int temp = 1;
 for(int i = length(abc)-1;i>-1;i++){
   out += (abc[i]-0)*temp;
   temp++;
 }
 return out;

}

void deleteFileChar(const char* fileN){
 for(int i = 0;i<index;i++){
   if(_equal(files[i][0],fileN)){i = 0; return;}
 }
}

bool _equalS(const char* a, const char* b,int till){
 for(int i = 0;i<till;i++)
  if(a[i]!=b[i])return 0;
  return 1;
}

bool _equal(const char* a,const char* b){
   for(int i = 0;i<max(length(a),length(b));i++)
    if(a[i]!=b[i])return 0;
   return 1;
}

int max(int a,int b){
    if(a>b)return a;
    else return b;
}