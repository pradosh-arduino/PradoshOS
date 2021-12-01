#pragma once 

#include "BasicRenderer.h"

void PrtWelcome();
void PutGUIbox(int TopLineStart, int TopLineEnd, int LeftLineStart, int LeftLineEnd, int RightLineStart, int RightLineEnd, int BottomLineStart, int BottomLineEnd, bool OKbutton, bool Cancelbutton, const char* msg);
void PrintButton(const char* buttonText);
void draw_rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height, uint8_t r, uint8_t g, uint8_t b);
void setRect(uint32_t xPos, uint32_t yPos, uint32_t xLength, uint32_t yLength, uint32_t colour, int delay, const char* text);
void setBlock(uint32_t x, uint32_t y, uint32_t L, uint32_t colour);
void printFill(const char* str);
int strcmp2(const char *p1, const char *p2);
void TextBox(int CordY, int height, int CordX, int width, uint32_t colour);

int strstr_butSlow(const char *, const  char *);
int strcmp_but_with_length_parameter(const char *, const char *, uint64_t);