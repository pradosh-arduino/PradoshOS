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
    
    
    char string[1000];
    int i = 0;

void HandleKeyboard(uint8_t scancode){
    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);
    switch (scancode){
        case LeftShift:
            isLeftShiftPressed = true;
            return; 
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case Enter:
            GlobalRenderer->Next();
            GlobalShell->HandleCommand(string);

            // clear string
            for(int in = 0; in < 1000; in++) {
                string[in] = 0;
            }

            // reset index
            i = 0;
            return;
        case Spacebar:
            GlobalRenderer->PutChar(' ');
            return;
        case BackSpace:
           GlobalRenderer->ClearChar();
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