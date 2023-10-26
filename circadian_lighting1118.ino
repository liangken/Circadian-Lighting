#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>              // Funciones para formatear fechas y horas
#include <WidgetRTC.h>            // Leer el tiempo de Internet en Blynk 
//Variables
int i = 0;
int statusCode;
char WIFIssid[]= "text";
char WIFIpassword[]="text";
String epass = "";
String esid="";
String st;
String content;
char auth[]="13yRRsVGn4GbEzchGifGXTPp0dWCFqNO";
int y;                                               // 年
byte m, d, w, h, mi, s;                              // 月/日/週/時/分/秒
int hours,minutes;

WidgetTerminal terminal(V2);
BlynkTimer timer;               // Para lanzar periodicamente las funciones del Blynk
WidgetRTC rtc;                  // Para leer el reloj de tiempo real

String Name="esp8266 circadian ";
int Parameterkey=0;                     //change the parameter
int Calibrationkey=0;                      //do calibration once
int Showtimekey=0;                         //do showtime
int ShowTimeDelay=2;
int CTtunable=2000;
int Lumtunable=0; 
int Fixkey=0;                              //DIY Fixed key
int Modifykey=0;
int resetwifi=0;
//int hours;
int HCT=15;                             //pinD8  GP15
int MCT=13;                             //pinD7  GP13
int LCT=12;                             //pinD6  GP12
int SLCT=14;                            //pinD5  GP14
int HCT_V13=0;
int MCT_V14=0;
int LCT_V12=0;
int SLCT_V21=0;
int spring=0,summer=0,autumn=0,winter=0;
int season=4;
int CTLumparameter_four[4][24][3]={
   {{5,1700,0},
    {6,1850,5},
    {7,2500,10},
    {8,3123,15},
    {9,4000,24},
    {10,5000,27},
    {14,5800,30},
    {15,4500,27},
    {16,4000,25},
    {18,2800,15},
    {19,2000,10},
    {20,1700,5},
    {21,1700,0}},
   {{4,1700,0},
    {5,1900,10},
    {7,2900,15},
    {8,3523,20},
    {9,5000,30},
    {10,6000,35},
    {14,6000,40},
    {15,5000,35},
    {17,4000,30},
    {19,3500,20},
    {20,2500,15},
    {21,1700,10},
    {22,1700,0}},
   {{5,1700,0},
    {6,1850,5},
    {7,2500,10},
    {8,3123,20},
    {9,4000,25},
    {10,5000,30},
    {12,5500,35},
    {14,5800,30},
    {15,5000,25},
    {16,4500,20},
    {17,3500,15},
    {19,2500,10},
    {20,2000,5},   
    {21,1700,0}},
   {{7,1700,0},
    {8,1850,10},
    {9,2650,25},
    {11,3124,30},
    {12,5000,32},
    {14,5000,32},
    {15,3124,30},
    {16,2500,25},
    {17,2000,20},
    {18,1700,10},
    {19,1700,0}},
};
int CTLumparameter[24][3]={
    {5,1700,0},
    {6,1850,5},
    {7,2500,10},
    {8,3123,15},
    {9,4000,24},
    {10,5000,27},
    {14,5800,30},
    {15,4500,27},
    {16,4000,25},
    {18,2800,15},
    {19,2000,10},
    {20,1700,5},
    {21,1700,0}};
int parameter[100][5]={};
int Reset[100][3]={};
int Stop[100][7]={                    //設定每周的幾點到幾點亮度為何
    {3,9,11,0,0,0,0},
    {6,0,23,0,0,0,0},
    {7,0,23,0,0,0,0}};
     
 

bool testWifi(void);
void launchWeb(void);
void setupAP(void);
 
//--------Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);
 
