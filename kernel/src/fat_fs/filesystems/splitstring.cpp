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

#include "splitstring.h"
#include "../../malloc.h"

char** SplitString::begin() {
    return &this->Data[0];
}

char** SplitString::end() {
    return &this->Data[this->Count];
}

SplitString strsplit( const char* str, char split) {
    uint64_t numReses = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == split && i != 0) {
            numReses++;
        }
    }
    char* res[numReses];
    int resIndex = 0;
    SplitString result = {};

    for (int i = 0; str[i]; i++) {
        if (str[i] == split) { continue; }
        char* currentChar = (char*)&str[i];
        size_t strsize = 0;
        for (int j = 0; currentChar[j]; j++) {
            if (currentChar[j] == split || !currentChar[j]) { break; }
            strsize++;
        }
        char tmpres[strsize+1];
        for (int j = 0; currentChar[j]; j++) {
            if (currentChar[j] == split || !currentChar[j] ) { tmpres[j] = 0; break; }
            tmpres[j] = currentChar[j];
            i++;
        }
        tmpres[strsize] = 0;
        res[resIndex] = (char*)_malloc(strsize+1);
        for (int j = 0; j < strsize+1; j++) {
            res[resIndex][j] = tmpres[j];
        }
        resIndex++;
    }

    result.Count = numReses+1;
    result.Data = res;

    return result;
}