#include <SoftwareSerial.h>

#define  noDEBUG
//---------------------------------------------
#ifdef DEBUG
#define port Serial

#else
#define port BT1
#endif

#define LED_ON digitalWrite(13,1);
#define LED_OFF digitalWrite(13,0);

#define   SEG     1000
#define  MIN     60000
#define  HORA  3600000
#define DIA   86400000      // Die en miliseg
#define  PIN_BOMBA  12
#define  PRENDER_BOMBA digitalWrite(PIN_BOMBA, 1);LED_ON
#define  APAGAR_BOMBA  digitalWrite(PIN_BOMBA, 0);LED_OFF

//-----------------------------------------------------
struct CFGR
{
  unsigned long rton;
  unsigned long frec;
  unsigned char lon;
  unsigned char loff;
  int Humedad_min;
  
};
extern CFGR cfg;

struct CMD
{ 
  char orden;
  int  parametro;    
};
extern CMD cmd;

extern SoftwareSerial BT1;
//-----------------------------------------------------
int leer_sensores();
int send_tx_config(); 
int leer_config();
int grabar_config();
void grabar_config_default();


