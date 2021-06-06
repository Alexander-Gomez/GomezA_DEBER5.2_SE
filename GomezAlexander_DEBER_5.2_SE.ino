  /* DEBER 5.2
   *  NOMBRE: Gomez Alexander
   * UNIDAD V: FUNCIONES ESPECÍFICAS
   * CÓDIGO 23 : MANEJO DE MODOS SLEEP
   * OBJETIVO: Corregir el codigo 23                         
   */
  #include<avr/power.h>
  #include<avr/sleep.h>
  #include<avr/wdt.h>
  #include <MsTimer2.h>
  #include<EEPROM.h>
  int dato;
  int on=0;
  void(* resetFunc) (void) = 0; // esta es la funcion
                                //void on(void);
  void setup() {
     dato=EEPROM.read(0);                 //Lectura de la memoria EPPROM en la posicion 0
     Serial.begin(9600);                  //Iniciamos la comunicacion serial en 9600 baudios
     Serial.println("SETUP");             //Mensaje de inicio
     if(dato==0){                         
      set_sleep_mode(SLEEP_MODE_STANDBY); //Tipo de SLEEP MODE
      sleep_enable();                     //Modo sleep activado
      EEPROM.write(0,1);                  //Escritura de la memoria EPPROM el valor de 1 en la posicion 0
      wdt_enable(WDTO_4S);                //wdt en 4 segundos
      }
      else{
       sleep_disable();                   //desactivamos el modo sleep
       EEPROM.write(0,0);                 //Escribimos en la memoria EEPROM el valor de 0 en la posicion 0
        MsTimer2::set(10000,tiempo);      //Configura timer 2 a un segundo
         MsTimer2::start();               //Iniciamos el timer
         wdt_enable(WDTO_4S);             //WDT en 4 segundos
      }
     attachInterrupt(0,encender,LOW);
  }
  void loop() {                          //iniciamos con una condicional
  if(dato==0){
    Serial.println("ME DORMI");          //mensaje de dormido
    delay(20);
   sleep_mode(); //entra a dormir
  }
   else{
    Serial.println("DESPIERTO");         //Mensaje de que el sistema desperto
    delay(2000);
    }
  }
  void tiempo(){
    Serial.println("ME DORMI");
    delay(20);
    sleep_mode();
   }
  
   void encender (){
      resetFunc();                       // la llamo con esto 
   }
