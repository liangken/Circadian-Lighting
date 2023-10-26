
void WIFIConnect(char *a, char *b){      
   WiFi.begin(a, b);      
   while (WiFi.status() != WL_CONNECTED) {  //不斷嚐試連接
     digitalWrite(2, LOW);
     delay(500);
     digitalWrite(2, HIGH);
     delay(500);
     Serial.println(".");   
   }
   Serial.print("WIFI: ");
   Serial.println(WIFIssid);         //顯示WIFI名稱
   Serial.print(Name);
   Serial.println(" connected!");  //已連接
//   Serial.print("IP: ");
//   Serial.println(WiFi.localIP());  //顯示IP位址
  
   terminal.clear();   
   terminal.print("WIFI: ");
   terminal.println(WIFIssid);         //顯示WIFI名稱
   terminal.print(Name);
   terminal.println(" connected!");  //已連接
//   terminal.print("IP: ");
//   terminal.println(WiFi.localIP());  //顯示IP位址
   terminal.flush(); 
  }
