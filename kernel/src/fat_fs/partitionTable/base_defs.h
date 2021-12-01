/*
#######################################
#                                     #
# Base Defs                           #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/

#ifndef __BASE_DEFS_H
#define __BASE_DEFS_H
#include <stdint.h>
#include <stddef.h>

#define PARTITION_ATTRIB_USE_LEGACY     0b0000000000000001  // If this and the partition attributes are true ( this & Partition.Attributes ), then this is a mbr partition
#define PARTITION_ATTRIB_HIDDEN         0b0000000000000010  // This should be pretty self-explanitory
#define PARTITION_ATTRIB_SYSTEM         0b0000000000000100  // This is also self-explanitory
#define PARTITION_ATTRIB_FIRMWARE       0b0000000000001000  // If this and the attrbiutes of the partition are true, then this is something like the efi system partition on a gpt disk
#define PARTITION_ATTRIB_LINUX_FS       0b0000000000010000  // Self-explanitory
#define PARTITION_ATTRIB_LINUX_SWAP     0b0000000000100000  // Self-explanitory
#define PARTITION_ATTRIB_BASIC_DATA     0b0000000001000000  // Self-explanitory
#define PARTITION_ATTRIB_VIPER_FS       0b0100000000000000  // Maybe in the future we will add our own file system and a partition type for it.
#define PARTITION_ATTRIB_MAIN_OS_PART   0b1000000000000000  // If this and the partition attributes are true then that partition is where all the os files are

#if defined(__cplusplus)

#endif

struct Partition{
    Partition();

    ///
    ///
    /// @param start the start sector of the partition
    ///
    ///
    void      SetStartSector(const uint64_t start);
    ///
    ///
    /// @param end the end sector of the partition
    ///
    ///
    void      SetEndSector(const uint64_t end);
    ///
    ///
    /// @param attributes nothing to say
    ///
    ///
    void      SetAttributes(const uint8_t attributes);
    ///
    ///
    /// @param name should be an array of size 72
    ///
    ///
    void      SetName(const uint8_t* name); // name must be an array of size 72
    ///
    ///
    /// @param id should be an array of size 16
    ///
    ///
    void      SetID(const uint8_t* id);

    const uint64_t StartSector;    // Start sector on the disk
    const uint64_t EndSector;      // End sector on the disk
    const uint8_t  Attributes;     // Attributes like if it is a mbr partition or a gpt one
    const uint8_t  Name[72];       // Name of the partition
    const uint8_t  ID[16];         // Partition id (16 for a guid if this is a gpt partition)
} __attribute__((packed)) ;

#if defined(__cplusplus)

#endif

#endif