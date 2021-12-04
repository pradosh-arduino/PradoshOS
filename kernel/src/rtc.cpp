#include "rtc.h"
#include "IO.h"
#include "BasicRenderer.h"
#include "cstr.h"
#include "scheduling/pit/pit.h"
#include "addons.h"

long long TimeAtBoot = 0;

int readPit(void) {
	unsigned count = 0;
	asm("cli");
	outb(0x43,0b0000000);
	count = inb(0x40);		
	count |= inb(0x40)<<8;		
	return count;
}
void setPit(unsigned count) {
	asm("cli");
	outb(0x40,count&0xFF);		// Low byte
	outb(0x40,(count&0xFF00)>>8);	// High byte
	return;
}
void sleep(int ms){
 for(int i = 0;i<ms/10;i++){
     for(int j  = 0;j<readPit();j++){setPit(899);}
 }
}
int getSeconds(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outb(cmos_address, 0x0);
    int second = inb(cmos_data);
    second = (second & 0x0F) + ((second / 16) * 10);
    return second;
}
int getMinutes(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outb(cmos_address, 0x02);
    int minute = inb(cmos_data);
    minute = (minute & 0x0F) + ((minute / 16) * 10);
    return minute;
}
int getHours(){
    int cmos_address = 0x70;
    int cmos_data    = 0x71;
    outb(cmos_address, 0x04);
    int  hour = inb(cmos_data);
    hour = (hour & 0x0F) + ((hour / 16) * 10);
    return hour;
}
bool time_init(){
 TimeAtBoot = (getSeconds()+(getMinutes()*60)+(getHours()*3600));
 return true;
}
long long currentTime(){
     return (getSeconds()+(getMinutes()*60)+(getHours()*3600));
} 
long long getTimeFromBoot(){
    return (getSeconds()+(getMinutes()*60)+(getHours()*3600))-TimeAtBoot;
}

void PutTime(){
    //int length = strlen((char*)to_string((long int)getHours()));
    //int lenght2 = strlen((char*)to_string((long int)getMinutes()));
    //Point LastCurPos = GlobalRenderer->CursorPosition;
    //Point CurPosTime = {ScreenWidth2 - (length + lenght2), 0};
    //GlobalRenderer->CursorPosition = CurPosTime;
    //GlobalRenderer->Print(to_string((long int)getHours()));
    //GlobalRenderer->PutChar(':');
    //GlobalRenderer->Print(to_string((long int)getMinutes()));
    //PIT::Sleepd(1);
    //GlobalRenderer->CursorPosition = LastCurPos;
    //PutTime();
}