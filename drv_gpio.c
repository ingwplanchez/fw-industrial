#include "system.h"

#define AntiRebote1(PIN)    do{if(input(PIN)==1){break;}}while(1)
#define AntiRebote0(PIN)    do{if(input(PIN)==0){break;}}while(1)

int1 Flag_btn_inicio,Flag_btn_stop,Flag_btn_subir,Flag_btn_bajar,Flag_rb0,Flag_ejecutar,Flag_salir;
int1 Flag_sub_menu0, Flag_sub_menu1,Flag_rotacion,Flag_adc_nivel,Flag_RH,Flag_RM;
int Flag_ciclo;
int Status_modo,Status_temp,Status_nivel;
int Status_Opcion,Status_Opcion1;
int time,segundos,minutos,seg,min,repeticion,seg_solenoide;

int timeticks = 0;
int Status_tiempo = TIEMPO_35MIN;
int Status_tiempo_cent;
//int Status_tiempo = 1;
int Status_agua = NIVEL_MEDIO;
int Status_fase = 0;
int16 contador,Vtemperatura,Vnivel,ADCNivel,ADCrule; 

int T_lavado,T_enjuague,T_centrifugado,T_ciclo;


void drv_gpio_alarmas(){
   
   if (input(ALARMA_VARIADOR1)==0){
      printf(lcd_putc,"\f  <<ALARMA V1>>\n");
      Status_modo = SIN_MODO ;
      drv_gpio_off();
      drv_gpio_clear();
      Status_tiempo = TIEMPO_35MIN;
      Flag_salir =1;
      //Flag_alarma1 =1;      
   }

   if (input(ALARMA_VARIADOR2)==0){
      printf(lcd_putc,"\f  <<ALARMA V2>>\n");
      Status_modo = SIN_MODO ;
      drv_gpio_off();
      drv_gpio_clear();
      Status_tiempo = TIEMPO_35MIN;
      Flag_salir = 1;
      //Flag_alarma2 =1;      
      
   }
   
}

void drv_gpio_int_rb0(){

   if (input(MICRO_SWITCH)==0){ 
      delay_ms(500);  
      printf(lcd_putc,"\f  PULSADOR DE\n");
      printf(lcd_putc," PUERTA ACTIVO\n");
      Status_modo = SIN_MODO ;
      drv_gpio_off();
      drv_gpio_clear();
      Flag_salir =1;
      Flag_rb0 = 1;

   }  
   
   if ((input(MICRO_SWITCH)==1) && (Status_modo == SIN_MODO)&&(Flag_rb0 == 1)){
      printf(lcd_putc,"\f  <<CONTINUAR>>\n");
      printf(lcd_putc,"PRESIONA(INICIO)\n"); 
      Flag_rb0 = 0;
   }  
}

void drv_gpio_int_rb(){

   if (input(BTN_INICIO)==0){

         //AntiRebote1(BTN_INICIO);
         delay_ms(250);       
         if(Flag_btn_inicio == 0){
            Flag_btn_inicio = 1;
            Flag_sub_menu0 = 1; 
            Flag_salir = 1;
            Status_modo = SIN_MODO ;
         }
         
         else{Flag_ejecutar = 1;}  
      }
      
      if (input(BTN_STOP)==0){
        //AntiRebote1(BTN_STOP);
         delay_ms(250);
         printf(lcd_putc,"\f    <<STOP>>\n");drv_gpio_off();
         Flag_salir = 0;
         Flag_btn_stop = 1;         

         drv_gpio_off();
         drv_gpio_clear();
         Flag_salir =1;

         Status_modo = SIN_MODO ;
         drv_gpio_off();

      }
   
      if (input(BTN_SUBIR_MENU)==0){
         //AntiRebote1(BTN_SUBIR_MENU);
         delay_ms(250);  
         Flag_btn_subir = 1;
         drv_gpio_status_subir();
      }
      
      if (input(BTN_BAJAR_MENU)==0){
         //AntiRebote1(BTN_BAJAR_MENU);
         delay_ms(250);  
         Flag_btn_bajar = 1;
         drv_gpio_status_bajar();
      }   
}

