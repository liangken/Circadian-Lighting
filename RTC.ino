

                                                   
String timeString(){
  char c[20];        // long enough to hold complete string
  sprintf(c, "%02d:%02d:%02d",hour(),minute(),second()); 
  String currentTime= String(c); 
  return currentTime;
}

String dateString(){
  char c[20];        // long enough to hold complete string
  sprintf(c, "%4d/%02d/%02d",year(),month(),day()); 
  String currentDate= String(c); 
  return currentDate;
}

void getTime(){
    y=year();
    m=month();
    d=day();
    h=hour();
    mi=minute();
    s=0;
//    displayClock(); 
  }


void displayClock(){                                                         // 顯示時間
    Serial.print(y);
    Serial.print("/");
    Serial.print(m);
    Serial.print("/");
    Serial.print(d);
    Serial.print(" ");
//    Serial.print(" ( ");
//    Serial.print(w);
//    Serial.print(" ) "); 
    Serial.print(h);
    Serial.print(":");
    Serial.print(mi);
    Serial.print(":");
    Serial.println(second());

    Blynk.virtualWrite(V2, "\n");           
    terminal.print(h);
    terminal.print(":");
    terminal.print(mi);
    terminal.print(":");
    terminal.println(second());
    terminal.flush();
}




/*
BLYNK_READ(V1) {  //虛擬腳位 V0 的讀取函數
  Blynk.virtualWrite(V1, Showtime);  //將參數 Calibration 傳送給虛擬腳位 V0
  }  
*/     
