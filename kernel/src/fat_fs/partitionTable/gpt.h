/*
#######################################
#                                     #
# GPT Partition                       #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/

#ifndef __GPT_H
#define __GPT_H
#include <stdint.h>
#include <stddef.h>
#include "base_defs.h"
#include "mbr.h"

#define GPT_EFI_PMBR_SECTOR             0
#define GPT_EFI_PART_HEADER_SECTOR      1
#define GPT_PARTITION_ENTRIES_SECTOR    2
#define GPT_PART_ATTRIB_FIRMWARE        0b1
#define GPT_PART_ATTRIB_USED_BY_OS      0b10
#define GPT_ENTRIES_SIZE                (512*31)/sizeof(GPT_PartitionEntry)

#if defined(__cplusplus)

#endif

extern uint8_t GPT_EFI_SIGNATURE[];

struct GPT_PartTableHeader{
    uint8_t                  Signature[8];   // MUST BE "EFI PART"
    uint32_t                 Revision;
    uint32_t                 HeaderSize;
    uint32_t                 CRC32_Checksum;
    uint32_t                 Reserved0;
    uint64_t                 ThisHdrLBA;
    uint64_t                 AlternateHdrLBA;
    uint64_t                 FirstUsableGptEntryBlock;
    uint64_t                 LastUsableGptEntryBlock;
    uint8_t                  GUID[16];
    uint64_t                 StartLBA_GUID_Entries;
    uint32_t                 NumEntries;
    uint32_t                 PartitionEntrySize; // In bytes!
    uint32_t                 CRC32_PartitionEntries;
    uint8_t                  Reserved1[512-0x5C];    // Should be zeroed
} __attribute__((packed)) ;

struct GPT_PartitionEntry{
    uint8_t                  PartitionTypeGUID[16];      // 0 == unused entry
    uint8_t                  UniqueGUID[16];
    uint64_t                 StartLBA;
    uint64_t                 EndLBA;
    uint8_t                  Attributes;
    uint8_t                  PartitionName[72];
} __attribute__((packed));

struct GPT_START{
    MBR PMBR;  // Protected MBR
    GPT_PartTableHeader PartitionTableHeader;
} __attribute__((packed)) ;

struct GPT_END{
    GPT_PartTableHeader PartitionTableHeaderMirror; // Has to be same as at the start
} __attribute__((packed));

#if defined(__cplusplus)

#endif

#endif