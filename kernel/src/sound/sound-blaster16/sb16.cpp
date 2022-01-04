#include "sb16.h"

const uint32_t PCI_Enable_Bit = 0x80000000;
const uint32_t PCI_Config_Address = 0xCF8;
const uint32_t PCI_Config_Data = 0xCFC;

unsigned char pci_bus_sb16 = 0;
unsigned char pci_device_sb16 = 0;
unsigned char pci_device_fn_sb16 = 0;

SoundBlaster16* SB16;

uint32_t sb16_ioaddr;

DSP* dspPort;
DSP_Write* dspPortw;
MixerPort* Mixer;

SoundBlaster16::SoundBlaster16(DSP* dspPort, DSP_Write* dspPortw){
    ResetDSP(dspPort);
    TurnSpeakerOn(dspPortw);
    DMAChannel1();
    Program(dspPort);
    SetIRQ(dspPort);
    GlobalRenderer->Print("Sound Blaster 16 - sound card Initialized!");
    GlobalRenderer->Next();
}

SoundBlaster16::~SoundBlaster16(){
    GlobalRenderer->Print("Sound Blaster 16 - Exited");
}

uint16_t getDeviceAddr;

void SoundBlaster16::PCI(){
    for (uint8_t bus = 0; bus != 0xff; bus++) {
    // per bus there can be at most 32 devices
    for (int device = 0; device < 32; device++) {
      // every device can be multi function device of up to 8 functions
      for (int func = 0; func < 8; func++) {
        // read the first dword (index 0) from the PCI configuration space
        // dword 0 contains the vendor and device values from the PCI configuration space
        int data = r_pci_32(pci_bus_sb16, pci_bus_sb16, func, 0);
        if (data != 0xffffffff) {
           // parse the values
           uint16_t device_value = (data >> 16);
           uint16_t vendor = data & 0xFFFF;

           pci_bus_sb16 = bus;
           pci_device_sb16 = device;
           pci_device_fn_sb16 = func;
        }
      }
    }
  }

  for(getDeviceAddr = getDeviceAddr; getDeviceAddr < 0xFFFF; getDeviceAddr++){
    sb16_ioaddr = r_pci_32(pci_bus_sb16, getDeviceAddr, pci_device_fn_sb16, 4);
    GlobalRenderer->Print(" Device ID 0x");
    GlobalRenderer->Print(to_hstring((uint16_t)getDeviceAddr));
    GlobalRenderer->Next();
    
    exit();
    //if(r_pci_32(pci_bus_sb16, pci_device_sb16, pci_device_fn_sb16, 4) <= 0){
    //  
    //}else{
    //  //GlobalRenderer->Print("Found SB16! BUS: 0x");
    //  //GlobalRenderer->Print(to_hstring((uint16_t)pci_bus_sb16));
    //  //GlobalRenderer->Print(" Device: 0x");
    //  //GlobalRenderer->Print(to_hstring((uint16_t)pci_device_sb16));
    //  ////GlobalRenderer->Print(" Function: 0x");
    //  ////GlobalRenderer->Print(to_hstring((uint16_t)func));
    //  //GlobalRenderer->Print(" Device ID 0x");
    //  //GlobalRenderer->Print(to_hstring((uint16_t)getDeviceAddr));
    //  //GlobalRenderer->Next();
    //  exit();
    //}
  }
}

void exit(){
  for(int i=0;i<100;i++){
    
  }
  GlobalRenderer->Clear();
  GlobalRenderer->CursorPosition = {0, 0};
}

void SoundBlaster16::ResetDSP(DSP* dspPort){
    outb(dspPort->DSPReset, 0x01);
    outb(dspPort->DSPReset, 0x00);
    dspPort->DSPReadPort = 0xAA;
}

void SoundBlaster16::SetIRQ(DSP* dspPort){
    outb(dspPort->DSPMixerPort, 0x80);
    uint16_t GetIRQ = inb(dspPort->DSPMixerPort);
    outb(dspPort->DSPMixerDataPort, GetIRQ);
}

void SoundBlaster16::TurnSpeakerOn(DSP_Write* dspPortw){
    outb(dspPortw->SpeakerAddr, dspPortw->SpeakerOn);
}

void SoundBlaster16::TurnSpeakerOff(DSP_Write* dspPortw){
    outb(dspPortw->SpeakerAddr, dspPortw->SpeakerOff);
}

void SoundBlaster16::DMAChannel1(){
    outb(0x0A, 5);     // disable channel 1
    outb(0x0C, 1);     // filp flop
    outb(0x0B, 0x49);  // transfer mode
    outb(0x83, 0x01);  // Page Transfer
    outb(0x02, 0x04);  // Position Low Bit
    outb(0x02, 0x0F);  // Position High Bit
    outb(0x03, 0xFF);  // Count Low Bit
    outb(0x03, 0x0F);  // Count High Bit
    outb(0x0A, 1);     // enable channel 1
}

void SoundBlaster16::Program(DSP* dspPort){
    outb(dspPort->DSPWrite, 0x40);
    outb(dspPort->DSPWrite, 165);
    outb(dspPort->DSPWrite, 0xC0);
    outb(dspPort->DSPWrite, 0x00);
    outb(dspPort->DSPWrite, 0xFE);
    outb(dspPort->DSPWrite, 0x0F);
}

void SoundBlaster16::SetVolume(MixerPort* mixer, uint8_t volume){
    outb(mixer->MasterVolume, volume);
}

uint32_t SoundBlaster16::r_pci_32(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg) {

  uint32_t index = PCI_Enable_Bit | (bus << 16) | (device << 11) | (func << 8) | (pcireg << 2);

  outl(index, PCI_Config_Address);

  return inl(PCI_Config_Data);
}