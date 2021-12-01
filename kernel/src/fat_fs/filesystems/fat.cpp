#include "fat.h"
#include "../../BasicRenderer.h"
#include "../../cstr.h"
#include "../../malloc.h"
#include "../../ahci/ahci.h"

#include "fs.h"

AHCI::Port* port;

/*
#######################################
#                                     #
# FAT_ClusterChain                    #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/

FAT_ClusterChain::FAT_ClusterChain() {
    this->clusterCount = 0;
    this->firstCluster = 0;
}

void FAT_ClusterChain::GetChain(AHCI::Port* port, uint32_t first) {
    this->firstCluster = first;
    uint32_t nextCluster = 0;
    this->clusters = (uint32_t*)_malloc(0x10);

    //uint8_t* buffer = (uint8_t*)malloc(512);
    //uint8_t* outputBuffer = buffer;

    do {
        this->clusterCount++;
    } while ( (nextCluster != 0) && !( ( nextCluster & 0x0FFFFFFF ) >= 0x0FFFFFF8 ) );
}

/*
#######
#     #
# Fat #
#     #
#######
*/
bool dbg;

/*
Fat::Fat(const AHCI::Port* port, const uint32_t PartitionOffset, const bool useGPT) {
    this->PartitionOffset = PartitionOffset;
    this->gpt = useGPT;
}*/

Fat::~Fat() {}

void Fat::Init() {
    port->Read( gpt ? PartitionOffset : PartitionOffset, (sizeof( FAT_BiosParameterBlock ) / 512 < 1) ? 1 : sizeof( FAT_BiosParamBlock ) / 512, &this->FAT_BiosParamBlock );

    if (this->FAT_BiosParamBlock.FAT_Size16 == 0) {
        FAT32_ExtendedBPB* Fat32ExBPB = (FAT32_ExtendedBPB*)this->FAT_BiosParamBlock.ExtendedBPB;
        FAT_Size = Fat32ExBPB->SectorsPerFat;
    } else {
        FAT_Size = this->FAT_BiosParamBlock.FAT_Size16;
    }

    TotalSectors = ( this->FAT_BiosParamBlock.TotalSectors16 == 0 ) ? this->FAT_BiosParamBlock.TotalSectors32 : this->FAT_BiosParamBlock.TotalSectors16;
    RootEntrySectorCount = ( ( this->FAT_BiosParamBlock.RootEntryCount * 32 ) + ( this->FAT_BiosParamBlock.BPS - 1 ) ) / this->FAT_BiosParamBlock.BPS;
    DataStart = this->FAT_BiosParamBlock.ReservedSectors + ( this->FAT_BiosParamBlock.FAT_Count * FAT_Size ) + RootEntrySectorCount + PartitionOffset;
    FatStart = this->FAT_BiosParamBlock.ReservedSectors + PartitionOffset;
    DataSectorCount = TotalSectors - (this->FAT_BiosParamBlock.ReservedSectors + ( this->FAT_BiosParamBlock.FAT_Count * FAT_Size ) + RootEntrySectorCount);
    TotalClusters = DataSectorCount / this->FAT_BiosParamBlock.SectorPerCluster;


    if ( this->FAT_BiosParamBlock.FAT_Size16 == 0 ) {
        // this->FAT_BiosParamBlock.TotalSectors32
        FAT32_ExtendedBPB* Fat32ExBPB = (FAT32_ExtendedBPB*)this->FAT_BiosParamBlock.ExtendedBPB;
        //RootEntryStart = DataStart - this->FAT_BiosParamBlock.SectorPerCluster * ( Fat32ExBPB->RootClusterNum - 2 );
        this->Label = (char*)Fat32ExBPB->VolumeLabel;
        RootEntryStart = Fat32ExBPB->RootClusterNum;
    } else {
        // this->FAT_BiosParamBlock.TotalSectors16
        FAT1x_ExtendedBPB* Fat1xExBPB = (FAT1x_ExtendedBPB*)this->FAT_BiosParamBlock.ExtendedBPB;
        this->Label = (char*)Fat1xExBPB->VolumeLabel;
        RootEntryStart = DataStart - RootEntrySectorCount;
    
    }

    if (TotalClusters < 4085) {
        FAT_Type = FAT_TYPE::FAT_TYPE_FAT12;
    } else if (TotalClusters < 65525) {
        FAT_Type = FAT_TYPE::FAT_TYPE_FAT16;
    } else if (TotalClusters < 268435445) {
        FAT_Type = FAT_TYPE::FAT_TYPE_FAT32;
    } else {
        FAT_Type = FAT_TYPE::FAT_TYPE_ExFAT;
    }

    GlobalRenderer->Print("Volume Label: ");
    if (IsValidLabel(this->Label)) {
        GlobalRenderer->Print("\\ ");
        for (int i = 0; i < 11; i++) {
            GlobalRenderer->PutChar(this->Label[i]);
        }
        GlobalRenderer->Next();
    } else {
        GlobalRenderer->Print("No label.");
    }

    switch ( this->FAT_Type ) {
        #define __FAT_TYPE(x) case x: GlobalRenderer->Print(#x); break;
        FOREACH_FAT_TYPE
        #undef __FAT_TYPE
    }

    GlobalRenderer->Print(   "Total Clusters:      " );
    GlobalRenderer->Print(to_hstring( TotalClusters ) );

    GlobalRenderer->Print( "FAT_Size         :   0x" );
    GlobalRenderer->Print( to_hstring( FAT_Size ) );
    GlobalRenderer->Print( "DataStart        :   0x" );
    GlobalRenderer->Print( to_hstring( DataStart ) );
    GlobalRenderer->Print( "Total Sectors    :   0x" );
    GlobalRenderer->Print( to_hstring( TotalSectors ) );
    GlobalRenderer->Print( "Partition offset :   0x" );
    GlobalRenderer->Print( to_hstring( PartitionOffset ) );
    GlobalRenderer->Print( "Data Sector Count:   0x" );
    GlobalRenderer->Print( to_hstring( DataSectorCount ) );

    GlobalRenderer->Print( "Root Entry at        0x" );
    GlobalRenderer->Print( to_hstring( (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32) ? ClusterToSector(RootEntryStart) : RootEntryStart ) );

    this->RootEntry = {};

    port->Read( (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32) ? ClusterToSector(RootEntryStart) : RootEntryStart, sizeof(FAT_DirectoryEntry) < 512 ? 1 : sizeof(FAT_DirectoryEntry)/512, &this->RootEntry );

    GlobalRenderer->Print(   "RootEntryType:       " );
    char* rootEntryType = (char*)this->RootEntry.Attributes;

    switch (this->RootEntry.Attributes) {
        case FAT_DirectoryEntryAttributes::DIRATTR_ARCHIVE:
            rootEntryType = "Archive";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_DIRECTORY:
            rootEntryType = "Directory";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_HIDDEN:
            rootEntryType = "Hidden";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_LONG_FILE_NAME:
            rootEntryType = "Long File Name";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_READ_ONLY:
            rootEntryType = "Read Only";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_SYSTEM:
            rootEntryType = "System";
            break;
        case FAT_DirectoryEntryAttributes::DIRATTR_VOLUME_ID:
            rootEntryType = "Volume ID";
            break;
    }
    GlobalRenderer->Print( rootEntryType );

    GlobalRenderer->Print("Directory name: \"");
    for (int i = 0; i < 8; i++) {
        GlobalRenderer->PutChar(this->RootEntry.Name[i]);
    }

    if (this->RootEntry.Extension[0] != 0) {
        GlobalRenderer->PutChar('.');
        for (int i = 0; i < 3; i++) {
            GlobalRenderer->PutChar(this->RootEntry.Extension[i]);
        }
    }

    GlobalRenderer->Next();

    return;
}