void drv_gpio_status_subir(){

   switch(Status_nivel){
   
      case 0:
         if(Flag_sub_menu0 == 1){Status_Opcion--;}
         if(Status_Opcion == -1) Status_Opcion = MAX_OPCION_1; 
         break;
         
      case 1:
         if(Flag_sub_menu1 == 1){Status_Opcion1--;}
         
         if(Status_Opcion == 3 ){
            if(Status_Opcion1 == -1) Status_Opcion1 = MAX_OPCION; 
         }
         else if(Status_Opcion == 4 || Status_Opcion == 5){
            if(Status_Opcion1 == -1) Status_Opcion1 = MAX_OPCION_ ;         
         }
         break;
   
     }  
}

void drv_gpio_status_bajar(){

   switch(Status_nivel){
   
      case 0:
         if(Flag_sub_menu0 == 1){Status_Opcion++;};
         if(Status_Opcion > MAX_OPCION_1) Status_Opcion = 0; 
         break;
         
      case 1:
         if(Flag_sub_menu1 == 1){Status_Opcion1++;};
         
         if(Status_Opcion==3 ){
            if(Status_Opcion1 > MAX_OPCION) Status_Opcion1 = 0; 
         }
         else if(Status_Opcion == 4 || Status_Opcion == 5){
            if(Status_Opcion1 > MAX_OPCION_) Status_Opcion1 = 0; 
         }
         break;
   
    }
}
   

void drv_gpio_lcd_menu(){

  switch(Status_nivel){
   case 0:
      drv_gpio_menu0();
      break;
   case 1:
      drv_gpio_menu1();
      break;
   case 2:
      //drv_gpio_menu2();
      break;
      
  } 
}

void drv_gpio_menu1(){
   
   //   if((Flag_sub_menu1 == 1) && (Flag_rb0) == 0){
   if((Flag_sub_menu1 == 1)){
         
      switch(Status_Opcion){
      case 3:
         drv_gpio_submenu_temp();
         break;
      case 4:
         drv_gpio_submenu_nivel();
         break;
      case 5:
         drv_gpio_submenu_tiempo();
         break;
      }
   }
}

void drv_gpio_menu0(){

   //if((Flag_sub_menu0 == 1) && (Flag_rb0) == 0){ 
   if(Flag_sub_menu0 == 1){
      
      switch(Status_opcion){
      
         case 0:
         
            printf(lcd_putc,"\f");
            printf(lcd_putc,AUTOM_);
            printf(lcd_putc,LAVADO);
            //printf(lcd_putc,LAVADO_);
            //printf(lcd_putc,CENTRIFUGADO);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish0();
               Status_modo = MODO_AUTOMATICO;
              // Status_modo = MODO_LAVADO ;
               
               drv_gpio_mode_time();
               drv_gpio_clear();    
            }
            break;
            
         case 1:   
            printf(lcd_putc,"\f");
            printf(lcd_putc,AUTOM);
            printf(lcd_putc,LAVADO_);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish0();
               Status_modo = MODO_LAVADO ;
               drv_gpio_mode_time();
               drv_gpio_clear();                      
            }
            break;
             
         case 2:      
            printf(lcd_putc,"\f");
            printf(lcd_putc,CENTRIFUGADO_);
            //printf(lcd_putc,AUTOM_);
            printf(lcd_putc,TEMPERATURA);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish0();
               Status_modo = MODO_CENTRIFUGADO;
               //Status_modo = MODO_AUTOMATICO;
               drv_gpio_mode_time();
               drv_gpio_clear();                
            }            
            break;
            
         case 3:     
            printf(lcd_putc,"\f");
            printf(lcd_putc,CENTRIFUGADO);
            //printf(lcd_putc,AUTOM);
            printf(lcd_putc,TEMPERATURA_);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish1();
               drv_gpio_submenu_temp();
            }  
            break;
      
         case 4:
            printf(lcd_putc,"\f");
            printf(lcd_putc,NIVEL_);
            printf(lcd_putc,TIEMPO);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish1();
               drv_gpio_submenu_nivel();
            }         
            break;  
             
         case 5:
            printf(lcd_putc,"\f");
            printf(lcd_putc,NIVEL);
            printf(lcd_putc,TIEMPO_);
            
            if(Flag_ejecutar == 1){
               drv_gpio_finish1();
               drv_gpio_submenu_tiempo();
            }          
            break;           
       }     
   }
}

