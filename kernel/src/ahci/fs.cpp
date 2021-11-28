/*
#include "fs.h"

unsigned int first_fat_sector = fat_boot->reserved_sector_count;
unsigned char FAT_table[sector_size];
unsigned int fat_offset = active_cluster * 4;
unsigned int fat_sector = first_fat_sector + (fat_offset / sector_size);
unsigned int ent_offset = fat_offset % sector_size;

unsigned int table_value = *(unsigned int*)&FAT_table[ent_offset] & 0x0FFFFFFF;

unsigned int total_sectorsVBR = (fat_boot->total_sectors_16 == 0)? fat_boot->total_sectors_32 : fat_boot->total_sectors_16;
unsigned int fat_size = (fat_boot->table_size_16 == 0)? fat_boot_ext_32->table_size_16 : fat_boot->table_size_16;
unsigned int root_dir_sectors = ((fat_boot->root_entry_count * 32) + (fat_boot->bytes_per_sector - 1)) / fat_boot->bytes_per_sector;
unsigned int data_sectors = fat_boot->total_sectors - (fat_boot->reserved_sector_count + (fat_boot->table_count * fat_size) + root_dir_sectors);
unsigned int total_clusters = data_sectors / fat_boot->sectors_per_cluster;

void InitFS(){

}

void* ReadSector(bool VBRmode){
    return (void*)total_sectorsVBR;
}

void* TotalDiskSize(){
    return (void*)fat_size;    
}

void UsedDiskSize(){
    return (void*)data_sectors;
}

const char* FSRead(){
    if(total_clusters < 4085){
        return "FAT12";
    }else if(total_clusters < 65525){
        return "FAT16";
    }else if (total_clusters < 268435445){
        return "FAT32";
    }else{
        return "exFAT";
    }
}
*/