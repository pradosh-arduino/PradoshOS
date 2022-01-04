#include "../BasicRenderer.h"
#include "setup.h"
void InitializeSetup(){
     GlobalRenderer->Clear();
     GlobalRenderer->ClearColour = 0x00805080; // backround
     GlobalRenderer->Clear();
     GlobalRenderer->Print("Welcome to PradoshOS installation");
     GlobalRenderer->Next();
}