void drv_gpio_submenu_tiempo(){
   
      switch(Status_opcion1){
      
         case 0:
            printf(lcd_putc,"\f");
            printf(lcd_putc,T_25MIN_);
            printf(lcd_putc,T_35MIN);
            
            if(Flag_ejecutar == 1){
               Status_tiempo = TIEMPO_25MIN;
               Flag_ejecutar = 0;
               drv_gpio_back();
            }
            break;
            
          case 1:
            printf(lcd_putc,"\f");
            printf(lcd_putc,T_25MIN);
            printf(lcd_putc,T_35MIN_);
            
            if(Flag_ejecutar == 1){
               Status_tiempo = TIEMPO_35MIN; 
               Flag_ejecutar = 0;
               drv_gpio_back();      
            }
            break;
            
          case 2:
          
            printf(lcd_putc,"\f");
            printf(lcd_putc,T_45MIN_);
            printf(lcd_putc,T_55MIN);
            
            if(Flag_ejecutar == 1){
               Status_tiempo = TIEMPO_45MIN;
               Flag_ejecutar = 0;
               drv_gpio_back();               
            }     
            break;
            
         case 3:
            printf(lcd_putc,"\f");
            printf(lcd_putc,T_45MIN);
            printf(lcd_putc,T_55MIN_);
            if(Flag_ejecutar == 1){
               Status_tiempo = TIEMPO_55MIN;
               Flag_ejecutar = 0;
               drv_gpio_back();
            }
            break;      
        }
   // }
}

void drv_gpio_submenu_nivel(){

   switch(Status_opcion1){
   
      case 0:
         printf(lcd_putc,"\f");
         printf(lcd_putc,MUY_BAJO_);
         printf(lcd_putc,BAJO);
         if(Flag_ejecutar == 1){
            Status_agua = NIVEL_BAJO_1;
            Flag_ejecutar = 0;
            drv_gpio_back();
         }
         break;
         
      case 1:
      
         printf(lcd_putc,"\f");
         printf(lcd_putc,MUY_BAJO);
         printf(lcd_putc,BAJO_);
         
         if(Flag_ejecutar == 1){
            Status_agua = NIVEL_BAJO_2;
            Flag_ejecutar = 0;
            drv_gpio_back();   
         }
         break;
         
      case 2:
         printf(lcd_putc,"\f");
         printf(lcd_putc,MEDIO_);
         printf(lcd_putc,ALTO );
         if(Flag_ejecutar == 1){
            Status_agua = NIVEL_MEDIO;
            Flag_ejecutar = 0;
            drv_gpio_back(); 
         }
         break;
            
      case 3:
         printf(lcd_putc,"\f");
         printf(lcd_putc,MEDIO);
         printf(lcd_putc,ALTO_);
         if(Flag_ejecutar == 1){
            Status_agua = NIVEL_ALTO;
            Flag_ejecutar = 0;
            drv_gpio_back(); 
         }          
         break;            
     }
}