File* GetFile(const char* path) {
    File* file = new File(path, NULL);
    char* ReadContents = "This is not read (yet) !\0";
    uint32_t Size = 0;

    Fat* fat;

    Fat::FatSearchResult dirEntryAtPath = fat->Traverse(path);
    Size = dirEntryAtPath.Result->FileSize;
    file->SetSectorOnDisk(dirEntryAtPath.ResultSector);

    file->SetContents(ReadContents);

    SplitString splitPath = strsplit((char*)path, '/');
    SplitString splitFileName = strsplit(splitPath.Data[0], '.');
    file->Name = splitFileName.Data[0];
    file->Extension = splitFileName.Count > 1 ? splitFileName.Data[1] : (char*)0xbad;

    file->Size = Size;

    return file;
}

Fat::FatSearchResult Fat::Traverse(const char* path) {
    GlobalRenderer->Print("RootEntryStart: 0x");
    GlobalRenderer->Print(to_hstring( RootEntryStart ) );

    FAT_DirectoryEntry Entry = {};
    port->Read( (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32) ? DataStart - RootEntrySectorCount + PartitionOffset : ClusterToSector(DataStart - RootEntrySectorCount), sizeof(FAT_DirectoryEntry) < 512 ? 1 : sizeof(FAT_DirectoryEntry)/512, &Entry); // This function read 512 bytes at once so we have to divide it by 512
    //assert(Entry.Name[0] != 0);
    GlobalRenderer->Print((char*)Entry.Name);
    asm("hlt"); //if os brokes make it a infinit loop

    if (*path == '/' && strlen(path) < 2) {
        return FatSearchResult{&this->RootEntry, this->RootEntryStart};
    }
    FatSearchResult result = FatSearchResult{NULL, 0};
    uint32_t currentCluster = this->RootEntryStart;
    SplitString splitPath = strsplit(path,'/');
    uint32_t index = 0;
    for (char* partialPath : splitPath) {
        FAT_DirectoryEntry CurrentEntry = {};
        bool foundEntry = false;

        dbg << (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32);
        GlobalRenderer->Print( to_hstring(this->RootEntryStart) );
        GlobalRenderer->Print( to_hstring(currentCluster) );
        GlobalRenderer->Print( to_hstring(ClusterToSector(currentCluster)) );

        port->Read( (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32) ? currentCluster : ClusterToSector(currentCluster), sizeof(FAT_DirectoryEntry) < 512 ? 1 : sizeof(FAT_DirectoryEntry)/512, &CurrentEntry); // This function read 512 bytes at once so we have to divide it by 512

        if (CurrentEntry.Name[0] == 0) {
            //TODO: Set ERRNO to FAT_NOT_FOUND
            break;
        }

        if (CurrentEntry.Attributes == FAT_DirectoryEntryAttributes::DIRATTR_LONG_FILE_NAME) {
            //TODO: Add lfn (long file name) support!
            continue;
        }

        uint8_t partialPathSplitDotCount = 0;
        SplitString partialPathSplit = strsplit((const char*)partialPath, '.');
        if (partialPathSplit.Count > 2) {
            //TODO: Handle multiple dots in a folder or file name
            
            partialPathSplitDotCount = partialPathSplit.Count;
        } else if (partialPathSplit.Count < 2) {
            partialPathSplitDotCount = partialPathSplit.Count;
        }
        char pathPartFirst8[8];
        _memcpy(&CurrentEntry.Name[0], pathPartFirst8, 8);
        if (pathPartFirst8 == partialPath) {
            if (partialPathSplitDotCount > 2) { /* We can't handle this (yet) ! */ }
            else {
                if (CurrentEntry.Extension[0] != 0) {   // it has a extension, which can be for a file or a random extension for a folder
                    char pathPartEnd3[3];
                    char pathSplitEnd3[3];
                    _memcpy(&CurrentEntry.Extension[0], pathPartEnd3, 3);
                    _memcpy( partialPathSplit.Data[1] ,pathSplitEnd3 , 3 );
                    if (pathPartEnd3 == partialPathSplit.Data[1]) {
                        foundEntry = true;
                    }
                }
            }
            foundEntry = true;
        }

        if (foundEntry) {
            if (CurrentEntry.Attributes != FAT_DirectoryEntryAttributes::DIRATTR_DIRECTORY)
            result.ResultSector = currentCluster;
            return result;
        }
        index++;
        currentCluster++;
    }

    return result;
}

