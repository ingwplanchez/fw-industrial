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

 /*
 switch(tim1ticks){
   case T1_100ms:
      ms++;
      if(ms>10){ms =0;}
      break;
   case T1_1S:
      seg++;
      if(seg>60){seg=0;}
      break; 
   case T1_1M:
      min++;
      
      break;     
 }
 
*/

/*
   switch(tim1ticks){
   
       case T1_100ms:
        flag_ms = 1;
        tim1ticks = 0;
        set_timer1(0);
        break;
       
       case T1_1S:
         flag_seg = 1 ;
         tim1ticks = 0;
         set_timer1(0);
         break;
       
       case T1_1M:
         flag_min = 1;
         tim1ticks = 0;
         set_timer1(0);
         break;
       
   }
   set_timer1(53036);
   tim1ticks++;
   
  */ 
}

//drv_time(2,T1_1S);
