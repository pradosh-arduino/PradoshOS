#pragma once

#include "../paging/PageFrameAllocator.h"
#include "../ahci/ahci.h"
#include "partitionTable/mbr.h"
#include "partitionTable/gpt.h"
#include "filesystems/fs.h"
#include "filesystems/fat.h"

using namespace AHCI;

void fs_init(AHCIDriver* ahci_driver);
void* __memcpy (void *dest, const void *src, size_t len);
void* _memset (void *dest, int val, size_t len);