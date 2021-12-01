/*
#######################################
#                                     #
# Fat FileSystem Driver               #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/
#ifndef __FAT_H
#define __FAT_H
#include <stdint.h>
#include <stddef.h>
#include "../partitionTable/gpt.h"
#include "splitstring.h"
#include "../../ahci/ahci.h"
#include "fs.h"

#define __FAT_TYPE(x) x

#define FOREACH_FAT_TYPE            \
        __FAT_TYPE(FAT_TYPE_FAT12)  \
        __FAT_TYPE(FAT_TYPE_FAT16)  \
        __FAT_TYPE(FAT_TYPE_FAT32)  \
        __FAT_TYPE(FAT_TYPE_ExFAT)  \


#if defined( __cplusplus )

#endif


extern AHCI::Port* port;

enum FAT_DirectoryEntryAttributes{
    DIRATTR_READ_ONLY       =   0x01,
    DIRATTR_HIDDEN          =   0x02,
    DIRATTR_SYSTEM          =   0x04,
    DIRATTR_VOLUME_ID       =   0x08,
    DIRATTR_DIRECTORY       =   0x10,
    DIRATTR_ARCHIVE         =   0x20,
    DIRATTR_LONG_FILE_NAME  =   DIRATTR_READ_ONLY | DIRATTR_HIDDEN | DIRATTR_SYSTEM | DIRATTR_VOLUME_ID
};

enum FAT_TYPE{
    #undef __FAT_TYPE
    #define __FAT_TYPE(x) x,
    FOREACH_FAT_TYPE
    #undef __FAT_TYPE
};

struct FAT_BiosParameterBlock{
    uint8_t          BootJump[3];
    uint8_t          SoftwareName[8];
    uint16_t         BPS;
    uint8_t          SectorPerCluster;
    uint16_t         ReservedSectors;
    uint8_t          FAT_Count;
    uint16_t         RootEntryCount;
    uint16_t         TotalSectors16;
    uint8_t          Type;
    uint16_t         FAT_Size16;
    uint16_t         SectorsPerTrack;
    uint16_t         HeadCount;
    uint32_t         HiddenSectors;
    uint32_t         TotalSectors32;

    uint8_t          ExtendedBPB[54];
} __attribute__((packed)) ;

struct FAT1x_ExtendedBPB{
    uint8_t          DriveNumber;
    uint8_t          Reserved0;
    uint8_t          Signature;      // Must be 0x28 or 0x29
    uint32_t         VolumeID;
    uint8_t          VolumeLabel[11];
    uint8_t          SystemIdentifier[8];
    uint8_t          BootCode[448];
    uint16_t         BootSignature;
} __attribute__((packed));

struct FAT32_ExtendedBPB{
    uint32_t         SectorsPerFat;
    uint16_t         Flags;
    uint16_t         FatVersion;     // High byte is Major version and low byte minor
    uint32_t         RootClusterNum; // Cluster number of the root directory
    uint16_t         FS_InfoSector;
    uint16_t         BackupSector;
    uint8_t          Reserved0[12];
    uint8_t          DriveNumber;
    uint8_t          Reserved1;
    uint8_t          Signature;
    uint32_t         VolumeID;
    uint8_t          VolumeLabel[11];
    uint8_t          SystemIdentifier[8];    // Always "FAT32 ", but never trust it...
    uint8_t          BootCode[420];
    uint16_t         BootSignature;
} __attribute__((packed)) ;

struct FAT32_FS_Info{
    uint32_t         LeadSignature;  // Has to be 0x41615252 for a valid FS_INFO structure
    uint8_t          Reserved0[480];
    uint32_t         MiddleSignature;    // This has to be 0x61417272
    uint32_t         LastFreeCluster;    // If 0xffffffff then it must be calculated. This also might be incorrect so check if it is in the range of total clusters
    uint32_t         ClusterSearchOffset;    // The cluster number where the driver should look for avaliable clusters. if it is 0xFFFFFFFF then we should start to look at index 2.
    uint8_t          Reserved1[12];
    uint32_t         TrailSignature; // Has to be 0xAA550000
} __attribute__((packed)) ;

struct FAT_DirectoryEntry{
    uint8_t          Name[8];
    uint8_t          Extension[3];
    uint8_t          Attributes;     // Enum FAT_DirectoryEntryAttributes has all the avaliable attributes
    uint8_t          Reserved0;
    uint8_t          CreationTimeThenthSec;  // Has to be in range of 0 and 199 inclusive

    uint16_t         CreationTime;           /* Split into fields: Hour first 5 bits, Minutes next 6 bits, Seconds last 5 bits */

    uint16_t         CreationDate;           /* Split into fields like the creation time: First 7 bits = Year, Next 4 bits = Month, Last 5 bits = Day */

    uint16_t         LastAccessedDate;       /* Split into fields (same as creation date): First 7 bits = Year, Next 4 bits = Month, Last 5 bits = Day */

    uint16_t         EntryHighBits;  // For FAT1x this is always zero

    uint16_t         LastModificationTime;   /* Split into fields: Hour first 5 bits, Minutes next 6 bits, Seconds last 5 bits */

    uint16_t         LastModifiedDate;       /* Split into fields (same as creation date): First 7 bits = Year, Next 4 bits = Month, Last 5 bits = Day */

    uint16_t         EntryLowBits;   // Use to find the first cluster of this entry

    uint32_t         FileSize;
} __attribute__((packed));

