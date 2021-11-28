#pragma once
#include <stdint.h>

namespace ACPI{
    struct RSDP2{
        unsigned char Signature[8];
        uint8_t Checksum;
        uint8_t OEMId[6];
        uint8_t Revision;
        uint32_t RSDTAddress;
        uint32_t Length;
        uint64_t XSDTAddress;
        uint8_t ExtendedChecksum;
        uint8_t Reserved[3];
    }__attribute__((packed));

    struct SDTHeader{
        unsigned char Signature[4];
        uint32_t Length;
        uint8_t Revision;
        uint8_t Checksum;
        uint8_t OEMID[6];
        uint8_t OEMTableID[8];
        uint32_t OEMRevision;
        uint32_t CreatorID;
        uint32_t CreatorRevision;
    }__attribute__((packed));

    struct RSDPDescriptor20 {
        RSDP2 rdsp10;
        uint32_t Length;
        uint64_t XsdtAddress;
        uint8_t  ExtendedChecksum;
        uint8_t  reserved[3];
    } __attribute__ ((packed));

    struct MCFGHeader{
        SDTHeader Header;
        uint64_t Reserved;
    }__attribute__((packed));

    struct DeviceConfig{
        uint64_t BaseAddress;
        uint16_t PCISegGroup;
        uint8_t StartBus;
        uint8_t EndBus;
        uint32_t Reserved;
    }__attribute__((packed));

    struct XSDT{
        struct SDTHeader h;
    };

    struct FACPHeader
    {
        SDTHeader sdt;
        uint32_t  unneded1;
        uint32_t  DSDT;
        uint8_t   unneded2[48 - 44];
        uint32_t  SMI_CMD;
        uint8_t   ACPI_ENABLE;
        uint8_t   ACPI_DISABLE;
        uint8_t   unneded3[64 - 54];
        uint32_t  PM1a_CNT_BLK;
        uint32_t  PM1b_CNT_BLK;
        uint8_t   unneded4[89 - 72];
        uint8_t   PM1_CNT_LEN;
        uint8_t   unneded5[18];
        uint8_t   century;
    };

    void begin(const void* addr);

    void* FindTable(SDTHeader* stdHeader, char* signature);
}