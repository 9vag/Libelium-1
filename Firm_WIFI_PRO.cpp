#include <WaspWIFI_PRO.h>

uint8_t socket = SOCKET0;

// URL POST SERVER 
// URL "http://ptsv2.com/t/ui1sl-1565799765/post"              // url for test a request, you can check what it is: http://ptsv2.com
// https://cxc-smart-water.scriptrapps.io/app/api/subscription/subscriber?
char type[] = "https";
char host[] = "cxc-smart-agriculture.scriptrapps.io";
char port[] = "443";
char url[]  = "app/api/subscription/subscriber??auth_token=WDdFQTk4QTU3MDpteURtcEJyb2tlcjpEODNCN0UzQUZDOTJBNjU5NEM2RUU0Q0VDRDIxMzFGMg==";


// define trusted Certificate Authority
char TRUSTED_CA[] =\ 
"-----BEGIN CERTIFICATE-----\r"\
"MIIDxTCCAq2gAwIBAgIBADANBgkqhkiG9w0BAQsFADCBgzELMAkGA1UEBhMCVVMx\r"\
"EDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxGjAYBgNVBAoT\r"\
"EUdvRGFkZHkuY29tLCBJbmMuMTEwLwYDVQQDEyhHbyBEYWRkeSBSb290IENlcnRp\r"\
"ZmljYXRlIEF1dGhvcml0eSAtIEcyMB4XDTA5MDkwMTAwMDAwMFoXDTM3MTIzMTIz\r"\
"NTk1OVowgYMxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdBcml6b25hMRMwEQYDVQQH\r"\
"EwpTY290dHNkYWxlMRowGAYDVQQKExFHb0RhZGR5LmNvbSwgSW5jLjExMC8GA1UE\r"\
"AxMoR28gRGFkZHkgUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgLSBHMjCCASIw\r"\
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL9xYgjx+lk09xvJGKP3gElY6SKD\r"\
"E6bFIEMBO4Tx5oVJnyfq9oQbTqC023CYxzIBsQU+B07u9PpPL1kwIuerGVZr4oAH\r"\
"/PMWdYA5UXvl+TW2dE6pjYIT5LY/qQOD+qK+ihVqf94Lw7YZFAXK6sOoBJQ7Rnwy\r"\
"DfMAZiLIjWltNowRGLfTshxgtDj6AozO091GB94KPutdfMh8+7ArU6SSYmlRJQVh\r"\
"GkSBjCypQ5Yj36w6gZoOKcUcqeldHraenjAKOc7xiID7S13MMuyFYkMlNAJWJwGR\r"\
"tDtwKj9useiciAF9n9T521NtYJ2/LOdYq7hfRvzOxBsDPAnrSTFcaUaz4EcCAwEA\r"\
"AaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYE\r"\
"FDqahQcQZyi27/a9BUFuIMGU2g/eMA0GCSqGSIb3DQEBCwUAA4IBAQCZ21151fmX\r"\
"WWcDYfF+OwYxdS2hII5PZYe096acvNjpL9DbWu7PdIxztDhC2gV7+AJ1uP2lsdeu\r"\
"9tfeE8tTEH6KRtGX+rcuKxGrkLAngPnon1rpN5+r5N9ss4UXnT3ZJE95kTXWXwTr\r"\
"gIOrmgIttRD02JDHBHNA7XIloKmf7J6raBKZV8aPEjoJpL1E/QYVN8Gb5DKj7Tjo\r"\
"2GTzLH4U/ALqn83/B2gX2yKQOC16jdFU8WnjXzPKej17CuPKf1855eJ1usV2GDPO\r"\
"LPAvTK33sefOT6jEm0pUBsV/fdUID+Ic/n4XuKxe9tQWskMJDE32p2u0mYRlynqI\r"\
"4uJEvlz36hz1\r"\
"-----END CERTIFICATE-----";
////////////////////////////////////////////////////////////////////////


// Data packet variable
char data[255]="";

// EXTRA VARIABLES
uint8_t error;
uint8_t status;
unsigned long previous;
char* sleepTime = "00:00:00:20";
int counter = 0;
char id_wasp[20]="MSK_SA";
char id_secret [20]="1234567989";


void setup() 
{
  error = WIFI_PRO.ON(socket);

  if (error == 0)
  {    
    USB.println(F("1. WiFi switched ON"));
  }
  else
  {
    USB.println(F("1. WiFi did not initialize correctly"));
  }



  // Set Trusted CA
  error = WIFI_PRO.setCA(TRUSTED_CA);

  if (error == 0)
  {    
    USB.println(F("2. Trusted CA set OK"));
  }
  else
  {
    USB.println(F("2. Error calling 'setCA' function"));
    WIFI_PRO.printErrorCode();
  }
  

  // Set URL
  error = WIFI_PRO.setURL( type, host, port, url );

  // check response
  if (error == 0)
  {
    USB.println(F("3. Set URL OK"));           
  }
  else
  {
    USB.println(F("3. Error calling 'setURL' function"));
    WIFI_PRO.printErrorCode();
  }

  // Switch OFF
  WIFI_PRO.OFF(socket);
  USB.println(F("4. WiFi switched OFF"));
  USB.println(F("Setup done\n\n"));
}



void loop()
{ 

  // Wake Up device
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


  // GET DATA
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

 
  // CONECT TO THE NETWORK
  // -----------------------------------------------------------------------------------------
  // check connectivity
  status =  WIFI_PRO.isConnected();

  // Check if module is connected
  if( status == true )
  {    
    USB.print(F("2. WiFi is connected OK"));
    // http request
    error = WIFI_PRO.post(data); 

    // SEND DATA PACKET
    // -----------------------------------------------------------------------------------------        
    // check response
    if( error == 0 )
    {
      USB.println(F("HTTPS POST OK"));          
      
      USB.print(F("Server answer:"));
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
    USB.print(F("2. WiFi is connected ERROR")); 
  }

  counter++;

  // 8. SLEEP DEVICE
  // -----------------------------------------------------------------------------------------
  USB.println(F("enter deep sleep"));
  USB.println(F("---------------------------------------------------------------------------------------------"));    
  USB.println(F("---------------------------------------------------------------------------------------------"));
  USB.println(F(" "));
  USB.println(F(" "));
      
  PWR.deepSleep(sleepTime,RTC_OFFSET,RTC_ALM1_MODE1,ALL_OFF);    }
