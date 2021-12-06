#include "GUI.h"
#include <cstring>
#include "userinput/mouse.h"
#include <string.h>
#include "scheduling/pit/pit.h"

/*
void TextBox(int CordY, int height, int CordX, int width, uint32_t colour){
  int priH = CordY + height;
  int priW = CordX + width;
  for(int i = CordY; i < priH; i++){
    GlobalRenderer->PutPix(priW, i, colour);
  }
  for(int l = CordX; l < priW; l++){
    GlobalRenderer->PutPix(l, priH, colour);
  }
  GlobalRenderer->SetCursor = {CordX}
}
*/

void setRect(uint32_t xPos, uint32_t yPos, uint32_t xLength, uint32_t yLength, uint32_t colour, int delay, const char* text){
  int LocalxL = xPos + xLength;
  int LocalyL = yPos + yLength;
  int str = strlen(text) / 2;
  for(int x = xPos; x < LocalxL; x++){
    for(int y = yPos; y < LocalyL; y++){
      GlobalRenderer->PutPix(x, y, colour);
      PIT::Sleepd(delay);
    }
  }
  Point OldPos = GlobalRenderer->CursorPosition;
  //int l = LocalxL / 2;
  //int k = LocalyL / 2;
  //int i = l - strlen(text) / 2;
  GlobalRenderer->CursorPosition.Y = LocalyL - (yLength / 2);
  GlobalRenderer->CursorPosition.X = LocalxL - (xLength - str / 2) + 16 * 8;
  GlobalRenderer->Colour = 0x00292929;
  GlobalRenderer->Print(text);
  GlobalRenderer->Colour = 0x00ffffff;
  GlobalRenderer->CursorPosition = OldPos;
}

void TextBox(uint32_t xPos, uint32_t yPos, uint32_t xLength, uint32_t yLength, uint32_t colour, int delay, const char* text){
  int LocalxL = xPos + xLength;
  int LocalyL = yPos + yLength;
  int str = strlen(text) / 2;
  for(int x = xPos; x < LocalxL; x++){
    for(int y = yPos; y < LocalyL; y++){
      GlobalRenderer->PutPix(x, y, colour);
      PIT::Sleepd(delay);
    }
  }
  Point OldPos = GlobalRenderer->CursorPosition;
  //int l = LocalxL / 2;
  //int k = LocalyL / 2;
  //int i = l - strlen(text) / 2;
  GlobalRenderer->CursorPosition.Y = LocalyL - (yLength / 2);
  GlobalRenderer->CursorPosition.X = LocalxL - (xLength - str / 2) + 16 * 8;
  GlobalRenderer->Colour = 0x00292929;
  GlobalRenderer->Print(text);
  GlobalRenderer->Colour = 0x00ffffff;
  GlobalRenderer->CursorPosition = OldPos;
}


void printFill(const char* str){
    int charLen = strlen(str);
    int LocalCharLength = charLen * 8;
    setRect(GlobalRenderer->CursorPosition.X, GlobalRenderer->CursorPosition.Y, LocalCharLength, 16, 0x00ffffff, 0, "");
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