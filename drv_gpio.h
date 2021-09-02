#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

   //PINES PUERTO A
   #define TEMPERATURA1          pin_a0
   #define NIVEL1                pin_a1
   #define SENSOR ROTACION       pin_a4
  
   //PINES PUERTO B
   #define MICRO_SWITCH          pin_b0
   #define ALARMA_VARIADOR1      pin_b1
   #define ALARMA_VARIADOR2      pin_b2
   //#define NF                    pin_b3
   #define BTN_STOP              pin_b4
   #define BTN_INICIO            pin_b5
   #define BTN_SUBIR_MENU        pin_b6  
   #define BTN_BAJAR_MENU        pin_b7 

   //PINES PUERTO C
   /*
   #define STF                   pin_c0
   #define STR                   pin_c1
   #define RH                    pin_c2
   #define RM                    pin_c3
   #define SOLENOIDE1            pin_c4
   #define SOLENOIDE2            pin_c5
   #define SOLENOIDE3            pin_c6
   #define SOLENOIDE4            pin_c7
   */
   
   #define STF                   pin_c4
   #define STR                   pin_c5
   #define NF                    pin_c6
   //#define RH                    pin_c7
   #define RH                    pin_c2
   #define SOLENOIDE1            pin_c0
   #define SOLENOIDE2            pin_c1
   #define SOLENOIDE3            pin_b3
   //#define SOLENOIDE4            pin_c2
   #define SOLENOIDE4            pin_c7
   
   
   //PINES PUERTO E
   #define SOL_COMPUERTA         pin_e0
   #define BOMB_EXTRACCION       pin_e1

   //MODOS LAVADORA
   #define SIN_MODO              0
   #define MODO_AUTOMATICO       1
   #define MODO_LAVADO           2
   #define MODO_CENTRIFUGADO     3
   //#define MODO_ENJUAGUE     3

   #define MODO_INICIO           4
   //NIVEL DE AGUA
   #define SIN_NIVEL             17
   #define NIVEL_BAJO_1          18
   #define NIVEL_BAJO_2          18 
   #define NIVEL_MEDIO           25
   #define NIVEL_ALTO            26
   
   //TEMPERATURA
   #define SIN_TEMP              0
   #define TEMP_FRIA             1
   #define TEMP_CALIENTE         2
   #define TEMP_TIBIA            3
   
   //TIEMPOS
   #define SIN_TIEMPO            0
   #define TIEMPO_25MIN          25
   #define TIEMPO_35MIN          30
   #define TIEMPO_45MIN          45
   #define TIEMPO_55MIN          55
   
   #define MAX_OPCION            2 // selftest 7
   #define MAX_OPCION_           3 // selftest 7
   #define MAX_OPCION_1          5 // selftest 7
   
   #define SIN_FASE              0// 
   #define FASE_LAVADO           1 // 
   #define FASE_ENJUAGUE         2 // 
   #define FASE_CENTRIFUGADO     3 // 
   
   // FUNCIONES D USO GNERAL
   
   void drv_gpio_int_rb();
   void drv_gpio_int_rb0();
   void drv_gpio_status_subir();
   void drv_gpio_status_bajar();
   void drv_gpio_alarmas();
   
   // FUNCIONES DE MENU
   
   void drv_gpio_selftest();
   void drv_gpio_lcd_menu();
   void drv_gpio_lcd_test();
   void drv_gpio_menu_test();
   void drv_gpio_mode_time();
   void drv_gpio_ticks();
   
   //FUNCIONES PARA CONTROL DE SALIDAS DIGITALES
   
   void drv_gpio_STF();
   void drv_gpio_STR();
   void drv_gpio_RH();
   void drv_gpio_RM();
   void drv_gpio_NF();
   void drv_gpio_SolComp();
   void drv_gpio_BomExt();
   void drv_gpio_BomExt_STF();
   void drv_gpio_Solenoide12();
   void drv_gpio_Solenoide34();
   void drv_gpio_off_nf_ON();
   //MODOS

   void drv_gpio_menu0();
   void drv_gpio_menu1();  
   void drv_gpio_submenu_modo();
   void drv_gpio_submenu_tiempo();
   void drv_gpio_submenu_nivel();
   void drv_gpio_submenu_temp();
   
   void drv_gpio_lavado();
   void drv_gpio_centrifugado();
   void drv_gpio_automatico();
   void drv_gpio_automatico2();
   void drv_gpio_enjuague();
   void drv_gpio_seg(int segundos,int1 showtime);
   
   void drv_gpio_finish0();
   void drv_gpio_finish1();
   void drv_gpio_off();
   void drv_gpio_clear();
   void drv_gpio_back();
   
   //GPIO ADC
   void drv_gpio_adc_lcd();
   int16 drv_gpio_adc_read(int channel);
   void drv_gpio_adc_modo();
   
   void drv_gpio_control_time();
   
   void drv_gpio_lcd_show1(char * cmd);
   void drv_gpio_lcd_show2(char * cmd,char * cmd1);
   
   void drv_gpio_pulsadores();
   
   int1 drv_gpio_level(int percent);
   
   int1 drv_gpio_vaciar(int percent);
   
  void drv_gpio_test_nivel();
   
   

#endif /* __DRV_LCD_H */


