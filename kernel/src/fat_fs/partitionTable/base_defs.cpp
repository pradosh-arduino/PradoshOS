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
#include "base_defs.h"

extern "C" {

Partition::Partition() : Attributes(0),StartSector(0),EndSector(0),Name(),ID() {
}

void Partition::SetStartSector(const uint64_t start) {
    *(uint64_t*)&StartSector = start;
}

void Partition::SetEndSector(const uint64_t end) {
    *(uint64_t*)&EndSector = end;
}

void Partition::SetAttributes(const uint8_t attributes) {
    *(uint8_t*)&Attributes = attributes;
}

void Partition::SetName(const uint8_t* name) {
    *(uint8_t**)&this->Name = (uint8_t*)name;
}

void Partition::SetID(const uint8_t* id) {
    *(uint8_t**)&this->ID = (uint8_t*)id;
}

}