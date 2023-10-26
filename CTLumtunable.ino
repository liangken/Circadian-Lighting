//newest version
int Hcolortemperature=6000;//仍須確認
int Mcolortemperature=4500;
int Lcolortemperature=2500;
int SLcolortemperature=1700;
float LumRatioH=0.1;//仍須修改
float LumRatioM=0.1;
float LumRatioL=0.1;
float LumRatioSL=0.05;
int HMcolortemperature=(Hcolortemperature*LumRatioH+Mcolortemperature*LumRatioM)/(LumRatioH+LumRatioM);
int HMLcolortemperature=(Hcolortemperature*LumRatioH+Mcolortemperature*LumRatioM+Lcolortemperature*LumRatioL)/(LumRatioH+LumRatioM+LumRatioL);
int MLcolortemperature=(Mcolortemperature*LumRatioM+Lcolortemperature*LumRatioL)/(LumRatioM+LumRatioL);
int MLSLcolortemperature=(Mcolortemperature*LumRatioM+Lcolortemperature*LumRatioL+SLcolortemperature*LumRatioSL)/(LumRatioSL+LumRatioM+LumRatioL);
int LSLcolortemperature=(Lcolortemperature*LumRatioL+SLcolortemperature*LumRatioSL)/(LumRatioSL+LumRatioL);
float MaxLum=0;
float H=0;
float M=0;
float L=0;
float SL=0;
int Lumtemp1;
int Lumtemp2;

void CTLumtunable(int CT, int Lum){
    CTLumcalculator(CT,Lum);
    Blynk.virtualWrite(V7,int(MaxLum));    
    if(Lum>MaxLum){                  //亮度調整條大於最大亮度時
      if(Lum==Lumtemp1){               //亮度調整條未改變(僅改變色溫調整條)
         Lum=Lumtemp2;}                  //此時亮度等於亮度調整數值2(先前最大亮度)
      else{                            //亮度調整條改變
         Lumtemp1=Lum;                   //紀錄 APP亮度調整條的數值1
         Lum=MaxLum;                     //此時亮度等於最大亮度
         Lumtemp2=MaxLum;}               //紀錄亮度調整條數值2為最大亮度
     if(Lumtemp2>MaxLum){Lumtemp2=MaxLum;}//亮度調整條數值2大於最大亮度，其數值改為新最大亮度
      Blynk.virtualWrite(V6,int(Lum));
      }
    HCT_V13=H*1000*Lum/MaxLum;
    MCT_V14=M*1000*Lum/MaxLum;
    LCT_V12=L*1000*Lum/MaxLum;
    SLCT_V21=SL*1000*Lum/MaxLum;
/*  Serial.print("MaxLum：");
    Serial.print(int(MaxLum));
    Serial.print("% ");
    Serial.print(CT);
    Serial.print(" HL：");
    Serial.print(int(HCT_V13));
    Serial.print(" ML：");
    Serial.print(int(MCT_V14));
    Serial.print(" LL：");
    Serial.println(int(LCT_V12));*/
    Blynk.virtualWrite(V13,HCT_V13);
    Blynk.virtualWrite(V12,MCT_V14);
    Blynk.virtualWrite(V14,LCT_V12);
    Blynk.virtualWrite(V21,SLCT_V21);
    doVirtualparameter();  
}

void CTtoparamter(int CTparameter[][3], int parameter[][5]){
     for(int i=0;i<96;i++){
       
       CTLumcalculator(CTparameter[i/4][1],CTparameter[i/4][2]);
       if(CTparameter[i/4][2]>MaxLum){CTparameter[i/4][2]=MaxLum;}
       if(i%4==0){
         parameter[i][0]=1;
         parameter[i][1]=CTparameter[i/4][0];
         parameter[i][2]=CTparameter[(i/4)+1][0];
         if(H<0){
           H=0;
         }  
         parameter[i][3]=H*1000*CTparameter[i/4][2]/MaxLum;
         parameter[i-4][4]=H*1000*CTparameter[i/4][2]/MaxLum;  
       }
       if(i%4==1){
         parameter[i][0]=2;
         parameter[i][1]=CTparameter[i/4][0];
         parameter[i][2]=CTparameter[(i/4)+1][0];
         if(M<0){
           M=0;
         }  
         parameter[i][3]=M*1000*CTparameter[i/4][2]/MaxLum;
         parameter[i-4][4]=M*1000*CTparameter[i/4][2]/MaxLum;
       }  
       if(i%4==2){
         parameter[i][0]=3;
         parameter[i][1]=CTparameter[i/4][0];
         parameter[i][2]=CTparameter[(i/4)+1][0];
         if(L<0){
           L=0;
         }  
         parameter[i][3]=L*1000*CTparameter[i/4][2]/MaxLum;
         parameter[i-4][4]=L*1000*CTparameter[i/4][2]/MaxLum;     
       } 
       if(i%4==3){
         parameter[i][0]=4;
         parameter[i][1]=CTparameter[i/4][0];
         parameter[i][2]=CTparameter[(i/4)+1][0];
         if(SL<0){
           SL=0;
         }  
         parameter[i][3]=SL*1000*CTparameter[i/4][2]/MaxLum;
         parameter[i-4][4]=SL*1000*CTparameter[i/4][2]/MaxLum;
       }                            
       if(CTparameter[i/4][0]==0){
            parameter[i-1][0]=0;       
            parameter[i-2][0]=0;
            parameter[i-3][0]=0;
            parameter[i-4][0]=0;
            parameter[i][0]=0;
            parameter[i+1][0]=0;
            parameter[i+2][0]=0;
            parameter[i+3][0]=0;}
     }
    
}

