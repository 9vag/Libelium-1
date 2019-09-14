/*  
 *  ------ Example for show how to send data over HTTP -------- 
 *  
 *  
 *  Version:           1.0
 *  Design:            David Gascon, Yuri Carmona
 *  Implementation:    Renzo Varela
 */


// BIBLIOTECAS
// -----------------------------------------------------------------------------------------
#include <WaspWIFI_PRO.h>

// CLASS
// -----------------------------------------------------------------------------------------

// DEFINATIONS
// -----------------------------------------------------------------------------------------
// Socket modulo de comunicación
uint8_t socket = SOCKET0;

// URL POST SERVER 
// URL "http://ptsv2.com/t/ui1sl-1565799765/post"              // url for test a request, you can check what it is: http://ptsv2.com
// https://cxc-smart-water.scriptrapps.io/app/api/subscription/subscriber?

char type[] = "http";
char host[] = "cxc-smart-agriculture.scriptrapps.io";
char port[] = "80";
char url[]  = "app/api/subscription/subscriber";


char* sleepTime = "00:00:00:30";

// GLOBAL VARIABLES
// -----------------------------------------------------------------------------------------

// WiFi AP settings (CHANGE TO USER'S AP)
char ESSID[] = "Area_Comercial_CNV";
char PASSW[] = "C0mercialWifi.";

// Data packet variable
char data[255]="";

// Extra Variables
uint8_t error;
uint8_t status;
unsigned long previous;
int counter = 0;
int8_t answer;
int sd_answer;
int i=0;

char id_wasp[20]="test_http";
char id_secret [20]="1234567989";

void setup() {
      
  USB.ON(); 
  USB.println(F("Firmware Estandar WIFI PRO v2.2"));

  // Wifi module configuration
  error = WIFI_PRO.ON(socket);
  if (error == 0)
  {    
    USB.println(F("1. WiFi switched ON"));
  }
  else
  {
    USB.println(F("1. WiFi did not initialize correctly"));
  }

  error = WIFI_PRO.setESSID(ESSID);

  if (error == 0)
  {    
    USB.println(F("3. WiFi set ESSID OK"));
  }
  else
  {
    USB.println(F("3. WiFi set ESSID ERROR"));
  }


  //////////////////////////////////////////////////
  // 4. Set password key (It takes a while to generate the key)
  // Authentication modes:
  //    OPEN: no security
  //    WEP64: WEP 64
  //    WEP128: WEP 128
  //    WPA: WPA-PSK with TKIP encryption
  //    WPA2: WPA2-PSK with TKIP or AES encryption
  //////////////////////////////////////////////////
  error = WIFI_PRO.setPassword(WPA2, PASSW);

  if (error == 0)
  {    
    USB.println(F("4. WiFi set AUTHKEY OK"));
  }
  else
  {
    USB.println(F("4. WiFi set AUTHKEY ERROR"));
  }


  // Software Reset 
  error = WIFI_PRO.softReset();

  if (error == 0)
  {    
    USB.println(F("5. WiFi softReset OK"));
  }
  else
  {
    USB.println(F("5. WiFi softReset ERROR"));
  }
  error = WIFI_PRO.setURL( type, host, port, url );
  // check response
  if (error == 0)
  {
    USB.println(F("2. setURL OK"));
  }
  else
  {
    USB.println(F("2. Error calling 'setURL' function"));
    WIFI_PRO.printErrorCode();
  }

  USB.println(F("---------------------------------------------------------------------------------------------"));
  
}



