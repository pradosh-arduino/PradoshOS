/*
#######################################
#                                     #
# Partition  Table                    #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/

#ifndef __PARTITIONTABLE_H
#define __PARTITIONTABLE_H

#include <stdint.h>
#include <stddef.h>
#include <defines.h>
#include "base_defs.h"
#include "gpt.h"
#include "mbr.h"
#include "../../malloc.h"
#include "../../ahci/ahci.h"
using namespace AHCI;
#ifdef __cplusplus
C_LINKAGE {
#endif

class PartitionTableReader{
public:
    PartitionTableReader(Port* port);

    bool GPT();

private:
    Port* port;
    bool gpt = true;    // We will assume this is true because we are booting an uefi os.
};

#ifdef __cplusplus
}
#endif

#endif