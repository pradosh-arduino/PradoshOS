#include "shell.h"

Shell* GlobalShell;
bool isSerialInit = false;
const char* DriverVersion[]{
    "AHCI         1.0.0",
    "PCI          1.0.0",
    "ACPI         1.0.0",
    "MTask        1.4.0",
    "Shell        0.1.0",
    "Panic        2.0.0",
    "RTC          1.6.0",
    "Serial COM   0.0.3",
};

void Shell::Init(){
    GlobalRenderer->Print("User$PradoshOS @ P0:> ");
    setCursorPosition(GlobalRenderer->CursorPosition.X, GlobalRenderer->CursorPosition.Y);
}

void setCursorPosition(int xe,int ye){
   
}

void Shell::HandleCommand(char* command){
    if(__strcmp(command, "clear") == 0) {
        GlobalRenderer->Clear();
        GlobalRenderer->CursorPosition = {0, 0};
    }else if(__strcmp(command, "cpuid") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("CPU type:");
        GlobalRenderer->Print(getName());
        GlobalRenderer->Next();
        GlobalRenderer->Print("CPU Vendor ID:");
        GlobalRenderer->Print(getName());
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Next();
        GlobalRenderer->Print("CPU Architecture:");
        GlobalRenderer->Print("x86_64");
        GlobalRenderer->Colour = 0x00ffffff;
        GlobalRenderer->Next();
    }else if(__strcmp(command, "time") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("current time: ");
        GlobalRenderer->Print(to_string((float)getHours()));
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->PutChar('.');
        GlobalRenderer->Print(to_string((float)getMinutes()));
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->PutChar('.');
        GlobalRenderer->Print(to_string((float)getSeconds()));
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->Colour = 0x00ffffff;
        GlobalRenderer->Next();
    }else if(__strcmp(command, "info") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("This OS is made by Pradosh.S.");
        GlobalRenderer->Colour = 0x00ffffff;
        GlobalRenderer->Next();
    }else if(__strcmp(command, "plugin") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("command          sub-command        arguments");
        GlobalRenderer->Next();
        GlobalRenderer->Print("plugin            install       <plugin-name>");
        GlobalRenderer->Next();
        GlobalRenderer->Print("plugin            remove        <plugin-name>");
        GlobalRenderer->Next();
        GlobalRenderer->Print("plugin            config        <plugin-name>");
        GlobalRenderer->Next();
        GlobalRenderer->Print("plugin            list          -------------");
        GlobalRenderer->Colour = 0x00ffffff;
    }else if(__strcmp(command, "OSversion") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("OS version: ");
        GlobalRenderer->Print("PradX (PradoshOS) Blaster x86_64");
        GlobalRenderer->Next();
        GlobalRenderer->Print("Kernel const char*: ");
        GlobalRenderer->Print("PradX Kernel 0.1.0-stable V2");
        GlobalRenderer->Next();
        GlobalRenderer->Print("Bootloader const char*: ");
        GlobalRenderer->Print("PradX Custom bootloder (gnu-efi)");
        GlobalRenderer->Next();
        GlobalRenderer->Print("Bootloader Type: ");
        GlobalRenderer->Print("UEFI");
        GlobalRenderer->Colour = 0x00ffffff;
        GlobalRenderer->Next();
    }else if(__strcmp(command, "driverVersion") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        for(int i = 0; i < 7; i++){
            GlobalRenderer->Print(DriverVersion[i]);
            GlobalRenderer->Next();
        }
        GlobalRenderer->Colour = 0x00ffffff;
    }else if(__strcmp(command, "ls") == 0){
        ls();
    }else if(__strcmp(command, "") == 0){
        
    }else if(equalS((const char*)"print",command,4)){
        echo(command);
    }else if(__strcmp(command, "shutdown") == 0){
        shutdown();
    }else if(__strcmp(command, "reboot") == 0){
        restart();
    }else if(__strcmp(command, "InitSerial") == 0){
        if(isSerialInit == false){
            //GlobalSerial->serial_configure_baud_rate(0x3F8, 9600);
            if(GlobalSerial->serial_configure_baud_rate(0x3F8, 9600) == true){
                
            }else{
                GlobalRenderer->PutChar('.');
                PIT::Sleepd(1);
            }
            isSerialInit = true;
            GlobalRenderer->Println(to_hstring(GlobalSerial->read_serial()));
            GlobalSerial->write_serial('e');
            GlobalRenderer->Println(to_hstring(GlobalSerial->read_serial()));
        }else{
            GlobalRenderer->Println("Serial Initilized already!");
        }
    }else if(__strcmp(command, "GetAHCIDatas") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Println("Getting AHCI data this will take some time...");
        for(int t = 0; t < 1024; t++){
            //GlobalRenderer->PutChar(AHCIDatas[t]);
        }
        GlobalRenderer->Colour = 0x00ffffff;
    }else if(equalS((const char*)"help",command,11)){
        GlobalRenderer->Println("command         sub-command         arguments             syntax            info");
        GlobalRenderer->Println("clear               ~                   ~                  clear      clears the screen");
        GlobalRenderer->Println("cpuid               ~                   ~                  cpuid       prints cpu info");
        GlobalRenderer->Println("time                ~                   ~                  time           shows time");
        GlobalRenderer->Println("info                ~                   ~                  info       shows the person who made");
    }else if(__strcmp(command, "Registry") == 0){
        GlobalRenderer->Colour = 0x0000ccff;
        registry->PrintGroup("SYSTEM", true, 1, 2);
        registry->PrintGroup("DRIVERS", true, 2, 0);
        registry->PrintGroup("SOFTWARE", true, 2, 0);
        registry->PrintGroup("HARDWARE", true, 2, 0);
        registry->PrintGroup("CONSOLE", true, 2, 0);
        registry->PrintGroup("USER", true, 1, 2);
        GlobalRenderer->Colour = 0x00ffffff;
    }else{
        GlobalRenderer->Colour = 0x0000ccff;
        GlobalRenderer->Print("'");
        GlobalRenderer->Print(command);
        GlobalRenderer->Print("' is not recognized as an command or a file");
        GlobalRenderer->Colour = 0x00ffffff;
        GlobalRenderer->Next();
    }

    GlobalRenderer->Print("User$PradoshOS @ P0:> ");
}

void ClearCharTimes(int length){
    for(int i = 0; i < length; i++){
        GlobalRenderer->ClearChar();
    }
}
void echo(const char* command){
    if(command[5]==0)GlobalRenderer->Println("No input string! Syntax: print <message>");
    else if(length(command)>5){
     for(int i = 5;command[i]!=0;i++){
        GlobalRenderer->PutChar(command[i]);
     }
     GlobalRenderer->Next();
    }
}

void ls(){
    GlobalRenderer->Colour = 0x0000ccff;
    for(int i = 0;i < getTotalFiles(); i++){
        asm("cli");
        GlobalRenderer->Print(to_string((float)i));
        GlobalRenderer->ClearChar();
        GlobalRenderer->ClearChar();
        GlobalRenderer->Print(getFileNameAt(i));
        GlobalRenderer->Print("   ");
        GlobalRenderer->Print(to_string((float)getFileSizeOf(i)));
        GlobalRenderer->Print(" Bytes");
        GlobalRenderer->Next();
    }
    GlobalRenderer->Colour = 0x00ffffff;
}

bool equalS(const char* a, const char* b,int till){
 for(int i = 0;i<till;i++)
  if(a[i]!=b[i])return 0;
  return 1;
}