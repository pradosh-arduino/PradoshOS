#include "syscalls2.h"
#include "../BasicRenderer.h"
#include "../fs.h"

void Syscalls::Debug(const char* str){
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x0000ccff;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print(str);
    GlobalRenderer->Next();
}

void Syscalls::Done(const char* str){
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x0000ff00;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print(str);
    GlobalRenderer->Next();
}

void Syscalls::Failed(const char* str){
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x00ff0000;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print(str);
    GlobalRenderer->Next();
}

void Syscalls::Warn(const char* str){
    GlobalRenderer->Print("[");
    GlobalRenderer->Colour = 0x00ffff00;
    GlobalRenderer->Print("***");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print("]");
    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Print(str);
    GlobalRenderer->Next();
}

void Syscalls::LoadingAnim(){
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("\\");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("/");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("\\");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("/");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("\\");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("-");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Print("/");
    PIT::Sleepd(5);
    GlobalRenderer->ClearChar();
    GlobalRenderer->Colour = 0x0000ff00;
    GlobalRenderer->Print("Done");
    GlobalRenderer->Colour = 0x00ffffff;
}