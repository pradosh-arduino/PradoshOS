#include "GUI.h"
#include <cstring>
#include "userinput/mouse.h"
#include <string.h>
#include "scheduling/pit/pit.h"
#undef strcmp
#ifndef STRCMP
# define STRCMP strcmp
#endif

int xpos;
void PrtWelcome(){
    for(int t = 650; t < 1300; t++){
      GlobalRenderer->PutPix(t, 360, 0x00ffffff);
      GlobalRenderer->PutPix(t, 364, 0x00ffffff);
    }
    for(int t = 650; t < 1300; t++){
      GlobalRenderer->PutPix(t, 550, 0x00ffffff);
      GlobalRenderer->PutPix(t, 554, 0x00ffffff);
    }
    for(int t = 360; t < 550; t++){
      GlobalRenderer->PutPix(650, t, 0x00ffffff);
      GlobalRenderer->PutPix(654, t, 0x00ffffff);
    }
    for(int t = 360; t < 550; t++){
      GlobalRenderer->PutPix(1300, t, 0x00ffffff);
      GlobalRenderer->PutPix(1296, t, 0x00ffffff);
    }
}
void PutGUIbox(int TopLineStart, int TopLineEnd, int LeftLineStart, int LeftLineEnd, int RightLineStart, int RightLineEnd, int BottomLineStart, int BottomLineEnd, bool OKbutton, bool Cancelbutton, const char* msg){
    for(int t = TopLineStart; t < TopLineEnd; t++){
      GlobalRenderer->PutPix(t, 360, 0xffffffff);
      GlobalRenderer->PutPix(t, 364, 0xffffffff);
    }
    for(int t = BottomLineStart; t < BottomLineEnd; t++){
      GlobalRenderer->PutPix(t, 550, 0xffffffff);
      GlobalRenderer->PutPix(t, 554, 0xffffffff);
    }
    for(int t = LeftLineStart; t < LeftLineEnd; t++){
      GlobalRenderer->PutPix(650, t, 0xffffffff);
      GlobalRenderer->PutPix(654, t, 0xffffffff);
    }
    for(int t = RightLineStart; t < RightLineEnd; t++){
      GlobalRenderer->PutPix(1300, t, 0xffffffff);
      GlobalRenderer->PutPix(1296, t, 0xffffffff);
    }
}
void PrintButton(const char* buttonText){
  GlobalRenderer->Next();
  GlobalRenderer->Print("-------------");
  GlobalRenderer->Next();
  GlobalRenderer->Print("| ");
  GlobalRenderer->Print(buttonText);
  GlobalRenderer->Print(" |");
  GlobalRenderer->Next();
  GlobalRenderer->Print("-------------");
}
void setRect(uint32_t xPos, uint32_t yPos, uint32_t xLength, uint32_t yLength, uint32_t colour, int delay){
  int LocalxL = xPos + xLength;
  int LocalyL = yPos + yLength;
  PIT::Sleepd(delay);
    for(int x = xPos; x < LocalxL; x++){
        for(int y = yPos; y < LocalyL; y++){
            GlobalRenderer->PutPix(x, y, colour);
        }
    }
}
void setBlock(uint32_t x, uint32_t y, uint32_t L, uint32_t colour){
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            GlobalRenderer->PutPix(x + i, y + j, colour);
        }
    }
}
void printFill(const char* str){
    int charLen = strlen(str);
    int LocalCharLength = charLen * 8;
    setRect(GlobalRenderer->CursorPosition.X, GlobalRenderer->CursorPosition.Y, LocalCharLength, 16, 0x00ffffff, 0);
    GlobalRenderer->Colour = 0x00292929;
    GlobalRenderer->Print(str);
    GlobalRenderer->Colour = 0x00ffffff;
}
uint64_t strlen(const char *str){
    const char *t = str;
    while(*(++str) != 0){;}
    return (uint64_t) (str - t);
}

int strcmp2(const char *p1, const char *p2)
{
  const unsigned char *s1 = (const unsigned char *) p1;
  const unsigned char *s2 = (const unsigned char *) p2;
  unsigned char c1, c2;
  do
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0')
        return c1 - c2;
    }
  while (c1 == c2);
  return c1 - c2;
}

int And(int a, int b){
  if(a == b){
    return 0;
  }
  return 1;
}

int Or(int a, int b, int Num){
  if(a == Num){
    return 0;
  }else if(b == Num){
    return 0;
  }
  return 1;
}

int strstr_butSlow(const char  *str1, const char  *str2)
{

    for(uint64_t  i = 0; strlen(str2) <= (strlen (str1) - i ); i++)
    {
        if ( strcmp_but_with_length_parameter( (const char *) (str1 + i), str2, strlen(str2) ) )
        return 1;
    }


    return 0;
}

int strcmp_but_with_length_parameter(const char * str1, const char * str2, uint64_t len){

    for(uint64_t i = 0; *(str1 + i) != 0 && *(str2 + i) !=0; i++)
    {
        if( (i >= len)  ||  ( *(str1 + i) != *(str2 + i) ) )
        return 0;
    }


    return 1;
}