struct FAT_LongFileNameEntry{
    uint8_t          Order;          // This value helps us to find the place where to insert this into the file's name
    uint16_t         FirstChars[5];  // First 5, 2-byte characters of the name
    uint8_t          Attributes;     // Always 0x0F (FAT_DirectoryEntryAttributes::DIRATTR_LONG_FILE_NAME)
    uint8_t          LongEntryType;  // 0 for name entries
    uint8_t          Checksum;       // Created of the short filename when the file was created
    uint16_t         MidChars[6];    // Next 6, 2-byte characters
    uint16_t         Zero;
    uint16_t         LastChars[2];   // Last 2, 2-byte characters
} __attribute__((packed)) ;

struct FAT_ClusterChain{
    FAT_ClusterChain();
    uint32_t firstCluster;
    uint32_t clusterCount;
    uint32_t* clusters;

    void GetChain(AHCI::Port* port, uint32_t first);
};

class Fat : public FileSystem {
public:
    Fat(const AHCI::Port* port, const uint32_t PartitionOffset, const bool useGPT);
    ~Fat();

    void Init();

    File* GetFile(const char* path);
    FAT_TYPE FAT_Type;
    struct FatSearchResult{
        FAT_DirectoryEntry* Result;
        uint32_t                 ResultSector;
    };
    FatSearchResult Traverse(const char* path);

    FAT_DirectoryEntry* ReadDirectory(uint32_t clusterNumber);
    FAT_DirectoryEntry* ReadFile(uint32_t clusterNumber);
private:

    inline uint32_t ClusterToSector(uint32_t cluster) {
        return ((cluster - 2) * this->FAT_BiosParamBlock.SectorPerCluster) + DataStart;
    }

    inline uint8_t IsValidLabel(char* label) {
        if (label[0] == 'N' && label[1] == 'O' && label[2] == ' ' &&
            label[3] == 'N' && label[4] == 'A' && label[5] == 'M' &&
            label[6] == 'E' && label[7] == ' ' && label[8] == ' ' &&
            label[9] == ' ' && label[10] == ' ' ) {
            return 0;
        }
        return 1;
    }

private:
    uint32_t FatStart;
    uint32_t FAT_Size;
    uint32_t DataStart;
    uint32_t TotalSectors;
    uint32_t TotalClusters;      // With this we can check which fat type we have to assume
    uint32_t RootEntryStart;
    uint32_t PartitionOffset;
    uint32_t DataSectorCount;
    uint32_t RootEntrySectorCount;
    bool gpt;
    FAT_BiosParameterBlock FAT_BiosParamBlock;
    FAT_DirectoryEntry RootEntry;
    char* Label;

public:
    GPT_PartitionEntry* GPT_PartitionPtr = NULL;
    int16_t GPT_PartSizeDifference = 0;
    MBR_Partition* MBR_PartitionPtr = NULL;
};

#if defined( __cplusplus )

#endif

#endif