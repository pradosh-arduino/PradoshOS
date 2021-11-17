#include "errScr.h"
#include "../BasicRenderer.h"
#include "../cstr.h"
#include "../mtask.h"
#include "../interrupts/IDT.h"
IDTDescEntry* descE;
void Panic(const char* msg, const char* location, const char* when, const char* Gate, uint8_t selector){
    GlobalRenderer->ClearColour = 0x00eb3b3b;
    GlobalRenderer->Clear();
    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Print("Critical System Error!");
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("An error has been occured! You need to restart your computer, Hold down Power button for several seconds or press the restart button if the error occour multiple times please contact: pradoshnathan@gmail.com");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Error code:");
    GlobalRenderer->Next();
    GlobalRenderer->Print("0x");
    GlobalRenderer->Print(to_hstring((uint16_t)descE->GetOffset()));
    GlobalRenderer->Next();
    GlobalRenderer->Print("Gate Type: ");
    GlobalRenderer->Print(Gate);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Selector: 0x");
    GlobalRenderer->Print(to_hstring((uint8_t)selector));
    GlobalRenderer->Next();
    GlobalRenderer->Print("error occoured at ");
    GlobalRenderer->Print(location);
    GlobalRenderer->Print(" while ");
    GlobalRenderer->Print(when);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("Main error:");
    GlobalRenderer->Print(msg);
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("Multitasking:  true");
    GlobalRenderer->Next();
    GlobalRenderer->Print("AHCI:          true");
    GlobalRenderer->Next();
    GlobalRenderer->Print("ACPI:          true");
    GlobalRenderer->Next();
    GlobalRenderer->Print("PCI:           true");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Verbose Mode:  false");
    GlobalRenderer->Next();
    GlobalRenderer->Print("system exited with error code: 1");
}