#include "Screen.h"
int Xmin = MousePosition.X -= MousePosition.Y;
int Ymin = MousePosition.Y -= MousePosition.X;
void DrawRect(int startPosY, int startPosX){
    GlobalRenderer->PutChar('a', MousePosition.X, startPosY);
    GlobalRenderer->PutChar('a', startPosX, MousePosition.Y);
    GlobalRenderer->PutChar('a', Xmin, startPosY);
    GlobalRenderer->PutChar('a', startPosX, Ymin);
}