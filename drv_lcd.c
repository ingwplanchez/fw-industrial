#include "system.h"

//int me = 0;
void drv_lcd_show(){
      printf(lcd_putc,"\f  <<PREPARADO>>\n");
      delay_ms(1500);
      printf(lcd_putc,"\f    LAVADORA\n");
      printf(lcd_putc,"PRESIONA(INICIO)\n"); 
      delay_us(1000);
     
}

void drv_lcd_show1(char * cmd){
      printf(lcd_putc,"\f");
      printf(lcd_putc,(char *)cmd);
      printf(lcd_putc,"\n");

}