void drv_gpio_submenu_temp(){

   switch(Status_opcion1){
      case 0:
         printf(lcd_putc,"\f");
         printf(lcd_putc,FRIA_);
         printf(lcd_putc,CALIENTE);
         if(Flag_ejecutar == 1){
            Status_temp = TEMP_FRIA;
            Flag_ejecutar = 0;
            drv_gpio_back();
         }
         break;
         
      case 1:   
         printf(lcd_putc,"\f");
         printf(lcd_putc,FRIA);
         printf(lcd_putc,CALIENTE_);
      
         if(Flag_ejecutar == 1){
            Status_temp = TEMP_CALIENTE ;
            Flag_ejecutar = 0;
            drv_gpio_back();            
         }
         break;
         
      case 2:
         printf(lcd_putc,"\f");
         printf(lcd_putc,TEMP_AMBOS_);

         if(Flag_ejecutar == 1){
            Status_temp = TEMP_TIBIA;
            Flag_ejecutar = 0;
            drv_gpio_back();
         }       
         break;         
    }
}

void drv_gpio_back(){

   switch(Status_nivel){
       
      case 1:
         Status_nivel = 0;
         //Status_Opcion = 0;
         Status_opcion1 = 0;
         Flag_btn_inicio = 1;
         Flag_sub_menu1 = 0;
         Flag_sub_menu0 = 1;
         //drv_gpio_menu0();
         break;
      
      case 2:
         Status_nivel = 1;
         Status_Opcion1 = 0;
         Flag_sub_menu1 = 1;
         break;
   } 
}

void drv_gpio_clear(){

   Status_Opcion = 0;
   Status_opcion1 = 0;  
   Flag_btn_inicio = 0;
   Flag_sub_menu1 = 0;
   Flag_sub_menu0 = 0;
   Flag_ejecutar = 0;
   Flag_salir = 0;
   Flag_RH = 0;
   Flag_RM = 0;
   seg = 0;
   min = 0;
   //min2 = 0;
}

void drv_gpio_finish1(){
   Flag_ejecutar = 0;
   Flag_sub_menu1 = 1;
   Status_nivel = 1;   
}

void drv_gpio_finish0(){
   Flag_ejecutar = 0;
   Flag_sub_menu1 = 0;
   Status_nivel = 0;   
}

void drv_gpio_off(){
   output_c(0b00000000); 
   output_e(0b00000000);  
   output_bit(SOLENOIDE3,0);
   //output_bit(RH,0);
   set_pwm1_duty(5);
}

void drv_gpio_off_nf_ON(){
   output_e(0b00000000);  
   output_bit(SOLENOIDE3,0);
   output_bit(SOLENOIDE4,0);
   output_bit(STF,0);
   output_bit(STR,0);
   output_bit(NF,1);
}

void drv_gpio_NF(){
   output_bit(SOLENOIDE3,0);
   output_bit(NF,1);
   //set_pwm1_duty(5);
}

void drv_gpio_STF(){
   output_bit(SOLENOIDE3,0);
   output_bit(STF,1);
}

void drv_gpio_STR(){
 
   output_bit(SOLENOIDE3,0);
   output_bit(STR,1);

}
void drv_gpio_RH(){

   set_pwm1_duty(34);
 
   output_bit(SOLENOIDE3,0);
   ////output_bit(RH,1);
   Flag_RH = 0;
   Flag_RM = 0;
   
}

void drv_gpio_RM(){
  //printf(lcd_putc,"\fVELOCIDAD MEDIA\n");
   set_pwm1_duty(17);//21
   output_bit(SOLENOIDE3,0);  
   Flag_RM = 1;
}

void drv_gpio_SolComp(){
  output_bit(SOLENOIDE3,0);
  output_bit(SOL_COMPUERTA,1);
  set_pwm1_duty(5);
}

void drv_gpio_BomExt(){
  output_bit(SOLENOIDE3,0);
  output_bit(BOMB_EXTRACCION,1);
  ////set_pwm1_duty(5);
}

void drv_gpio_BomExt_STF(){
   output_bit(SOLENOIDE3,0);
   output_bit(STF,1);
   output_bit(BOMB_EXTRACCION,1);
   ////output_bit(RH,1);
   set_pwm1_duty(315);
   Flag_RH = 1;
   Flag_RM = 0;
}

void drv_gpio_Solenoide12(){
  output_bit(SOLENOIDE3,0);
  output_bit(SOLENOIDE1,1);
  output_bit(SOLENOIDE2,1);
  //set_pwm1_duty(5);
}

