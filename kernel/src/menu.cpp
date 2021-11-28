#include "menu.h"

void PrintConsole(){
    GlobalRenderer->CursorPosition = {0, 0};
    GlobalRenderer->Print("this is the the console which contolls the whole system.");
    GlobalRenderer->Next();
    GlobalRenderer->Print("POSConsole>>");
}