void loop() 
{
  // 1. Wake Up device
  // -----------------------------------------------------------------------------------------

  RTC.ON();
  ACC.ON();

  // WIFI
  error = WIFI_PRO.ON(socket);
  if (error == 0)
  {    
    USB.println(F("1. WiFi switched ON"));
  }
  else
  {
    USB.println(F("1. WiFi did not initialize correctly"));
  }



    
  // 2. GET DATA
  // -----------------------------------------------------------------------------------------

  counter++;
  
  // BAT
  USB.print(F("Getting data..."));  
  char bat_str[12];
  dtostrf(PWR.getBatteryLevel(), 2, 0, bat_str);

  float temp_flt = rand() % 12 + 1;
  char temp_str[20]="2";
  Utils.float2String (temp_flt, temp_str, 1);

  float hum_flt = rand() % 101;
  char hum_str[20]="2";
  Utils.float2String (hum_flt, hum_str, 1);
  
  float pres_flt = rand() % 1100 + 900;
  char pres_str[20]="2";
  Utils.float2String (pres_flt, pres_str, 1);
 
  char wv_str[20]="N";
 
  float ane_flt = rand() % 100 + 1;
  char ane_str[20]="2";
  Utils.float2String (ane_flt, ane_str, 1);
 
  float pluv1_flt = rand() % 10 + 1;
  char pluv1_str[20]="2";
  Utils.float2String (pluv1_flt, pluv1_str, 1);
 
  float pluv2_flt = rand() % 10 + 1;
  char pluv2_str[20]="2";
  Utils.float2String (pluv2_flt, pluv2_str, 1);
 
  float pluv3_flt = rand() % 10 + 1;
  char pluv3_str[20]="2";
  Utils.float2String (pluv3_flt, pluv3_str, 1);
 
  float soil2_flt = rand() % 8000 + 5000;
  char soil2_str[20]="2";
  Utils.float2String (soil2_flt, soil2_str, 1);
 
  
  // 4. BUILD DATA PACKET
  // -----------------------------------------------------------------------------------------
  // Crea el paquete de datos

  //cxc-smart-water.scriptrapps.io/app/api/subscription/subscriber?&id=2345&id_wasp=MSD_SA&id_secret=696418FDC337DE58&WT=100&BAT=100&COND=100&ORP=100&DO=100&PH=100

  sprintf( data, "id=%d&id_wasp=%s&id_secret=%s&BAT=%d&TC=%s&HUM=%s&PRES=%s&STR=%s&ANE=%s&PLV1=%s&PLV2=%s&PLV3=%s&SOIL2=%s",
  counter,
  id_wasp, 
  id_secret,
  PWR.getBatteryLevel(), 
  temp_str,
  hum_str,
  pres_str,
  wv_str,
  ane_str,
  pluv1_str,
  pluv2_str,
  pluv3_str,
  soil2_str);

  // Show data packet
  USB.print(F("data: "));
  USB.println(data);


  // 6. CONECT TO THE NETWORK
  // -----------------------------------------------------------------------------------------
  USB.println(F("CONECTING..."));
  status =  WIFI_PRO.isConnected();

  // SI ESTA CONECTADO
  if (status == true)
  {    
    USB.print(F("WIFI CONECTED"));

    

    
    // 7.1 SEND DATA PACKET
    // -----------------------------------------------------------------------------------------    
    USB.print(F("SENDING DATA...   "));
    error = WIFI_PRO.post(data); 
    // Revisa respuesta
    if (error == 0)
    {
      USB.println(F("DATA SENT "));
      USB.println(data);
      USB.print(F("\nServer answer:"));
      USB.println(WIFI_PRO._buffer, WIFI_PRO._length);
    }
    else
    {
      USB.println(F("Error calling 'post' function"));
      WIFI_PRO.printErrorCode();
    }
  }
  else
  {
    USB.println(F("ERROR: WiFi is NOT connected"));
  }
  


     
  // 8. SLEEP DEVICE
  // -----------------------------------------------------------------------------------------
  USB.println(F("enter deep sleep"));
  USB.println(F("---------------------------------------------------------------------------------------------"));    
  USB.println(F("---------------------------------------------------------------------------------------------"));
  USB.println(F(" "));
  USB.println(F(" "));
      
  PWR.deepSleep(sleepTime,RTC_OFFSET,RTC_ALM1_MODE1,ALL_OFF);    
} 
