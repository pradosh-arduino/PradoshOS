#include "code.h"

char str1[] = "this";
char Commands1[] = "if", Commands2[] = "for", Commands3[] = "else";
int result;

const char* trueData = "true";
const char* falseData = "false";

bool isTrue;
int CodeMain(){
    result = strcmp2(str1, Commands1);
    GlobalRenderer->Print("difference:");
    if(result == 01){
        GlobalRenderer->Print("true");
    }else if(result == 00){
        GlobalRenderer->Print("false");
    }else{
        GlobalRenderer->Print("Unknown Bool type!");
    }
    GlobalRenderer->Next();

    return 0;
}