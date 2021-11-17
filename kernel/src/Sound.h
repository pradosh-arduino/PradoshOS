#pragma once

#include "scheduling/pit/pit.h"
#include "IO.h"

static void play_sound(uint32_t nFrequence);
static void nosound();
void beep();
void beepError();
void PlayStartupSound();
void PlayShutdownSound();
void testSong();