void drv_gpio_Solenoide34(){
  
  output_bit(SOLENOIDE3,1);
  output_bit(SOLENOIDE4,1);

  ////set_pwm1_duty(5);
}

void drv_gpio_lavado(){

   Status_fase = FASE_LAVADO;
   ///drv_gpio_NF();
   
   while(min<T_lavado && Flag_salir != 1){
      if(Flag_salir != 1){drv_gpio_STF()           ; drv_gpio_RM();drv_gpio_seg(5,true); }
      if(Flag_salir != 1){drv_gpio_off_nf_ON()     ;while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(6,true);}
         
      if(Flag_salir != 1){drv_gpio_off_nf_ON()     ;drv_gpio_seg(2,true);}
         
      if(Flag_salir != 1){drv_gpio_STR()           ; drv_gpio_RM();drv_gpio_seg(5,true);}
      if(Flag_salir != 1){drv_gpio_off_nf_ON()     ; while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(10,true);}
         
      if(Flag_salir != 1){drv_gpio_off_nf_ON()     ; drv_gpio_seg(2,true);}
   }

   
   if(Status_modo==MODO_LAVADO){
      Flag_salir = 0;
      Status_modo = SIN_MODO ;
      Status_fase = SIN_FASE;
      drv_gpio_off();
   }

   ////drv_gpio_off();
}

void drv_gpio_enjuague(){

   //min2 = 0;
   //drv_gpio_NF();
   
   if(Status_modo==MODO_AUTOMATICO){
      T_ciclo = T_lavado + T_enjuague;
   }
   else if(Status_modo == MODO_CENTRIFUGADO){
      T_ciclo = Status_tiempo*0.15;
   }
   
   for(repeticion = 0 ;repeticion<3;repeticion++){
   
      Status_fase = SIN_FASE ;
      
      //T_ciclo = T_ciclo *(repeticion+1);
      
      if(Status_modo==MODO_AUTOMATICO){
         //T_ciclo = T_lavado +(T_ciclo *(repeticion+1));
         switch(repeticion){
            case 0:
               T_ciclo = T_lavado + 4;
               break;
            case 1:
               T_ciclo = T_lavado + 8;
               break;
            case 2:
               T_ciclo = T_lavado + 13;
               break;
         }
      }
      
      else if(Status_modo == MODO_CENTRIFUGADO){
         //T_ciclo = T_ciclo *(repeticion+1);
         switch(repeticion){
            case 0:
               T_ciclo = 4;
               break;
            case 1:
               T_ciclo = 8;
               break;
            case 2:
               T_ciclo = 13;
               break;
         }
      }
         // Se abre la bomba de agua hasta que el nivel de agua sea cero    
      while(drv_gpio_vaciar(SIN_NIVEL)==0 && Flag_salir != 1){drv_gpio_NF();drv_gpio_BomExt();drv_gpio_seg(1,true);}
      // se apaga la bomba de extraccion

      
      // T_lavado = Status_tiempo*0.4
      // T_centrifugado = Status_tiempo*0.15;
      // T_enjuague = Status_tiempo*0.45;
      // T_enjuague = Status_tiempo*0.15;
	  
      Status_fase = FASE_LAVADO;
      
      drv_gpio_off_nf_ON();
         ////for(Flag_ciclo = 0;Flag_ciclo<2;Flag_ciclo++){
        while(min<T_ciclo && Flag_salir != 1){
            if(Flag_salir != 1){drv_gpio_STF()        ; drv_gpio_RM();drv_gpio_seg(5,true); }
            if(Flag_salir != 1){drv_gpio_off_nf_ON()  ; while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(6,true);}
            
            if(Flag_salir != 1){drv_gpio_off_nf_ON()  ; drv_gpio_seg(2,true);}
            
            if(Flag_salir != 1){drv_gpio_STR()        ; drv_gpio_RM();drv_gpio_seg(5,true);}
            if(Flag_salir != 1){drv_gpio_off_nf_ON()  ; while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(10,true);}
            
            if(Flag_salir != 1){drv_gpio_off_nf_ON()  ; drv_gpio_seg(2,true);}
            
        }       
       output_bit(SOLENOIDE1,0);
       output_bit(SOLENOIDE2,0);
   }  
}


