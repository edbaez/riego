
void setup_blutu()
{
  BT1.begin(9600); 
}
//------------------------------------------------------------
//#include <arduino.h>
#include"indoor.h"
#include<EEPROM.h>;
 
CFGR cfg;
 
//------------------------------------------------------------------
int leer_config()
{
  unsigned char *k,i;
  k = (unsigned char*)&cfg;
  for(i=0;i< sizeof(CFGR); *k++ = EEPROM.read(i++));
  if (cfg.frec==0)
    return -1;
 return 0;
}
 
int grabar_config()
{
  unsigned char *k,i=0;
  k = (unsigned char*)&cfg;
  for(i=0;i< sizeof(CFGR);EEPROM.write(i++,*k++));
  return 0;
}
 
 
void grabar_config_default()
{
  cfg.rton = 10*SEG;
  cfg.frec = 12*HORA;
  cfg.lon  = 8;
  cfg.loff = 18;
  grabar_config();
     
}
//------------------------------------------------------------------
 
int send_tx_config()
{
  char jj[20];
  BT1.print(itoa(cfg.frec/HORA,jj,10));
  BT1.print(" ; ");
  BT1.print(itoa(cfg.rton/SEG,jj,10));
 
  return 0;
}
 
//------------------------------------------------------------------
int leer_sensores()
     {return 0;}
 
 
 
//------------------------------------------------------------------
int func_A()
{
  return 0;
}
int func_B()
{
  return 0;
}
int func_C()
{
  return 0;
}
 
