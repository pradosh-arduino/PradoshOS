#pragma once 
#include "../../IO.h"
#include "../../scheduling/pit/pit.h"
#include "../../BasicRenderer.h"
#include "../../cstr.h"

struct DSP{
    uint16_t DSPMixerPort = 0x224;
    uint16_t DSPMixerDataPort = 0x225;
    uint16_t DSPReset = 0x226;
    uint16_t DSPRead = 0x22A;
    uint16_t DSPWrite = 0x22C;
    uint16_t DSPReadStatus = 0x22E;
    uint16_t DSPReadPort;
};

struct DSP_Write{
    uint8_t OutputSampleRateAddr = 0x04;
    uint8_t TimeConstAddr = 0x40;
    uint8_t Stop8bit = 0xD0;
    uint8_t SpeakerOn = 0xD1;
    uint8_t SpeakerOff = 0xD3;
    uint8_t ResumePlayBack8bit = 0xD4;
    uint8_t Stop16bit = 0xD5;
    uint8_t ResumePlayBack16bit = 0xD6;
    uint16_t SpeakerAddr = 0x22C;
    //MISC
    uint8_t GetDSPVersion = 0xE1;
};

struct MixerPort{
    // 0xLR = L for Left channel, R for Right channel
    // Min Volume 0x0, Max Volume 0xF
    uint8_t MasterVolume = 0x22;

    //Set IRQ
    uint8_t IRQ = 0x80;
};

class SoundBlaster16{
    public:
    SoundBlaster16(DSP* dspPort, DSP_Write* dspPortw);
    ~SoundBlaster16();

    void ResetDSP(DSP* dspPort);
    void SetIRQ(DSP* dspPort);
    void TurnSpeakerOn(DSP_Write* dspPortw);
    void TurnSpeakerOff(DSP_Write* dspPortw);
    void DMAChannel1();
    void Program(DSP* dspPort);
    void SetVolume(MixerPort* mixer, uint8_t volume);
    uint32_t r_pci_32(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg);
    void PCI();
};
void exit();

extern SoundBlaster16* SB16;
extern DSP* dspPort;
extern DSP_Write* dspPortw;
extern MixerPort* Mixer;