void drv_gpio_centrifugado(){
   
   drv_gpio_enjuague();
   
   output_bit(SOLENOIDE1,0);
   output_bit(SOLENOIDE2,0);
   
   Status_fase = SIN_FASE;
   
   if(Status_modo==MODO_AUTOMATICO){
      T_ciclo = Status_tiempo;//T_lavado + T_enjuague + T_centrifugado;
   }
   else if(Status_modo == MODO_CENTRIFUGADO){
      T_ciclo = Status_tiempo_cent;//T_enjuague + T_enjuague;
   }
      
   while(drv_gpio_vaciar(SIN_NIVEL)==0 && Flag_salir != 1){drv_gpio_BomExt();drv_gpio_seg(1,true);}
   
   //T_centrifugado = (Status_tiempo*0.15) + 1;
   
   while(min<T_ciclo && Flag_salir != 1){
     output_bit(SOLENOIDE1,0);
     output_bit(SOLENOIDE2,0);
     if(Flag_salir != 1){ drv_gpio_BomExt_STF();drv_gpio_NF();drv_gpio_seg(60,true);}
     else{break;}//if(Flag_salir == 1);break;
   }
   ////} 
   
   Flag_salir = 0;
   Status_modo = SIN_MODO ;
   Status_fase = SIN_FASE;
   drv_gpio_off();
   //if(Status_modo == MODO_AUTOMATICO){drv_gpio_SolComp();drv_gpio_seg(5,true);drv_gpio_off();Status_modo = SIN_MODO ;}
}



void drv_gpio_automatico2(){

   drv_gpio_lavado();
   drv_gpio_centrifugado();

}

void drv_gpio_automatico(){


   drv_gpio_NF();

   T_lavado = Status_tiempo*0.4;
   Status_fase = FASE_LAVADO;
   
   /*
   #define FASE_LAVADO           1 // 
   #define FASE_ENJUAGUE         2 // 
   #define FASE_CENTRIFUGADO     3 // 
   
   */
   // T_centrifugado = Status_tiempo*0.15;
   // T_enjuague = Status_tiempo*0.45;
   
   for(minutos = 0; minutos<T_lavado;minutos++){ 
   
      for(Flag_ciclo = 0;Flag_ciclo<2;Flag_ciclo++){
      
         if(Flag_salir != 1){drv_gpio_STF()              ; drv_gpio_RM();drv_gpio_seg(5,true); }
         if(Flag_salir != 1){drv_gpio_off_nf_ON()        ; while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(6,true);}
         
         if(Flag_salir != 1){drv_gpio_off_nf_ON()        ; drv_gpio_seg(2,true);}
         
         if(Flag_salir != 1){drv_gpio_STR()              ; drv_gpio_RM();drv_gpio_seg(5,true);}
         if(Flag_salir != 1){drv_gpio_off_nf_ON()        ; while(Flag_rotacion == 0){drv_gpio_off_nf_ON();drv_gpio_seg(1,true);}}//drv_gpio_seg(10,true);}
         
         if(Flag_salir != 1){drv_gpio_off_nf_ON()        ; drv_gpio_seg(2,true);}
      }
   }
   //FIN LAVADO

   drv_gpio_enjuague();

   //CENTRIGUGADO
   
   Status_fase = SIN_FASE;
   
   while(drv_gpio_vaciar(SIN_NIVEL)==0 && Flag_salir != 1){drv_gpio_BomExt();drv_gpio_NF();drv_gpio_seg(1,true);}
   
   //T_centrifugado = (Status_tiempo*0.15)+1; 
   
   for(minutos = 0; minutos<T_centrifugado;minutos++){
       
     //if(Flag_salir != 1){ drv_gpio_STF(); drv_gpio_RH();   drv_gpio_seg(60,true);}drv_gpio_BomExt_STF()
     if(Flag_salir != 1){ drv_gpio_BomExt_STF();drv_gpio_NF();   drv_gpio_seg(60,true);}
     else{break;}//if(Flag_salir == 1);break;
   } 

   //FIN CEBTRIGUGADO
   
   Flag_salir = 0;   
   drv_gpio_SolComp();
   drv_gpio_seg(5,true);
   drv_gpio_off();
   Status_modo = SIN_MODO ;
   Status_fase = SIN_FASE;
   //drv_gpio_SolComp();
}

