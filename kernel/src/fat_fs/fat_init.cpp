#include "fat_init.h"

#include "../paging/PageFrameAllocator.h"
#include "../ahci/ahci.h"
#include "partitionTable/mbr.h"
#include "partitionTable/gpt.h"
#include "filesystems/fs.h"
#include "filesystems/fat.h"

using namespace AHCI;

void fs_init(AHCIDriver* ahci_driver) {

    Port* FS_PRT;
    // Getting the port to read something from the disk
    AHCIDriver* sataPort;

    bool useGPT = false; // Assume we are on gpt right now

    GPT_PartTableHeader PartitionTableHeader;
    sataPort->FS_PORT->Read(GPT_EFI_PART_HEADER_SECTOR, 1, &PartitionTableHeader);

    for (uint8_t gptSignatureIndex = 0; gptSignatureIndex < 8; gptSignatureIndex++) {
        if (PartitionTableHeader.Signature[gptSignatureIndex] != GPT_EFI_SIGNATURE[gptSignatureIndex]) {
            useGPT = false; break;
        }
    }

    // Warning: This partition is currently going to be the last existing fat partition on the drive
    Partition FAT_Partition;
    _memset(&FAT_Partition, 0, sizeof(Partition));

    int16_t gpt_partition_size_difference = 0;
    if (useGPT) {
        GPT_START* partTable = (GPT_START*)GlobalAllocator.RequestPage();
        _memset(partTable, 0, 0x1000);

        sataPort->FS_PORT->Read(GPT_EFI_PMBR_SECTOR, sizeof ( MBR ), &partTable->PMBR);

        if (partTable->PMBR.Partitions[0].SectorCount == 0 ||
            partTable->PMBR.ValidationSignature != MBR_VALID_MBR) return; // Invalid mbr in the gpt
        
        partTable->PartitionTableHeader = PartitionTableHeader;

        bool breakLoop = false;
        for (uint64_t index = 0; !breakLoop; index++) {
            if (partTable->PartitionTableHeader.PartitionEntrySize < 512) {
                /// COMPLICATED STUFF : START!
                uint8_t entryCount = 512 / partTable->PartitionTableHeader.PartitionEntrySize;
                int16_t entry_size_difference = partTable->PartitionTableHeader.PartitionEntrySize - sizeof(GPT_PartitionEntry);
                gpt_partition_size_difference = entry_size_difference;
                GPT_PartitionEntry CurrentEntries[entryCount];

                sataPort->FS_PORT->Read(partTable->PartitionTableHeader.StartLBA_GUID_Entries + index, 1, &CurrentEntries[0]);

                const uint8_t* rawData = (const uint8_t*)&CurrentEntries[0];
                for (uint64_t partIndex = 0; partIndex < 512; partIndex += (entry_size_difference + sizeof(GPT_PartitionEntry)) ) {
                    const GPT_PartitionEntry* CurrentEntr = (const GPT_PartitionEntry*)&rawData[partIndex];
                    if (CurrentEntr->StartLBA == 0) { breakLoop = true; break; }

                    __memcpy((void*)CurrentEntr->PartitionName, (void*)FAT_Partition.Name, 72);
                    __memcpy((void*)CurrentEntr->UniqueGUID, (void*)FAT_Partition.ID, 16);
                    FAT_Partition.SetEndSector(CurrentEntr->EndLBA);
                    FAT_Partition.SetAttributes(CurrentEntr->Attributes);
                    FAT_Partition.SetStartSector(CurrentEntr->StartLBA);
                }
                break;

                /// COMPLICATED STUFF : END!
            } else {
                GPT_PartitionEntry CurrentPartitionEntry;
                sataPort->FS_PORT->Read(partTable->PartitionTableHeader.StartLBA_GUID_Entries + index,
                                (partTable->PartitionTableHeader.PartitionEntrySize/512) <= 0 ? 1 : partTable->PartitionTableHeader.PartitionEntrySize/512,
                                &CurrentPartitionEntry);
                __memcpy(CurrentPartitionEntry.PartitionName, (void*)FAT_Partition.Name, 72);
                __memcpy(CurrentPartitionEntry.UniqueGUID, (void*)FAT_Partition.ID, 16);
                FAT_Partition.SetEndSector(CurrentPartitionEntry.EndLBA);
                FAT_Partition.SetAttributes(CurrentPartitionEntry.Attributes);
                FAT_Partition.SetStartSector(CurrentPartitionEntry.StartLBA);
            }
        }
    } else {
        MBR* partTable = (MBR*)GlobalAllocator.RequestPage();
        _memset(partTable, 0, 0x1000);

        sataPort->FS_PORT->Read(0, sizeof(MBR) / 512, partTable);

        if (partTable->ValidationSignature != MBR_VALID_MBR); // GlobalRenderer->Println something like "Warning: not a valid mbr!"

        for (int i = 0; i < 4; i++) {
            if (partTable->Partitions[i].EndSector == 0) continue;

            FAT_Partition.SetStartSector( *(uint64_t*)&partTable->Partitions[i].LBA_Start );
            FAT_Partition.SetEndSector( partTable->Partitions[i].EndSector );
            FAT_Partition.SetAttributes( partTable->Partitions[i].Attributes );
            FAT_Partition.SetID( &partTable->Partitions[i].SystemID );
        }
    }

    /* 
     * #################################
     * #                               #
     * # FAT FILESYSTEM INITIALIZATION #
     * #                               #
     * #################################
     */

    Fat* fatFsReader;
    //fatFsReader = fatFsReader.FatH(sataPort, FAT_Partition.StartSector, useGPT);  
    
    MBR_Partition* partEntry = new MBR_Partition();
    partEntry->Attributes = FAT_Partition.Attributes;
    partEntry->LBA_Start = FAT_Partition.StartSector;
    partEntry->SectorCount = FAT_Partition.EndSector - FAT_Partition.StartSector;
    partEntry->SystemID = FAT_Partition.ID[0];
    fatFsReader->MBR_PartitionPtr = partEntry;
    
    fatFsReader->Init();
    File* file = fatFsReader->GetFile("/startup.nsh");
    GlobalRenderer->Println( "This is the contents of the file '/startup.nsh':'" );
    GlobalRenderer->Print( file->GetContents() );
    GlobalRenderer->Println( "'This the filename: '" );
    GlobalRenderer->Print( file->Name );
    GlobalRenderer->Print( "'");
    if (file->Extension != (char*)0xbad) {
        GlobalRenderer->Println(" and this the extension: '");
        GlobalRenderer->Print( file->Extension );
        GlobalRenderer->Print( "'" );
    }
}

void* __memcpy (void *dest, const void *src, size_t len)
{
  char *d = (char*)dest;
  const char *s = (const char*)src;
  while (len--)
    *d++ = *s++;
  return dest;
}

void* _memset (void *dest, int val, size_t len)
{
  unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;
  return dest;
}