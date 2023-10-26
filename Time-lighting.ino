float HL=0;
float ML=0;
float LL=0;
float SLL=0;
char charHL[4]="";
char charML[4]="";
char charLL[4]="";
char charSLL[4]="";
void secSLCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s>=startime and s<endtime){
      SLL=initialuminance+(s-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*      Serial.print("LL ");
      Serial.println(LL);*/
      analogWrite(SLCT,SLL);
      } 
  }
void secLCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s>=startime and s<endtime){
      LL=initialuminance+(s-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*      Serial.print("LL ");
      Serial.println(LL);*/
      analogWrite(LCT,LL);
      } 
  }
void secMCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s>=startime and s<endtime){
      ML=initialuminance+(s-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*      Serial.print("ML ");
      Serial.println(ML);*/
      analogWrite(MCT,ML);
      } 
  }
void secHCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s>=startime and s<endtime){
      HL=initialuminance+(s-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*      Serial.print("HL ");
      Serial.println(HL);*/
      analogWrite(HCT,HL);
      } 
  }
void minsecSLCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(mi>=startime and mi<endtime){
      secSLCT(0,60,initialuminance+(mi-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void minsecLCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(mi>=startime and mi<endtime){
      secLCT(0,60,initialuminance+(mi-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void minsecMCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(mi>=startime and mi<endtime){
      secMCT(0,60,initialuminance+(mi-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void minsecHCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(mi>=startime and mi<endtime){
      secHCT(0,60,initialuminance+(mi-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void minSLCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s==0){
        if(mi>=startime and mi<endtime){
          SLL=initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*          Serial.print("ML ");
          Serial.println(ML);*/
          delay(10);
          analogWrite(SLCT,SLL);
        } 
     }
  }

void minLCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s==0){
        if(mi>=startime and mi<endtime){
          LL=initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*          Serial.print("h ");
          Serial.print(h);
          Serial.print(" min ");
          Serial.print(mi);
          Serial.print(" LL ");
          Serial.println(LL);*/
          delay(10);
          analogWrite(LCT,LL);
        } 
     }
  }
void minMCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s==0){
        if(mi>=startime and mi<endtime){
          ML=initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*          Serial.print("ML ");
          Serial.println(ML);*/
          delay(10);
          analogWrite(MCT,ML);
        } 
     }
  }
void minHCT(float startime, float endtime, float initialuminance, float finaluminance){
     if(s==0){
        if(mi>=startime and mi<endtime){
          HL=initialuminance+(mi-startime+1)*(finaluminance-initialuminance)/(endtime-startime);
/*          Serial.print("HL ");
          Serial.println(HL);*/
          delay(10);
          analogWrite(HCT,HL);
      } 
     }
  }
void hrminSLCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(h>=startime and h<endtime){
      minSLCT(0,60,initialuminance+(h-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(h-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }

void hrminLCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(h>=startime and h<endtime){
      minLCT(0,60,initialuminance+(h-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(h-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void hrminMCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(h>=startime and h<endtime){
      minMCT(0,60,initialuminance+(h-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(h-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }
void hrminHCT(float startime, float endtime, float initialuminance, float finaluminance){
    if(h>=startime and h<endtime){
      minHCT(0,60,initialuminance+(h-startime)*(finaluminance-initialuminance)/(endtime-startime),initialuminance+(h-startime+1)*(finaluminance-initialuminance)/(endtime-startime));
      } 
  }

void settingsec(){
   getTime(); 
   int ss=s;
   for(s=0;s<=ss;s++){ 
        secSLCT(0,7,0,255);
        secLCT(7,14,0,255);
        secMCT(14,22,0,255);
        secHCT(22,30,0,255);
        secHCT(30,37,255,0);
        secMCT(37,44,255,0);
        secLCT(44,52,255,0);    
        secSLCT(52,60,255,0);
    }
  }    
void settingminsec(){
  getTime();
  int mii=mi;
  int ss=s;
  int x=60;
  for(mi=0;mi<=mii;mi++){
    if(mi==mii){getTime();x=s;}
    for(s=0;s<=x;s++){
        minsecSLCT(0,7,0,255);
        minsecLCT(7,14,0,255);
        minsecMCT(14,22,0,255);
        minsecHCT(22,30,0,255);
        minsecHCT(30,37,255,0);
        minsecMCT(37,44,255,0);
        minsecLCT(44,52,255,0);    
        minsecSLCT(52,60,255,0);   
      }
    }
  }    
void settinghrmin(int a[][5], int b[][7]){
  analogWrite(HCT,0);
  analogWrite(MCT,0);
  analogWrite(LCT,0);
  analogWrite(SLCT,0);
  displayClock();
  int hrr=h;
  int mii=mi;
  int x=60;
  s=0;
  for(h=0;h<=hrr;h++){
    if(h==hrr){x=mi;s=0;}
    for(mi=0;mi<=x;mi++){
      doparameter(a,b);
      }
    Blynk.run();  
    }
    h=hrr;
    mi=mii;  
  }  
void settingshow(int delaytime, int a[][5]){
    analogWrite(HCT,0);
    analogWrite(MCT,0);
    analogWrite(LCT,0);
    analogWrite(SLCT,0);
    int hrr=h;
    int mii=mi;
    s=0;
    for(h=0;h<=24;h++){
      Blynk.run(); 
    for(mi=0;mi<=60;mi++){
      delay(delaytime);
      runparameter(a);
      }
    }
     h=hrr;
     mi=mii; 
}
void runparameter(int a[][5]){  
    for(int i=0;i<99;i++){
            if(a[i][0]==1){hrminHCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==2){hrminMCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==3){hrminLCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==4){hrminSLCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
    }
}
void doparameter(int a[][5],int b[][7]){
    for(int i=0;i<99;i++){
       if(b[i][0]==w and h>=b[i][1] and h<b[i][2]){
            analogWrite(HCT,b[i][3]);
            analogWrite(MCT,b[i][4]);
            analogWrite(LCT,b[i][5]);
            analogWrite(SLCT,b[i][6]);
            break;}
            if(a[i][0]==1){hrminHCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==2){hrminMCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==3){hrminLCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            if(a[i][0]==4){hrminSLCT(a[i][1],a[i][2],a[i][3],a[i][4]);}
            
    }
    
}
void doVirtualparameter(){
        analogWrite(HCT,HCT_V13);
        analogWrite(MCT,MCT_V14);
        analogWrite(LCT,LCT_V12); 
        analogWrite(SLCT,SLCT_V21);
}
  
void displayParameter(int a[][5]){
       Serial.println("");
    for(int i=0;i<99;i++){
       if(a[i][0]==1){
          Serial.print("hrminHCT(");
          Serial.print(a[i][1]);Serial.print(",");
          Serial.print(a[i][2]);Serial.print(",");
          Serial.print(a[i][3]);Serial.print(",");
          Serial.print(a[i][4]);Serial.println(")");
          Serial.print(a[i][5]);Serial.println(")");}
       if(a[i][0]==2){
          Serial.print("hrminMCT(");
          Serial.print(a[i][1]);Serial.print(",");
          Serial.print(a[i][2]);Serial.print(",");
          Serial.print(a[i][3]);Serial.print(",");
          Serial.print(a[i][4]);Serial.println(")");
          Serial.print(a[i][5]);Serial.println(")");}  
       if(a[i][0]==3){
          Serial.print("hrminLCT(");
          Serial.print(a[i][1]);Serial.print(",");
          Serial.print(a[i][2]);Serial.print(",");
          Serial.print(a[i][3]);Serial.print(",");
          Serial.print(a[i][4]);Serial.println(")");
          Serial.print(a[i][5]);Serial.println(")");}    
       if(a[i][0]==4){
          Serial.print("hrminSLCT(");
          Serial.print(a[i][1]);Serial.print(",");
          Serial.print(a[i][2]);Serial.print(",");
          Serial.print(a[i][3]);Serial.print(",");
          Serial.print(a[i][4]);Serial.println(")");
          Serial.print(a[i][5]);Serial.println(")");}         
    }
       Serial.println("");
  }
void terminaldisplayParameter(String Name,int a[][5]){
       terminal.println("");
       terminal.println(Name);
    for(int i=0;i<99;i++){
       if(a[i][0]==1){
          terminal.print("hrminHCT(");
          terminal.print(a[i][1]);terminal.print(",");
          terminal.print(a[i][2]);terminal.print(",");
          terminal.print(a[i][3]);terminal.print(",");
          terminal.print(a[i][4]);terminal.println(",");
          terminal.print(a[i][5]);terminal.println(")");}
       if(a[i][0]==2){
          terminal.print("hrminMCT(");
          terminal.print(a[i][1]);terminal.print(",");
          terminal.print(a[i][2]);terminal.print(",");
          terminal.print(a[i][3]);terminal.print(",");
          terminal.print(a[i][4]);terminal.println(",");
          terminal.print(a[i][5]);terminal.println(")");}  
       if(a[i][0]==3){
          terminal.print("hrminLCT(");
          terminal.print(a[i][1]);terminal.print(",");
          terminal.print(a[i][2]);terminal.print(",");
          terminal.print(a[i][3]);terminal.print(",");
          terminal.print(a[i][4]);terminal.println(",");
          terminal.print(a[i][5]);terminal.println(")");} 
        if(a[i][0]==4){
          terminal.print("hrminSLCT(");
          terminal.print(a[i][1]);terminal.print(",");
          terminal.print(a[i][2]);terminal.print(",");
          terminal.print(a[i][3]);terminal.print(",");
          terminal.print(a[i][4]);terminal.println(",");
          terminal.print(a[i][5]);terminal.println(")");}  
    }
       terminal.println("");
  }
void terminaldisplayCTLumParameter(String Name,int a[][3]){
       terminal.println("");
       terminal.println(Name);
    for(int i=0;i<24;i++){
       if(a[i][0]!=0){
          terminal.print("(");
          terminal.print(a[i][0]);terminal.print(",");
          terminal.print(a[i][1]);terminal.print(",");
          terminal.print(a[i][2]);terminal.println(")");}
    }
       terminal.println("");
  }
  
void displayLighting(){                                                         // 顯示現在亮度
    Serial.println(Name);
    Serial.print("HL:");
    Serial.print(int(HL));
    Serial.print("  ML:");
    Serial.print(int(ML));
    Serial.print("  LL:");
    Serial.println(int(LL));
    Serial.print("  SLL:");
    Serial.println(int(SLL));

    Blynk.virtualWrite(V2, "");  
    terminal.print("HL:");
    terminal.print(int(HL));
    terminal.print("  ML:");
    terminal.print(int(ML));
    terminal.print("  LL:");
    terminal.println(int(LL));
    terminal.print("  SLL:");
    terminal.println(int(SLL));
    terminal.flush();
}