void setup()
{      
  pinMode(LED_BUILTIN, OUTPUT);//WIFI連接指示燈
  pinMode(HCT,OUTPUT);
  pinMode(MCT,OUTPUT);
  pinMode(LCT,OUTPUT);
  pinMode(SLCT,OUTPUT);
  Serial.begin(9600); //Initializing if(DEBUG)Serial Monitor
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initializing EEPROM
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
 
  // Read eeprom for ssid and password
  Serial.println("Reading EEPROM ssid");
  
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
 
  
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  
  Serial.print("WIFI: ");
  Serial.print(esid);
  
  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    //return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup accesspoint or HotSpot
  }
 
  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
    Serial.print(".");
    delay(100);
    server.handleClient();
  }
  Blynk.begin(auth, esid.c_str(), epass.c_str());
  Serial.print(Name);
  rtc.begin();
   Serial.println("done");
   CTtoparamter(CTLumparameter,parameter);  
   Copytoparameter(CTLumparameter,Reset);
   settinghrmin(parameter,Stop);
  Serial.println("HIGHT");
  for(int i=0;i<96;i++){
      if(parameter[i][0]==1){
         for(int j=1;j<5;j++){
            Serial.print(parameter[i][j]);
            Serial.print(" ");
         }
         Serial.println();
      }
  }
  Serial.println("MEDIUM");
  for(int i=0;i<96;i++){
      if(parameter[i][0]==2){
         for(int j=1;j<5;j++){
            Serial.print(parameter[i][j]);
            Serial.print(" ");
         }
         Serial.println();
      }
  }
  Serial.println("LOW");
  for(int i=0;i<96;i++){
      if(parameter[i][0]==3){
         for(int j=1;j<5;j++){
            Serial.print(parameter[i][j]);
            Serial.print(" ");
         }
         Serial.println();
      }
  }
  Serial.println("SUPER_LOW");
  for(int i=0;i<96;i++){
      if(parameter[i][0]==4){
         for(int j=1;j<5;j++){
            Serial.print(parameter[i][j]);
            Serial.print(" ");
         }
         Serial.println();
      }
  }
  Blynk.run(); 
  CTcalculator();
  resetbar(2000);
   terminal.clear();   
   terminal.print("WIFI: ");
   terminal.println(esid);         //顯示WIFI名稱
   terminal.print(Name);
   terminal.println(" connected!");  //已連接
   terminal.flush(); 
   
}
void loop() {

  
    Blynk.run();  
    if(Modifykey!=2){getTime();}                        // 取得時間
    timer.run();
    delay(1000);
    if(season<4){
      if(season==0 && spring==1){
        Copytoseason(0,CTLumparameter_four, CTLumparameter);
        CTtoparamter(CTLumparameter,parameter);
        delay(100);
        Blynk.virtualWrite(V22, 0); 
        spring=0; 
        season=4;    
      }
      else if(season==1 && summer==1){
        Copytoseason(1,CTLumparameter_four, CTLumparameter);
        CTtoparamter(CTLumparameter,parameter);
        delay(100);
        Blynk.virtualWrite(V23, 0); 
        summer=0; 
        season=4;      
      }
      else if(season==2 && autumn==1){
        Copytoseason(2,CTLumparameter_four, CTLumparameter);
        CTtoparamter(CTLumparameter,parameter);
        delay(100);
        Blynk.virtualWrite(V24, 0); 
        autumn=0;  
        season=4;    
      }
      else if(season==3 && winter==1){
        Copytoseason(3,CTLumparameter_four, CTLumparameter);
        CTtoparamter(CTLumparameter,parameter);
        delay(100);
        Blynk.virtualWrite(V25, 0);
        winter=0;   
        season=4;     
      }      
    }
    
    if(Fixkey==0){doparameter(parameter,Stop);}
   
    if(Fixkey==1){
      if(Modifykey==0){doVirtualparameter();}
      if(Modifykey==1){CTLumtunable(CTtunable,Lumtunable);}      
      if(Modifykey==2){
        h=hours;
        mi=0;
        runparameter(parameter);
       }
      } 
             
    if(Calibrationkey==1){Serial.println("Calibration");
         resetbar(2000);                                       //Fix button off
         Fixkey=0;             
         Blynk.virtualWrite(V2, "\n");
         
         terminal.println("Calibration");
         terminal.flush();
         Serial.println("444");      
         settinghrmin(parameter,Stop);
         Blynk.virtualWrite(V0, 0);
         Calibrationkey=0;
         }
    if(Showtimekey==1){Serial.println("Showtime");
         resetbar(2000);
         Fixkey=0; 
         Blynk.virtualWrite(V2, "\n");
         terminal.print("Showtime：");
         terminal.println(ShowTimeDelay);
         terminal.flush();  
         settingshow(ShowTimeDelay,parameter);} 
    if(resetwifi==1){
       Blynk.virtualWrite(V26, 0);
       resetwifi==0;
       delay(100);
       for (int i = 0; i < 512; ++i) {
          EEPROM.write(i, 0);
        }
       EEPROM.commit();
       delay(100);
       ESP.reset();
    }
}
 
 
//Functions used for saving WiFi credentials and to connect to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for WiFi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connection timed out, opening AP or Hotspot");
  return false;
}
 
void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}
 