void CTLumcalculator(int CT, int Lum){
/*  Serial.println(CT);
  Serial.print(Lum);
  Serial.println("%");*/
  if(CT==0){L=0;H=0;M=0;MaxLum=0;}
  if(SLcolortemperature<=CT and CT<LSLcolortemperature){
    SL=1;
    H=0;
    M=0;
    L=LumRatioSL*(SLcolortemperature-CT)/(LumRatioL*(CT-Lcolortemperature));
    MaxLum=LumRatioSL*(SLcolortemperature-Lcolortemperature)*100/(CT-Lcolortemperature); 
  }
  if(LSLcolortemperature<=CT and CT<MLSLcolortemperature){
    SL=1;
    L=1;
    H=0;
    M=LumRatioSL*(SLcolortemperature-CT)+LumRatioL*(Lcolortemperature-CT)/(LumRatioM*(CT-Mcolortemperature));
    MaxLum=(LumRatioSL*(SLcolortemperature-Mcolortemperature)+LumRatioL*(Lcolortemperature-Mcolortemperature))*100/(CT-Mcolortemperature);     
    }  
  if(MLSLcolortemperature<=CT and CT<MLcolortemperature){
    L=1;
    M=1;
    H=0;   
    SL=(LumRatioL*(Lcolortemperature-CT)+LumRatioM*(Mcolortemperature-CT))/(LumRatioSL*(CT-SLcolortemperature));
    MaxLum=(LumRatioL*(Lcolortemperature-SLcolortemperature)+LumRatioM*(Mcolortemperature-SLcolortemperature))*100/(CT-SLcolortemperature);    
    }
  if(MLcolortemperature<=CT and CT<HMLcolortemperature){
    SL=0;
    L=1;
    M=1;
    H=(LumRatioL*(Lcolortemperature-CT)+LumRatioM*(Mcolortemperature-CT))/(LumRatioH*(CT-Hcolortemperature));;
    MaxLum=(LumRatioL*(Lcolortemperature-Hcolortemperature)+LumRatioM*(Mcolortemperature-Hcolortemperature))*100/(CT-Hcolortemperature);    
  }
  if(HMLcolortemperature<=CT and CT<HMcolortemperature){
    SL=0;
    H=1;
    M=1;    
    L=(LumRatioM*(Mcolortemperature-CT)+LumRatioH*(Hcolortemperature-CT))/(LumRatioL*(CT-Lcolortemperature));
    MaxLum=(LumRatioM*(Mcolortemperature-Lcolortemperature)+LumRatioH*(Hcolortemperature-Lcolortemperature))*100/(CT-Lcolortemperature);    
    }              
  if(HMcolortemperature<=CT and CT<=Hcolortemperature){
    SL=0;
    L=0;
    H=1;
    M=LumRatioH*(Hcolortemperature-CT)/(LumRatioM*(CT-Mcolortemperature));
    MaxLum=LumRatioH*(Hcolortemperature-Mcolortemperature)*100/(CT-Mcolortemperature);    
    }
}

void CTcalculator(){
   Serial.println(LSLcolortemperature);
   Serial.println(MLSLcolortemperature);
   Serial.println(MLcolortemperature);
   Serial.println(HMLcolortemperature);
   Serial.println(HMcolortemperature);
   }
void resetbar(int CTtunable){
  Blynk.virtualWrite(V3,0);   
  Blynk.virtualWrite(V13,0);
  Blynk.virtualWrite(V12,0);
  Blynk.virtualWrite(V14,0);
  Blynk.virtualWrite(V6,0);
  Blynk.virtualWrite(V5,CTtunable);
  Blynk.virtualWrite(V15,0);  
  }
BLYNK_WRITE(V9) {   
  LumRatioH=param.asInt()*0.01;  //以整數型態取得參數
  }
BLYNK_WRITE(V10) {   
  LumRatioM=param.asInt()*0.01;  //以整數型態取得參數
  }
BLYNK_WRITE(V11) {   
  LumRatioL=param.asInt()*0.01;  //以整數型態取得參數
  }
BLYNK_WRITE(V19) {   
  LumRatioSL=param.asInt()*0.01;  //以整數型態取得參數
  }
BLYNK_WRITE(V16) {   
  Hcolortemperature=param.asInt();  //以整數型態取得參數
  }
BLYNK_WRITE(V17) {   
  Mcolortemperature=param.asInt();  //以整數型態取得參數
  }
BLYNK_WRITE(V18) {   
  Lcolortemperature=param.asInt();  //以整數型態取得參數
  }     
BLYNK_WRITE(V20) {   
  SLcolortemperature=param.asInt();  //以整數型態取得參數
  }     
BLYNK_WRITE(V22) { 
  spring=param.asInt();  
  season=0;  //以整數型態取得參數
  
  }     
BLYNK_WRITE(V23) { 
  summer=param.asInt(); 
  season=1;  //以整數型態取得參數
  
  }     
BLYNK_WRITE(V24) {
  autumn=param.asInt();    
  season=2;  //以整數型態取得參數
  
  }     
BLYNK_WRITE(V25) {  
  winter=param.asInt();  
  season=3;  //以整數型態取得參數
 
  }     
