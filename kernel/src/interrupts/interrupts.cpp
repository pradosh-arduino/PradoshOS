#include "interrupts.h"
#include "IDT.h"
#include "../errorScreen/errScr.h"
#include "../IO.h"
#include "../userinput/keyboard.h"
#include "../scheduling/pit/pit.h"
#include "../kernelUtil.h"

IDTDescEntry *ptr = NULL;

IDTR idtr;

IDTDescEntry *foo = NULL;

void* SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector){
    foo = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    foo->SetOffset((uint64_t)handler);
    foo->type_attr = type_attr;
    foo->selector = selector;
}
void PrepareInterrupts(){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)PITInt_Handler, 0x20, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DivideByZero_Handler, 0x0, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)InvalidOpCode_Handler, 0x6, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)StackSegmentFault_Handler, 0xC, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)Debug_Handler, 0x1, IDT_TA_TrapGate, 0x08);

    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();
}

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    Panic("Page Fault Detected", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void StackSegmentFault_Handler(interrupt_frame* frame){
    Panic("Stack Segment Fault", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void Debug_Handler(interrupt_frame* frame){
    Panic("Debug error", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void DivideByZero_Handler(interrupt_frame* frame){
    Panic("Division by zero", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void InvalidOpCode_Handler(interrupt_frame* frame){
    Panic("Invalid OP Code", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void DoubleFault_Handler(interrupt_frame* frame){
    Panic("Double Fault Detected", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void GPFault_Handler(interrupt_frame* frame){
    Panic("General Protection Fault Detected", "IDT", "loading the kernel", foo->GetOffset(), foo->type_attr, foo->selector);
    while(1){}
}

__attribute__((interrupt)) void KeyboardInt_Handler(interrupt_frame* frame){
    uint8_t scancode = inb(0x60);

    HandleKeyboard(scancode);

    PIC_EndMaster();
}

__attribute__((interrupt)) void MouseInt_Handler(interrupt_frame* frame){

    uint8_t mouseData = inb(0x60);

    HandlePS2Mouse(mouseData);

    PIC_EndSlave();
}

__attribute__((interrupt)) void PITInt_Handler(interrupt_frame* frame){
    PIT::Tick();
    PIC_EndMaster();
}


void PIC_EndMaster(){
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);

}