FAT_DirectoryEntry* Fat::ReadDirectory(uint32_t cluster) {
    FAT_DirectoryEntry* result = NULL;
    //TODO: implement
    return result;
}

FAT_DirectoryEntry* Fat::ReadFile(uint32_t cluster) {
    FAT_DirectoryEntry result;
    port->Read( (this->FAT_Type == FAT_TYPE::FAT_TYPE_FAT32) ? this->ClusterToSector(cluster) : cluster, sizeof(FAT_DirectoryEntry) < 512 ? 1 : sizeof(FAT_DirectoryEntry)/512, &result );
    
    uint32_t firstCluster = cluster+1;
        
    int32_t SIZE = result.FileSize;
    int32_t nextFileCluster = firstCluster;
    uint8_t buffer[513];
    uint8_t fatbuffer[513];

    while (SIZE > 0) {
        uint32_t fileSector =  + this->FAT_BiosParamBlock.SectorPerCluster * (nextFileCluster - 2);
        int sectorOffset=0;

        for (; SIZE > 0; SIZE -= 512) {
            port->Read(fileSector+sectorOffset, 1, buffer);
            sectorOffset++;

            buffer[SIZE > 512 ? 512 : SIZE] = '\0';

            if (++sectorOffset > this->FAT_BiosParamBlock.SectorPerCluster-1) {
                break;
            }
        }

        uint32_t fatSectorForCurrentCluster = nextFileCluster / (512/sizeof(uint32_t));
        port->Read(this->FatStart + fatSectorForCurrentCluster, 1, fatbuffer);

        uint32_t fatOffsetInSectorForCurrentCluster = nextFileCluster % (512/sizeof(uint32_t));
        nextFileCluster = ((uint32_t*)&fatbuffer)[fatOffsetInSectorForCurrentCluster] & 0x0FFFFFFF;
    }

    return &result;
}