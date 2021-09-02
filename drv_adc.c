#include "system.h"
/*
int16 Vtemperatura;
int16 Vnivel;
//int16 Frecuencia;
//int16 DutyCicle;

//float VoltajeTemp;
//float VoltajeNivel;
int time;

int16 drv_adc_read(int channel){

   int16 medicion=0;                     //variable entera que contendra la medicion del convertidor AD
   int1 done = 0;                        //Contendra 1 si el convertidor terminó de convertir
   
   setup_adc_ports(AN0_AN1_AN3); // CANALES ANALOGICOS AN0 AN1 Y AN3
   setup_adc(ADC_CLOCK_INTERNAL); // conversion analogica con el reloj interno
   //setup_adc (adc_clock_internal);     //Usando el oscilador interno 
   //setup_adc_ports (all_analog);       //Todo el puerto analogico como entrada analogica    
   set_adc_channel (channel);          //Establecemos el canal de lectura analogica
   delay_ms(1);                       //a small delay is required after setting the channel
   medicion=read_adc ();               // Hace conversión AD 
   done = adc_done();                  //done = 1 si el convertidor termino de convertir
   while(!done)
   {
      done = adc_done();               //Mientras no acabe de convertir se seguira ciclando
   }
   setup_adc (adc_off);                //detenemos al convertidor
   //medicion = (medicion/1023.0)*5;
   return medicion;    
   
}

void drv_adc_lcd(){

   Vtemperatura = drv_adc_read(0);
   //VoltajeTemp = (Frecuencia/1023.0)*5;
   Vnivel = drv_adc_read(1);
   //VoltajeNivel = (DutyCicle/1023.0)*5;
   lcd_putc("\f");
   printf(lcd_putc,"TEMP : %2.1fv",(Vtemperatura/1023.0)*5);
   //printf(lcd_putc,"Temp:  %4.1f",VoltajeTemp);
   lcd_putc("\n");
   printf(lcd_putc,"NIVEL: %2.1fv",(Vnivel/1023.0)*5);
   //printf(lcd_putc,"Nivel: %4.1f",VoltajeNivel);
   delay_ms(250);
}

void drv_adc_modo(){


   if(time==6){ // Cada 2 interrupciones muestra los pulsos del motor
             // es decir cada 1 seg. cada desbordamiento tarda 500ms
             // De Acuerdo a la Ecuacion:
             // T = 4/Fosc*Preescaler(65536 - x)
             // T = 1u*8(65536 - 3036)             
   if(Status_modo!=SIN_MODO){drv_adc_lcd();}
  }
  // Para la primera interrupcion w = 0 y se hace contar el timer 1 nuevamente
  // 500ms cargando el valor 3036
   set_timer1(3036); 
     
   time++; // se incrementa w luego de la interrupcion, sus valores seran 0 0 1
   if(time>6){time=0;}
   
}
*/
