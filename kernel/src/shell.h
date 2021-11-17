#pragma once
#include <stdint.h>
#include "scheduling/pit/pit.h"
#include "BasicRenderer.h"
#include "addons.h"
#include "CPUID.h"
#include "rtc.h"
#include "fs.h"
#include "powerMgmt.h"
#include "COM.h"
#include "cstr.h"
#include "ahci/ahci.h"
#include "registry.h"

class Shell{
    public:
    void Init();
    void HandleCommand(char* command);
};
void ClearCharTimes(int length);
void echo(const char* command);
void ls();
bool equalS(const char* a, const char* b,int till);
void setCursorPosition(int xe,int ye);
extern Shell* GlobalShell;