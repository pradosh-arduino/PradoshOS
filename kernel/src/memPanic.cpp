#include "memPanic.h"
#include "BasicRenderer.h"
#include "Reboot.h"
#include "scheduling/pit/pit.h"
void PanicMem(const char* panicMemMessage){
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 5 sec..");
    PIT::Sleepd(1);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 4 sec..");
    PIT::Sleepd(1);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 3 sec..");
    PIT::Sleepd(1);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 2 sec..");
    PIT::Sleepd(1);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 1 sec..");
    PIT::Sleepd(1);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Memory Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMemMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 0 sec..");
    PIT::Sleepd(1);
    RebootSystem();
}