void drv_gpio_control_time(){
   
   seg++;
   if(seg>59){
      min++;
      //min2++;
      seg = 0;
   }
      
      switch(Status_modo){
      
         case MODO_AUTOMATICO:
            if(min == Status_tiempo){Flag_salir =1;drv_gpio_off();}
            break;
         case MODO_LAVADO:
            if(min == T_lavado){Flag_salir =1;drv_gpio_off();}
            break;
         case MODO_CENTRIFUGADO:
            if(min == Status_tiempo_cent){Flag_salir =1;drv_gpio_off();}
            break;
      }
      
      lcd_gotoxy(1,2);
      
      if(seg<10){
         printf(lcd_putc,"Tiempo:%2dm:0%ds\n",min,seg);
      }
      else{
         printf(lcd_putc,"Tiempo:%2dm:%2ds\n",min,seg);
      }
   ////}   
}

void drv_gpio_seg(int segundos,int1 showtime){

int i,j;

   if(Flag_salir ==1 || Status_modo == SIN_MODO){
      goto fin;
   } 
  
  else{
      for(i = 1; i <=segundos; i++){
         
         if(showtime==1){
            drv_gpio_mode_time();
            drv_gpio_control_time();
            drv_gpio_test_nivel();
         } 
         else{
            //drv_gpio_mode_time();
            printf(lcd_putc,"\f<<INVERSION DE>>",);
            lcd_gotoxy(1,2);
            printf(lcd_putc,"    <<GIRO>>\n");
         }
         for(j = 0; j <=10; j++){
            delay_ms(100);
            drv_gpio_pulsadores();
          
            if(Flag_salir ==1 || Status_modo == SIN_MODO){
               goto fin;
            }     
         }
      }
   }
   
   fin:
   i = 0;

}

void drv_gpio_pulsadores(){

   drv_gpio_int_rb();      //Verifica los Botones para manejar el menu
   drv_gpio_lcd_menu();    // Muestra El menu activo
   drv_gpio_int_rb0();
   drv_gpio_alarmas();     // Verifica cada 500ms la activacion de las Alarmas 1 y 2 
   drv_gpio_ticks();
   //drv_gpio_adc_modo();  
}

void drv_gpio_ticks(){
  // FRECUENCIMETRO DIGITAL
  
   if(timeticks==10){   // Cada 10 interrupciones muestra los pulsos del motor
                        // es decir cada 1 seg. cada desbordamiento tarda 100ms
                        // De Acuerdo a la Ecuacion:
                        // T = 4/Fosc*Preescaler(65536 - x)
                        // T = 1u*1(65536 - 0)
                
      contador = get_timer0();   // Obtiene la cantidad de pulsos en el timer 0
      contador=contador*2;       // El valor del timer se multiplica por el preescaler 
                                 //minimo que es 2
      if(contador == 0)Flag_rotacion = 1; 
      else Flag_rotacion = 0; 
      set_timer0(0); // Inicializa el timer 0
   
  }
     
   timeticks++; // se incrementa w luego de la interrupcion, sus valores seran 0 0 1
   if(timeticks>10){timeticks = 0;}
}

