#include "RTL8139.h"

long ee_addr;

int mac_address_index = 0;

uint32_t mac_address[6];

#define eeprom_delay() inl(ee_addr)

#define EE_WRITE_CMD (5 << 6)
#define EE_READ_CMD (6 << 6)
#define EE_ERASE_CMD (7 << 6)

const uint32_t PCI_ENABLE_BIT = 0x80000000;
const uint32_t PCI_CONFIG_ADDRESS = 0xCF8;
const uint32_t PCI_CONFIG_DATA = 0xCFC;

int realtek8319Found = 0;

unsigned char pci_bus = 0;
unsigned char pci_device = 0;
unsigned char pci_device_fn = 0;

unsigned char bus = 0;
unsigned char device = 0;
unsigned char device_fn = 0;

uint8_t ChipCmd = 0x37;

uint32_t pci_ioaddr;

unsigned long ioaddr;

uint8_t TxConfig = 0x40;
uint8_t RxConfig = 0x44;

#define EE_SHIFT_CLK	    0x04	/* EEPROM shift clock. */
#define EE_CS		        0x08	/* EEPROM chip select. */
#define EE_DATA_WRITE	    0x02	/* EEPROM chip data in. */
#define EE_WRITE_0	        0x00
#define EE_WRITE_1      	0x02
#define EE_DATA_READ	    0x01	/* EEPROM chip data out. */
#define EE_ENB		    (0x80 | EE_CS)

uint8_t Cfg9346=0x50, Config0=0x51, Config1=0x52;

RTL8139* rtl8139;

void RTL8139::Init(){
        // there are 256 busses allowed
    for (bus = 0; bus != 0xff; bus++) {

    // per bus there can be at most 32 devices
    for (device = 0; device < 32; device++) {

      // every device can be multi function device of up to 8 functions
      for (int func = 0; func < 8; func++) {

        // read the first dword (index 0) from the PCI configuration space
        // dword 0 contains the vendor and device values from the PCI configuration space
        int data = r_pci_32(bus, device, func, 0);
        if (data != 0xffffffff) {
        
           // parse the values
           uint16_t device_value = (data >> 16);
           uint16_t vendor = data & 0xFFFF;

           // check vendor and device against the values of the RTL 8139 PCI device
           realtek8319Found = 0;
           if (vendor == 0x10ec && device_value == 0x8139) {

            realtek8319Found = 1;

            pci_bus = bus;
            pci_device = device;
            pci_device_fn = func;

            pci_ioaddr = r_pci_32(pci_bus, pci_device, pci_device_fn, 4);

            GlobalRenderer->Print("RTL8139 found! bus: ");
            GlobalRenderer->Print(to_hstring((uint16_t)pci_bus));
            GlobalRenderer->Next();
            GlobalRenderer->Print(" device: ");
            GlobalRenderer->Print(to_hstring((uint16_t)pci_device));
            GlobalRenderer->Next();
            GlobalRenderer->Print(" func: ");
            GlobalRenderer->Next();
            GlobalRenderer->Print(to_hstring((uint64_t)pci_device_fn));
            GlobalRenderer->Next();
          }
        }
      }
    }
  }

    PutIOAddr();
    PowerCard();
    EnableTransfer();
    SetTransferConfig();
    GetMacAddr();
}

uint32_t RTL8139::r_pci_32(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg) {

  uint32_t index = PCI_ENABLE_BIT | (bus << 16) | (device << 11) | (func << 8) |
                 (pcireg << 2);

  outl(index, PCI_CONFIG_ADDRESS);

  return inl(PCI_CONFIG_DATA);
}

void RTL8139::PutIOAddr(){
    GlobalRenderer->Print("pci ioaddr: 0x");
    GlobalRenderer->Print(to_hstring((uint32_t)pci_ioaddr));
    GlobalRenderer->Next();

    ioaddr = pci_ioaddr & ~3;

    GlobalRenderer->Print("ioaddr: 0x");
    GlobalRenderer->Print(to_hstring((unsigned long)ioaddr));
}

void* RTL8139::PowerCard(){
    outb(0x00, ioaddr + Config1);
    return 0;
}

void RTL8139::BusMaster(){
    GlobalRenderer->Print("BUS mastering ...");

    uint16_t command_register = r_pci_32(pci_bus, pci_device, pci_device_fn, 0x04);

    GlobalRenderer->Print("BUS mastering command_register = 0x");
    GlobalRenderer->Print(to_hstring((uint32_t)command_register));
    GlobalRenderer->Next();

    command_register |= 0x04;

    command_register = r_pci_32(pci_bus, pci_device, pci_device_fn, 0x04);

    GlobalRenderer->Print("BUS mastering command_register = 0x");
    GlobalRenderer->Print(to_hstring((uint32_t)command_register));
    GlobalRenderer->Next();
}

void RTL8139::SoftwareReset(){
    outb(0x10, ioaddr + ChipCmd);
    while ((inb(ioaddr + ChipCmd) & 0x10) != 0) {
      GlobalRenderer->Print("waiting for reset!");
    }
    GlobalRenderer->Next();
    GlobalRenderer->Print("Reset done.");
}

void RTL8139::EnableTransfer(){
    outb(0x0C, ioaddr + ChipCmd);
    GlobalRenderer->Print("Enable receiver and transmitter done.");
}

void RTL8139::SetTransferConfig(){
    outl(0x03000700, ioaddr + TxConfig);
    outl(0x0000070a, ioaddr + RxConfig);
}

void RTL8139::SendTSAD(){
    // under construction
}

int RTL8139::read_eeprom(long ioaddr, int location) {

  unsigned retval = 0;
  ee_addr = ioaddr + Cfg9346;
  int read_cmd = location | EE_READ_CMD;

  outb(EE_ENB & ~EE_CS, ee_addr);
  outb(EE_ENB, ee_addr);

  // Shift the read command bits out.
  for (int i = 10; i >= 0; i--) {

    int dataval = (read_cmd & (1 << i)) ? EE_DATA_WRITE : 0;

    outb(EE_ENB | dataval, ee_addr);
    eeprom_delay();

    outb(EE_ENB | dataval | EE_SHIFT_CLK, ee_addr);
    eeprom_delay();
  }

  outb(EE_ENB, ee_addr);
  eeprom_delay();

  for (int i = 16; i > 0; i--) {

    outb(EE_ENB | EE_SHIFT_CLK, ee_addr);
    eeprom_delay();

    retval = (retval << 1) | ((inb(ee_addr) & EE_DATA_READ) ? 1 : 0);

    outb(EE_ENB, ee_addr);
    eeprom_delay();
  }

  // Terminate the EEPROM access.
  outb(~EE_CS, ee_addr);

  return retval;
}

void RTL8139::GetMacAddr(){
    for (int i = 0; i < 6; i++) {
      mac_address[i] = 0;
    }

    int readEEPROMResult = read_eeprom(ioaddr, 0) != 0xffff;
    if (readEEPROMResult) {

      // loop three times to read three int (= 32 bit)
      for (int i = 0; i < 3; i++) {

        uint16_t data = read_eeprom(ioaddr, i + 7);

        mac_address[mac_address_index] = data & 0xFF;
        mac_address[mac_address_index + 1] = data >> 8;

        mac_address_index += 2;
      }

    } else {

      // loop six times
      for (int i = 0; i < 6; i++) {

        uint16_t data = inb(ioaddr + i);

        mac_address_index += 1;
      }
    }

    GlobalRenderer->Print("MAC: ");
    for (int i = 0; i < 6; i++) {
      GlobalRenderer->PutChar(mac_address[i]);
    }
    GlobalRenderer->Next();
}