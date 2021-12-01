/*
#######################################
#                                     #
# MBR Partition                       #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/
#ifndef __MBR_H
#define __MBR_H
#include <stdint.h>
#include <stddef.h>
#include "base_defs.h"

#define MBR_PART_BOOTABLE   0x80
#define MBR_VALID_MBR       0xaa55

#if defined( __cplusplus )

#endif

struct MBR_Partition{
    uint8_t              Attributes;

    uint8_t              StartHead;
    uint8_t              StartSector : 6;
    uint16_t             StartCylinder : 10;

    uint8_t              SystemID;

    uint8_t              EndHead;
    uint8_t              EndSector : 6;
    uint16_t             EndCylinder : 10;

    uint32_t             LBA_Start;
    uint32_t             SectorCount;
} __attribute__((packed)) ;

//uint8_t              Bootloader[0x1b8];
struct MBR{
    uint8_t              Bootloader[440];
    uint32_t             UniqueDiskID;
    uint16_t             Reserved0;
    MBR_Partition   Partitions[4];
    uint16_t             ValidationSignature;
} __attribute__((packed)) ;


#if defined( __cplusplus )

#endif

#endif