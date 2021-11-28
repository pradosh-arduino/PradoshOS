#include "acpi.h"
#include <cstddef>
#include "addons.h"
#include "errorScreen/errScr.h"
#include "interrupts/interrupts.h"
#include "cstr.h"

namespace ACPI{
    void* FindTable(SDTHeader* stdHeader, char* signature){
        int entries = (stdHeader->Length - sizeof(ACPI::SDTHeader)) / 8;
        for(int t = 0; t < entries; t++){
            ACPI::SDTHeader* newSDTHeader = (ACPI::SDTHeader*)*(uint64_t*)((uint64_t)stdHeader + sizeof(ACPI::SDTHeader) + (t * 8));
            for (int i = 0; i < 4; i++){
                if(newSDTHeader->Signature[i] != signature[i]){
                    break;
                }
                if (i == 3) return newSDTHeader;
            }
        }
        return 0;
    }
}   