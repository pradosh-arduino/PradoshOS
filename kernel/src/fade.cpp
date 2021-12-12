#include "fade.h"
#include "BasicRenderer.h"
#include "scheduling/pit/pit.h"

void fade(){
    for(uint16_t i = 0x00000000; i < 0x000000FF; i += 0x01){
        GlobalRenderer->ClearColour = i;
        GlobalRenderer->Clear();
        PIT::Sleepd(0.2);
    }
}