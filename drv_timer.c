#include "system.h"

int16 tim1ticks,systemtime;
//int1 flag_ms,flag_seg,flag_min;


void drv_time(){

tim1ticks++;  

	switch(tim1ticks){

	   case T1_100ms:
		  systemtime = T1_100ms;
		  //set_timer0(0);
		  break;
	   case T1_1S: 
		  systemtime = T1_1S;
		  //set_timer0(0);
		  break;
	   case T1_5S:
		  systemtime = T1_5S;
		  //set_timer0(0);
		  break;
	   case T1_10S:
		  systemtime = T1_10S;
		  //set_timer0(0);
		  break;
	   case T1_20S:
		  systemtime = T1_20S;
		  //set_timer0(0);
		  break;
	   case T1_1M: 
		  systemtime = T1_1M;
		  tim1ticks = 0;
		  //set_timer0(0);
		  break;
		  
	   set_timer1(53036);
	}

}