void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan completed");
  if (n == 0)
    Serial.println("No WiFi Networks found");
  else
  {
    Serial.print(n);
    Serial.println(" Networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<p>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li style='font-size:20px;'>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
 
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</p>";
  delay(100);
  WiFi.softAP("ESP-NAME", "");
  Serial.println("Initializing_Wifi_accesspoint");
  launchWeb();
  Serial.println("over");
}


void createWebServer()
{
 {
    server.on("/", []() {
 
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html style='font-size:30px'><head >ESP8266 WiFi Connectivity Setup </head>";
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\" style='font-size:20px'></form>";
      content += "<p style='font-size:25px'>";
      content += ipStr;
      content += "</p><p style='font-size:20px'>";
      content += st;
      content += "</p><form method='get' action='setting' style='font-size:20px'><label>SSID: </label><input name='ssid' length=64><br><br><label>PASS: </label><input name='pass' length=64><br><br><input type=\"submit\" value=\"submit\" style='font-size:20px'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
 
      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });
 
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");
 
        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();
 
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);
 
    });
  } 
}

BLYNK_WRITE(V0) {  //Calibration指令
  //虛擬腳位 V0 的寫入函數
  //int value=param.asInt(); //以整數型態取得參數
  //String value=param.asDouble();  //以浮點數型態取得參數
  //String value=param.asFloat();  //以浮點數型態取得參數
  //String value=param.asStr();  //以字串型態取得參數
  //有些元件如搖桿會傳遞多的變數, 則 param 為一參數陣列
  Calibrationkey=param.asInt();  //以整數型態取得參數
  //int x=param[0].asInt();  //以整數型態取得參數
  //int y=param[1].asInt();  //以整數型態取得參數
  }
BLYNK_WRITE(V1) {  //Showtime 指令
  Showtimekey=param.asInt();  //以整數型態取得參數
  }
BLYNK_WRITE(V2) {  //Termianl 指令
   if (String("Who is online")== param.asStr()){terminal.println(Name);}
   if (Name == param.asStr()){                                          //顯示裝置的時間以及各色溫亮度。 
      terminal.println(Name);               
      displayClock();
      displayLighting();// 顯示時間
      }
   if (Name+String(" Showparameter") == param.asStr()){                 //顯示裝置在不同時間的色溫與亮度參數。
      terminaldisplayParameter(Name,parameter);
      }
   if (Name+String(" ShowCTLumparameter") == param.asStr()){                 //顯示裝置在不同時間的色溫與亮度參數。
      terminaldisplayCTLumParameter(Name,CTLumparameter);
      }                         
   if (Name+String(" CTLumparameter") == param.asStr()){
      Parameterkey=1;
      terminal.println("Now you can change the CTLumparameter:");
      }
   if (Parameterkey==1 && Name+String(" CTLumparameter") != param.asStr()){
      String Str=param.asStr();
      if(String("Nothing")==Str){
           terminal.println("Nothing happened!");
           terminaldisplayCTLumParameter(Name,CTLumparameter);          
           Parameterkey=0;}
      else if(String("Reset")==Str){           
           terminal.println(Name+" is Reset.");
           Copytoparameter(Reset,CTLumparameter);
           CTtoparamter(CTLumparameter,parameter); 
           terminaldisplayCTLumParameter(Name,CTLumparameter);
           Parameterkey=0;}
      else {
           Serial.println(Str);
           StrtoCTLumparameter(Str,CTLumparameter);
           CTtoparamter(CTLumparameter,parameter);       
           terminal.println("New CTLumparameter:");
           terminaldisplayCTLumParameter(Name,CTLumparameter); 
           Parameterkey=0;}
      }    
  terminal.flush(); //Ensure everything is sent
  }
BLYNK_WRITE(V3) {  //DIY Fix button
  Fixkey=param.asInt();  //以整數型態取得參數
  }  
BLYNK_WRITE(V4) {   
  ShowTimeDelay=param.asInt();  //以整數型態取得參數
  }
BLYNK_WRITE(V5) {   
  CTtunable=param.asInt();  //以整數型態取得參數
  Modifykey=1;
  }
BLYNK_WRITE(V6) {   
  Lumtunable=param.asInt();  //以整數型態取得參數
  Modifykey=1;
  }
BLYNK_WRITE(V13) {   
  HCT_V13=param.asInt();  //以整數型態取得參數
  Modifykey=0;
  }      
BLYNK_WRITE(V14) {   
  MCT_V14=param.asInt();  //以整數型態取得參數
  Modifykey=0;
  }  
BLYNK_WRITE(V12) {   
  LCT_V12=param.asInt();  //以整數型態取得參數
  Modifykey=0;
  }
BLYNK_WRITE(V21) {   
  SLCT_V21=param.asInt();  //以整數型態取得參數
  Modifykey=0;
  }
BLYNK_WRITE(V15) {   
//  Modifykey=2;
  hours=param.asInt();
  minutes=(param.asFloat()-hours)*60;
  }     
BLYNK_WRITE(V26) {  
  resetwifi=param.asInt();
}
