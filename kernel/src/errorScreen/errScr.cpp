#include "errScr.h"
#include "../BasicRenderer.h"
#include "../cstr.h"
#include "../mtask.h"
#include "../interrupts/IDT.h"
#include "../scheduling/pit/pit.h"
#include "../mtask.h"

void Panic(const char* msg, const char* location, const char* when, uint64_t offset, uint8_t type_attr, uint16_t selector){
    GlobalRenderer->ClearColour = 0x00eb3b3b;
    GlobalRenderer->Clear();
    GlobalRenderer->CursorPosition = {0, 0};

    //uint16_t sel = selectorI;

    GlobalRenderer->Print("Critical System Error!");
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("An error has been occured! You need to restart your computer, Hold down Power button for several seconds or press the restart button if the error occour multiple times please contact: pradoshnathan@gmail.com");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Error code:");
    GlobalRenderer->Next();
    GlobalRenderer->Print("0x");
    GlobalRenderer->Print(to_hstring((uint32_t)offset));
    GlobalRenderer->Next();
    GlobalRenderer->Print("Gate Type: ");
    if(type_attr == 0b10001110){
        GlobalRenderer->Print("IDT_TA_InterruptGate");
    }else if(type_attr == 0b10001100){
        GlobalRenderer->Print("IDT_TA_CallGate");
    }else if(type_attr == 0b10001111){
        GlobalRenderer->Print("IDT_TA_TrapGate");
    }else{
        GlobalRenderer->Print("Unknown Gate - (Very Critical error)");
    }
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
    //GlobalRenderer->Print("Current Process(s): ");
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
}