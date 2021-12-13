#pragma once
#include "../IO.h"
#include "../cstr.h"
#include "../BasicRenderer.h"

// docs >> https://www.wfbsoftware.de/realtek-rtl8139-network-interface-card/

class RTL8139{
    public:
    void Init();
    void PutIOAddr();
    void* PowerCard();
    void BusMaster();
    void SoftwareReset();
    void EnableTransfer();
    void SetTransferConfig();
    void SendTSAD();
    void GetMacAddr();

    public:
    uint32_t r_pci_32(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg);
    int read_eeprom(long ioaddr, int location);
};
extern RTL8139* rtl8139;
