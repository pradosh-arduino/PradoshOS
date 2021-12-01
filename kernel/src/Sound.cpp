#include "Sound.h"
 static void play_sound(uint32_t nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
 //make it shutup
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
 }
 
 //Make a beep
 void beep() {
 	 play_sound(1000);
 	 PIT::Sleepd(10);
	 nosound();
 }
 void beepError(){
     play_sound(100);
 	 PIT::Sleepd(10);
 	 nosound();
 }

 void PlayStartupSound(){
	 play_sound(1000);
 	 PIT::Sleepd(10);
	 nosound();
	 PIT::Sleepd(5);
	 play_sound(1000);
 	 PIT::Sleepd(5);
	 nosound();
	 PIT::Sleepd(5);
	 play_sound(1000);
 	 PIT::Sleepd(5);
 	 nosound();
 }
 void PlayShutdownSound(){
	 play_sound(1000);
 	 PIT::Sleepd(5);
	 nosound();
	 PIT::Sleepd(5);
	 play_sound(1000);
 	 PIT::Sleepd(5);
	 nosound();
	 PIT::Sleepd(5);
	 play_sound(1000);
 	 PIT::Sleepd(10);
 	 nosound();
 }
 void testSong(){
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(8000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(8000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
	 play_sound(4000);
 	 PIT::Sleepd(3);
	 nosound();
 }

 