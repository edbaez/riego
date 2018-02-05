#include <EEPROM.h>

//--------------------------------------------------
//   C O N T R O L     R I E G O
//BY EDG 2016-
//       2018
//--------------------------------------------------
#define DEBUG
#define SEG      1000      // segudo en milseg
#define MIN     60000      // minuto en miliseg
#define HORA  3600000      // hora en miliseg
#define DIA  86400000      // Die en miliseg
//--------------------------------------------------
#define PIN_BOMBA 12      // 
#define NIVEL_AGUA 14     // PIN ASOCIADO AL MIDDOR DE NIVEL.
#define IF_AGUA     1     //   digitalRead(HIVEL_AGUA)
#define ENCENDER_BOMBA   digitalWrite(PIN_BOMBA,0);//   O J O 
#define APAGAR_BOMBA     digitalWrite(PIN_BOMBA,1);// A L  R E V E Z 
//---------------------------------------------------
#include <SoftwareSerial.h>
//---------------------------------------------------
SoftwareSerial BT1(3, 2);   // RX | TX

class tiempo_bcd{
  char segundo;
  char minuto;
  char hora;
};
class efemerides {
  tiempo_bcd t_encendido;
  tiempo_bcd t_apagado;
  char pendiente;
  };



class estado {
  public:
  unsigned long T_on= 10000;    //Tiempo de encendido.deault 10 minuto por dia                                                                                                                                                                                                       
  unsigned long Tau = DIA/2;    //DIA;
  boolean control_bomba_manual;
  efemerides T_gr;
} ST;

//---------------------------------------------------
void setup()
   { 
     pinMode(PIN_BOMBA,1);
     digitalWrite(PIN_BOMBA,1);
     Serial.begin(9600);
     Serial.print("hola");
     
     pinMode(13,OUTPUT);
     setup_blutu();
     setup_rtc();
     
     pinMode(NIVEL_AGUA,0);
     titilar(40);
    }
//---------------------------------------------------
void loop()
   {  
     if(leer_terminal()== 2) interprete();
     control_riego();
     return; 
   } 




   
//---------------------------------------------------
char msj[35];
int leer_terminal()
// lee el puerto blue thoy,
// retorna:
//        0 no recivio nada o no completo datos nuevos
//        2 hay nuevos valores recivio 
//        -1 exeso de caracteres sin fin de coso
{
   static char j =0;
   char c;
   while(BT1.available())
     {
      c =(char)BT1.read(); 
      if(c== '#')           //final del choro de parametros
      {
        msj[j]='\0';
        j=0;
        return 2;           // valor de retorno XXXX
      }
      else
      {
        msj[j++]=c;        //escribe el caracter en el bufer
        if( j>30)          // largo del bufer exedido
        {
          j=0;
          return -1;       // retorna -1 no encontro final de string
        }
      }
     }
   return 0;              // sin completar string o sin dator en el bufer
}

//   comando  1 primeros caractyeres
//    parámetro el resto.
//
//

   void interprete()  // Decodifica los datos arrivados por blutu
   {
    char cmd;
    cmd = msj[0];
    switch( cmd)  
    {
      case 'R': 
      {
        BT1.print ("T");
        BT1.print (ST.T_on/SEG);
        BT1.print ("#");
        BT1.print ("U");
        BT1.print (ST.Tau/MIN);
        BT1.print ("#");
        
       Serial.print("request");
       
      }                   break ;
      case 'B':
      {
        if(atoi(msj+1)==1)
        {
          ENCENDER_BOMBA
          Serial.println("bomba on");
          ST.control_bomba_manual = 1        ;// enciende 
          }
        else  
        {
          APAGAR_BOMBA;
          ST.control_bomba_manual = 0;
          Serial.println("bomba off");
        }
      }                                ;break;
      case 'G': 
          if (read_ds1307()) print_time();// Leer los registros del RTC
          else   Serial.println("No s DS1307");
          break;
          
      case 'T': Serial.println (ST.T_on=(double)SEG*atoi(msj+1)) ;break;
      case 'U': Serial.println (ST.Tau= (double)MIN*atoi(msj+1)) ;break;
      
      default : Serial.println(cmd);
    }
    
#ifdef DEBUG
    //  Serial.println("interprete");
    //  Serial.println(T_on);
    // Serial.println(y);
    // Serial.println(vel);
#endif 
   }
// ............................................ 
#define tiempo_de_encendido  
  void control_riego()
  {
    if(((millis()%ST.Tau <= ST.T_on)or ST.control_bomba_manual)&IF_AGUA) ENCENDER_BOMBA
    else APAGAR_BOMBA
  }
// ............................................ 
  void titilar(int pulsos)
  {
    int j;
    for( j= 0;j++<pulsos; digitalWrite(13, !digitalRead(13)))
    delay(100);
  }
