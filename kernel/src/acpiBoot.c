#include "malloc.h"
#include "cstr.h"

const int MAX_CPU_COUNT = 10;

uint8_t *g_localApicAddr;

uint32_t g_acpiCpuCount;
uint8_t g_acpiCpuIds[MAX_CPU_COUNT];


typedef struct AcpiHeader
{
    uint32_t signature;
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oem[6];
    uint8_t oemTableId[8];
    uint32_t oemRevision;
    uint32_t creatorId;
    uint32_t creatorRevision;
} __attribute__((packed)) AcpiHeader;

// ------------------------------------------------------------------------------------------------
typedef struct AcpiFadt
{
    AcpiHeader header;
    uint32_t firmwareControl;
    uint32_t dsdt;
    uint8_t reserved;
    uint8_t preferredPMProfile;
    uint16_t sciInterrupt;
    uint32_t smiCommandPort;
    uint8_t acpiEnable;
    uint8_t acpiDisable;
    // TODO - fill in rest of data
} __attribute__((packed)) AcpiFadt;

// ------------------------------------------------------------------------------------------------
typedef struct AcpiMadt
{
    AcpiHeader header;
    uint32_t localApicAddr;
    uint32_t flags;
} __attribute__((packed)) AcpiMadt;

// ------------------------------------------------------------------------------------------------
typedef struct ApicHeader
{
    uint8_t type;
    uint8_t length;
} __attribute__((packed)) ApicHeader;

// APIC structure types
#define APIC_TYPE_LOCAL_APIC            0
#define APIC_TYPE_IO_APIC               1
#define APIC_TYPE_INTERRUPT_OVERRIDE    2

// ------------------------------------------------------------------------------------------------
typedef struct ApicLocalApic
{
    ApicHeader header;
    uint8_t acpiProcessorId;
    uint8_t apicId;
    uint32_t flags;
} __attribute__((packed)) ApicLocalApic;

// ------------------------------------------------------------------------------------------------
typedef struct ApicIoApic
{
    ApicHeader header;
    uint8_t ioApicId;
    uint8_t reserved;
    uint32_t ioApicAddress;
    uint32_t globalSystemInterruptBase;
} __attribute__((packed)) ApicIoApic;

// ------------------------------------------------------------------------------------------------
typedef struct ApicInterruptOverride
{
    ApicHeader header;
    uint8_t bus;
    uint8_t source;
    uint32_t interrupt;
    uint16_t flags;
} __attribute__((packed)) ApicInterruptOverride;

// ------------------------------------------------------------------------------------------------
static AcpiMadt *s_madt;

