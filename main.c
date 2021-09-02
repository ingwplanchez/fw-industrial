#include "system.h"

int1 timetm1 = 0;
//int1 timetm2 = 0;

void main_config();

//INTERRUPCIONES

#int_rb
Void Rb4_Rb7_ISR(){

}

/*Interrupcion por RB4-RB7*/
#int_ext
void RB0_ISR(){

}
 
/*Interrupcion por timer1*/

#int_timer1
void timer1_isr(void)
{
   if(timetm1==1){   
      drv_gpio_ticks();
   }       
   timetm1++;     
}

void main(){

   main_config(); // Configuracion inicial

   Flag_btn_inicio = 1;
   Flag_sub_menu0 = 1; 
   Flag_salir = 1;
   Status_modo = SIN_MODO ;
   
   drv_gpio_off();
   output_bit(SOLENOIDE3,0);
   output_bit(RH,0);
   
   while(1){
         
      switch(Status_modo){
         case MODO_LAVADO:
            drv_gpio_lavado();
            
            Status_modo = SIN_MODO;
            break;
            
         case MODO_CENTRIFUGADO:
            drv_gpio_centrifugado();   
            Status_modo = SIN_MODO;
            break;
            
          case MODO_AUTOMATICO:
             drv_gpio_automatico2();
             Status_modo = SIN_MODO;
            break;
            
           case MODO_INICIO:
		   /*
			if(Flag_sub_menu0 == 0){
				drv_gpio_pulsadores();
				delay_ms(100);}
		   */
            break;
            
          default:
            drv_gpio_pulsadores();
            delay_ms(100);
            break;
        }        
    } 
}

void main_config(){

   set_tris_d(0b00000000);
   set_tris_c(0b00000000);
   set_tris_b(0b11110111);
   set_tris_e(0b00000000);  
   
   //enable_interrupts(int_ext);      // Habilito las interrupcio por RB0
   //enable_interrupts(int_rb);       // Habilito innterrupcion RB4 - RB7

   enable_interrupts(int_timer1);   // Habilito la interrupcion por timer1
   //enable_interrupts(int_timer2);   // Habilito la interrupcion por timer1
   enable_interrupts(global);       // Habilitacion Global de interruociones
   
   //ext_int_edge(0,H_TO_L);          // Config. Ext RB0  por flanco de subida
   
   setup_timer_0(rtcc_ext_h_to_l | rtcc_div_2); /* Configuracion del timer 0
                                             como contador para detectar por
                                             flanco de bajada con un 
                                             preescaler de 2 (Cuenta cada
                                             2us)*/
   //setup_timer_1(t1_internal | t1_div_by_8); 
   /* configuracion del timer 1 como           
   Temporizador con un preescalerde 8 (cuenta cada 8us)*/
                                             
   setup_timer_1(t1_internal | t1_div_by_1);  
   
   // Duty minimo = 5(1%), Duty Max = 500(100%)  
   //Preescaler Timer 2 = 4
   //Frecuencia PWM 2000HZ
   setup_ccp1(CCP_PWM); 
   setup_timer_2(T2_DIV_BY_4, 124, 1);
                  // Inicializacion del modulo PWM
   
   set_timer0(0);    //inicializacion del timer 0
   set_pwm1_duty(5);
   
   //output_b(0b00000000);

/*   
   enable_interrupts(int_timer1);   // Habilito la interrupcion por timer1
   enable_interrupts(int_timer2);   // Habilito la interrupcion por timer1
   enable_interrupts(global);       // Habilitacion Global de interruociones
*/   

   output_c(0b00000000);
   output_e(0b00000000);
   output_bit(SOLENOIDE3,0);
   
   delay_ms(100);
   
   lcd_init(); // Inicializacion de pantalla LCD
     
}


