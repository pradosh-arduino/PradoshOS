#include "keyboard.h"
#include "../GUI.h"
#include "../addons.h"
#include "../scheduling/pit/pit.h"
#include "../shell.h"

    bool isLeftShiftPressed;
    bool isRightShiftPressed;

    bool isF1Pressed;
    bool isCommandInputOn;
    bool isCommandEnter;
    bool EnterActivator;
    bool isEnterPressed = false;
    
    int isF3Pressed = 0;
    
    char string[1000];
    int i = 0;

void HandleKeyboard(uint8_t scancode){
    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);
    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            isF3Pressed = 0;
            return; 
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            isF3Pressed = 0;
            return;
        case RightShift:
            isRightShiftPressed = true;
            isF3Pressed = 0;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            isF3Pressed = 0;
            return;
        case Enter:
            GlobalRenderer->Next();
            isF3Pressed = 0;
            //GlobalShell->HandleCommand(string);

            //// clear string
            //for(int in = 0; in < 1000; in++) {
            //    string[in] = 0;
            //}
            //
            //// reset index
            //i = 0;
            return;
        case Spacebar:
            GlobalRenderer->PutChar(' ');
            isF3Pressed = 0;
            return;
        case BackSpace:
           GlobalRenderer->ClearChar();
           isF3Pressed = 0;
           return;
        case 0x04:
           isF3Pressed++;
           return;

        // remove from string
        string[i - 1] = 0;
        i--;
        return;
    }

    if(ascii != 0){
        GlobalRenderer->PutChar(ascii);
        string[i] = ascii;
        i++;
    }

}