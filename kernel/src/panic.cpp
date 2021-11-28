#include "panic.h"
#include "BasicRenderer.h"
#include "Reboot.h"
#include "scheduling/pit/pit.h"
void Panic(const char* panicMessage){
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 5 sec..");
    PIT::Sleepd(10);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 4 sec..");
    PIT::Sleepd(10);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 3 sec..");
    PIT::Sleepd(10);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 2 sec..");
    PIT::Sleepd(10);
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
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

    GlobalRenderer->Print("Kernel Error Detected");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("contact: pradoshnathan@gmail.com for more info");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Rebooting in 0 sec..");
    PIT::Sleepd(10);
    RebootSystem();
}