#include "userspace.h"

void StartUserspace(){
    GlobalRenderer->Print("sucessfully entered in userspace");
}
void LoopUserspace(){
    //nothing to do
}
void StopUserspace(){
    GlobalRenderer->ClearColour = 0xFF292929;
    GlobalRenderer->Clear();
    GlobalRenderer->Print("Saving your settings...");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Exiting Userspace...");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Stopping services...");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Stopping background processes...");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Requesting a system shutdown...");
    PlayShutdownSound();
    PIT::Sleepd(30);
}

void LoadKernelUserspace(){
    GlobalRenderer->Print("Kernel cannot be runned while Userspace is running");
}

void ErrorUserspace(){
    userPanic("Unable to enter userspace Kernel is not responding");
}