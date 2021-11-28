#include "registry.h"

Registry* registry;

void Registry::Init(){
    //HGROUP 
}

void Registry::PrintKey(HKEY a){
    GlobalRenderer->Print("[HKEY] ");
    GlobalRenderer->Print(a);
}

void Registry::PrintGroup(HGROUP a, bool expaned, int subClass, int minus){
    int k = subClass * 16;
    if(k == 16){
        k = 1;
    }
    int m = minus * 8;
    GlobalRenderer->CursorPosition = {k, GlobalRenderer->CursorPosition.Y};
    GlobalRenderer->Print("[HGROUP] ");
    GlobalRenderer->Print(a);
    GlobalRenderer->Next();
    if(expaned == true){
        putSpace(GlobalRenderer->CursorPosition.X + 16 - m);
        GlobalRenderer->PutChar(0x004);
        GlobalRenderer->Print("-----");
        PrintKey("Default");
        GlobalRenderer->Next();
        putSpace(GlobalRenderer->CursorPosition.X + 16 - m);
        putSpace(6);
        PrintKey("Value");
    }
    GlobalRenderer->Next();
}

void putSpace(int f){
    for(int i = 0; i < f; i++){
        GlobalRenderer->PutChar(' ');
    }
}