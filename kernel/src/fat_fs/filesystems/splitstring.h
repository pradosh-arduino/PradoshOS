/*
#######################################
#                                     #
# Split String                        #
#                                     #
# This Code is from GAMMINGNOOB#3589  #
# HUGE THANKS TO HIM                  #
#                                     #
#######################################
*/
#pragma once

#include <stdint.h>
#include <cstddef>

struct SplitString{
    uint64_t Count;
    char** Data;
    char** begin();
    char** end();
};

SplitString strsplit( const char*, char );
