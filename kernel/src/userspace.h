#pragma once

#include "BasicRenderer.h"
#include "scheduling/pit/pit.h"
#include "userPanic.h"
#include "IO.h"
#include "Sound.h"

void StartUserspace();
void StopUserspace();
void LoadKernelUserspace();
void ErrorUserspace();
void LoopUserspace();