void drv_gpio_mode_time(){

       T_lavado = Status_tiempo*0.4;
       T_enjuague = Status_tiempo*0.45;
       T_centrifugado = Status_tiempo*0.15;
       
       Status_tiempo_cent = Status_tiempo*0.6;
       
       
   switch(Status_modo){
   
       case MODO_AUTOMATICO:
         //printf(lcd_putc,"\f <<AUTOMATICO>>\n");    
         //Status_tiempo = 30;
         printf(lcd_putc,"\fAUTOMATICO:%dm\n",Status_tiempo);  
         //printf(lcd_putc,"\fAUTOMATICO:%dm\n",Status_agua);  
      break;  
      
      case MODO_LAVADO:
         //Status_tiempo = 15;
         
        // Status_tiempo = T_lavado;
         printf(lcd_putc,"\fLAVADO: %dm\n",T_lavado);
         //printf(lcd_putc,"\f   <<LAVADO>>\n");
         break;
         
      case MODO_CENTRIFUGADO:
         printf(lcd_putc,"\fCENTRIFUGADO:%dm\n",Status_tiempo_cent); 
         break;
              
         
     }  
}

//GPIO ADC

int16 drv_gpio_adc_read(int channel){

   int16 medicion=0;                     //variable entera que contendra la medicion del convertidor AD
   int1 done = 0;                        //Contendra 1 si el convertidor termin� de convertir
   
   setup_adc_ports(AN0_AN1_AN3); 		// CANALES ANALOGICOS AN0 AN1 Y AN3
   setup_adc(ADC_CLOCK_INTERNAL); 		// conversion analogica con el reloj interno
   set_adc_channel (channel);          	//Establecemos el canal de lectura analogica
   delay_ms(1);                       	//a small delay is required after setting the channel
   medicion=read_adc ();               // Hace conversi�n AD 
   done = adc_done();                  //done = 1 si el convertidor termino de convertir
   while(!done)
   {
      done = adc_done();               //Mientras no acabe de convertir se seguira ciclando
   }
   setup_adc (adc_off);                //detenemos al convertidor
   //medicion = (medicion/1023.0)*5;
   return medicion;   
}

void drv_gpio_adc_lcd(){

   Vtemperatura = drv_gpio_adc_read(0);
   Vnivel = drv_gpio_adc_read(1);
   printf(lcd_putc,"\fTEMP : %2.1fv\n",(Vtemperatura/1023.0)*5);
   printf(lcd_putc,"NIVEL: %2.1fv\n",(Vnivel/1023.0)*5);
   delay_ms(100);

}

void drv_gpio_adc_modo(){

   if(time>45){          
      if(Status_modo!=SIN_MODO){drv_gpio_adc_lcd();}
   }
     
   time++; // se incrementa w luego de la interrupcion, sus valores seran 0 0 1
   if(time>45){time=0;}
   
}

int1 drv_gpio_level(int percent){

   ADCNivel = drv_gpio_adc_read(1);
   ADCrule = (1023*percent)/100;
   
   if(ADCNivel < ADCrule){
      Flag_adc_nivel = 0;
   }
   else{
      Flag_adc_nivel = 1;
      
   }
   return Flag_adc_nivel;
   
}

int1 drv_gpio_vaciar(int percent){

   ADCNivel = drv_gpio_adc_read(1);
   ADCrule = (1023*percent)/100;
   
   if(ADCNivel <= ADCrule){
      Flag_adc_nivel = 1;
   }
   else{
      Flag_adc_nivel = 0;
   }
   return Flag_adc_nivel;

}

//void drv_gpio_test_nivel(){}

void drv_gpio_test_nivel(){

   switch(Status_fase){
   
      ///case FASE_ENJUAGUE :
      case FASE_LAVADO :
         if(drv_gpio_level(Status_agua)==0 && Flag_salir != 1){
            drv_gpio_Solenoide12();
         }
         else{
            seg_solenoide++;
            //delay_ms(1000);
            if(seg_solenoide==12){
               output_bit(SOLENOIDE1,0);
               output_bit(SOLENOIDE2,0);
               seg_solenoide = 0;
            }
            
         }
         break;
      
      case SIN_FASE:
      
         break;
      }
      
      
}

