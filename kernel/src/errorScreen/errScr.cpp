#include "errScr.h"
#include "../BasicRenderer.h"
#include "../cstr.h"
#include "../mtask.h"
#include "../interrupts/IDT.h"
#include "../scheduling/pit/pit.h"
#include "../mtask.h"
#include "regError.h"
#include "../userinput/keyboard.h"

bool halt;

void Panic(const char* msg, const char* location, const char* when, uint64_t offset, uint8_t type_attr, uint16_t selector){
    GlobalRenderer->ClearColour = 0x00eb3b3b;
    GlobalRenderer->Clear();
    GlobalRenderer->CursorPosition = {0, 0};

    halt = true;

    GlobalRenderer->Print("Critical System Error!");
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    GlobalRenderer->Print("An error has been occured! You need to restart your computer, Hold down Power button for several seconds or press the restart button if the error occour multiple times please contact: pradoshnathan@gmail.com");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Offset:");
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
    Point Reg64Pos = GlobalRenderer->CursorPosition;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RAX)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RBX)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RCX)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RDX)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RSP)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RBP)));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister64(__REG__RIP)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->CursorPosition.Y = Reg64Pos.Y;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__EAX)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__EBX)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__ECX)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__EDX)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__ESP)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__EBP)));
    GlobalRenderer->Next();
    GlobalRenderer->CursorPosition.X = Reg64Pos.X + 20 * 8;
    GlobalRenderer->Print(to_hstring((uint32_t)GetRegister32(__REG__EIP)));
    GlobalRenderer->Next();
    GlobalRenderer->Next();
    block_task(7);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Beginning of Task Cleanup");
    GlobalRenderer->Next();
    cleanup_terminated_task(task2);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Setting the kernel stack");
    GlobalRenderer->Next();
    set_kernel_stack(__REG__ESP);
    GlobalRenderer->Print("Done setting stack. location = ESP");
    GlobalRenderer->Next();
    kernel_idle_task();

}