// ------------------------------------------------------------------------------------------------
static void AcpiParseFacp(AcpiFadt *facp)
{
    if (facp->smiCommandPort)
    {
        GlobalRenderer->Print("Enabling ACPI");
        outb(facp->smiCommandPort, facp->acpiEnable);
        GlobalRenderer->Print("ACPI enabled!");

        // TODO - wait for SCI_EN bit
    }
    else
    {
        GlobalRenderer->Print("ACPI already enabled");
        GlobalRenderer->Next();
    }
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseApic(AcpiMadt *madt)
{
    s_madt = madt;

    GlobalRenderer->Print("Local APIC Address = ");
    GlobalRenderer->Print(to_hstring((uint32_t)madt->localApicAddr));
    GlobalRenderer->Next();
    g_localApicAddr = (uint8_t *)(uintptr_t)madt->localApicAddr;

    uint8_t *p = (uint8_t *)(madt + 1);
    uint8_t *end = (uint8_t *)madt + madt->header.length;

    while (p < end)
    {
        ApicHeader *header = (ApicHeader *)p;
        uint8_t type = header->type;
        uint8_t length = header->length;

        if (type == APIC_TYPE_LOCAL_APIC)
        {
            ApicLocalApic *s = (ApicLocalApic *)p;

            GlobalRenderer->Print("Found CPU:");
            GlobalRenderer->Next();
            GlobalRenderer->Print("ApicProcessorID:");
            GlobalRenderer->Print(to_hstring((uint8_t)s->acpiProcessorId));
            GlobalRenderer->Next();
            GlobalRenderer->Print("ApicID:");
            GlobalRenderer->Print(to_hstring((uint8_t)s->apicId));
            GlobalRenderer->Next();
            GlobalRenderer->Print("Flags:");
            GlobalRenderer->Print(to_hstring((uint32_t)s->flags));
            GlobalRenderer->Next();

            if (g_acpiCpuCount < MAX_CPU_COUNT)
            {
                g_acpiCpuIds[g_acpiCpuCount] = s->apicId;
                ++g_acpiCpuCount;
            }
        }
        else if (type == APIC_TYPE_IO_APIC)
        {
            ApicIoApic *s = (ApicIoApic *)p;

            GlobalRenderer->Print("Found I/O APIC:");
            GlobalRenderer->Print(to_hstring(s->ioApicId));
            GlobalRenderer->PutChar(' ');
            GlobalRenderer->Print(to_hstring(s->ioApicAddress));
            GlobalRenderer->PutChar(' ');
            GlobalRenderer->Print(to_hstring(s->globalSystemInterruptBase));
            //g_ioApicAddr = (uint8_t *)(uintptr_t)s->ioApicAddress;
            GlobalRenderer->Next();
        }
        else if (type == APIC_TYPE_INTERRUPT_OVERRIDE)
        {
            ApicInterruptOverride *s = (ApicInterruptOverride *)p;

            GlobalRenderer->Print("Found Interrupt Override:");
            GlobalRenderer->Print(to_hstring(s->bus));
            GlobalRenderer->PutChar(' ');
            GlobalRenderer->Print(to_hstring(s->source));
            GlobalRenderer->PutChar(' ');
            GlobalRenderer->Print(to_hstring(s->interrupt));
            GlobalRenderer->PutChar(' ');
            GlobalRenderer->Print(to_hstring(s->flags));
            GlobalRenderer->Next();
        }
        else
        {
            GlobalRenderer->Print("Unknown APIC structure");
        }

        p += length;
    }
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseDT(AcpiHeader *header)
{
    uint32_t signature = header->signature;

    char sigStr[5];
    _memcpy(sigStr, &signature, 4);
    sigStr[4] = 0;
    for(int i = 0;  i < 5; i ++){
        GlobalRenderer->PutChar(sigStr[i]);
    }
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_hstring((uint32_t)signature));
    GlobalRenderer->Next();

    if (signature == 0x50434146)
    {
        AcpiParseFacp((AcpiFadt *)header);
    }
    else if (signature == 0x43495041)
    {
        AcpiParseApic((AcpiMadt *)header);
    }
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseRsdt(AcpiHeader *rsdt)
{
    uint32_t *p = (uint32_t *)(rsdt + 1);
    uint32_t *end = (uint32_t *)((uint8_t*)rsdt + rsdt->length);

    while (p < end)
    {
        uint32_t address = *p++;
        AcpiParseDT((AcpiHeader *)(uintptr_t)address);
    }
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseXsdt(AcpiHeader *xsdt)
{
    uint64_t *p = (uint64_t *)(xsdt + 1);
    uint64_t *end = (uint64_t *)((uint8_t*)xsdt + xsdt->length);

    while (p < end)
    {
        uint64_t address = *p++;
        AcpiParseDT((AcpiHeader *)(uintptr_t)address);
    }
}

// ------------------------------------------------------------------------------------------------
static bool AcpiParseRsdp(uint8_t *p)
{
    // Parse Root System Description Pointer
    GlobalRenderer->Print("RSDP found");

    GlobalRenderer->Next();

    // Verify checksum
    uint8_t sum = 0;
    for (uint i = 0; i < 20; ++i)
    {
        sum += p[i];
    }

    if (sum)
    {
        GlobalRenderer->Print("Checksum failed");
        return false;
    }

    // Print OEM
    char oem[7];
    _memcpy(oem, p + 9, 6);
    oem[6] = '\0';
    GlobalRenderer->Print("OEM = ");
    for(int i = 0; i < 7; i++){
        GlobalRenderer->PutChar(oem[i]);
    }
    
    GlobalRenderer->PutChar(' ');

    // Check version
    uint8_t revision = p[15];
    if (revision == 0)
    {
        GlobalRenderer->Print("Version 1");

        uint32_t rsdtAddr = *(uint32_t *)(p + 16);
        AcpiParseRsdt((AcpiHeader *)(uintptr_t)rsdtAddr);
    }
    else if (revision == 2)
    {
        GlobalRenderer->Print("Version 2");

        uint32_t rsdtAddr = *(uint32_t *)(p + 16);
        uint64_t xsdtAddr = *(uint64_t *)(p + 24);

        if (xsdtAddr)
        {
            AcpiParseXsdt((AcpiHeader *)(uintptr_t)xsdtAddr);
        }
        else
        {
            AcpiParseRsdt((AcpiHeader *)(uintptr_t)rsdtAddr);
        }
    }
    else
    {
        GlobalRenderer->Print("Unsupported ACPI version");
    }

    return true;
}

// ------------------------------------------------------------------------------------------------
void AcpiInit()
{
    // TODO - Search Extended BIOS Area

    // Search main BIOS area below 1MB
    uint8_t *p = (uint8_t *)0x000e0000;
    uint8_t *end = (uint8_t *)0x000fffff;

    while (p < end)
    {
        uint64_t signature = *(uint64_t *)p;

        if (signature == 0x2052545020445352) // 'RSD PTR '
        {
            if (AcpiParseRsdp(p))
            {
                break;
            }
        }

        p += 16;
    }
}

// ------------------------------------------------------------------------------------------------
uint AcpiRemapIrq(uint irq)
{
    AcpiMadt *madt = s_madt;

    uint8_t *p = (uint8_t *)(madt + 1);
    uint8_t *end = (uint8_t *)madt + madt->header.length;

    while (p < end)
    {
        ApicHeader *header = (ApicHeader *)p;
        uint8_t type = header->type;
        uint8_t length = header->length;

        if (type == APIC_TYPE_INTERRUPT_OVERRIDE)
        {
            ApicInterruptOverride *s = (ApicInterruptOverride *)p;

            if (s->source == irq)
            {
                return s->interrupt;
            }
        }

        p += length;
    }

    return irq;
}