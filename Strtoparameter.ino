void Strtoparameter(String valueString, int valueArray[][5]){
     int i=0;
     int j=0;
     int temp=0;
     int pos;
     do {
         pos=valueString.indexOf(',');                                           //數出字串中','的位置，找不到則回傳-1
         if(pos != -1){                                
            valueArray[j][i] = valueString.substring(0, pos).toInt();
            valueString = valueString.substring(pos+1, valueString.length());
            i++;
           }
         else{
            if(valueString.length()>0) {
              valueArray[j][i++] = valueString.toInt();              
              }  
            }
          if(i%5==0){i=0;j++;}  
         }while (pos >=0);
     while(temp<=(606-(i+1)*(j+1))){      //606為矩陣總數
         valueArray[j][i++] = 0;         
         if(i%5==0){i=0;j++;}
         temp++;} 
                           
}

void StrtoCTLumparameter(String valueString, int valueArray[][3]){
     int i=0;
     int j=0;
     int temp=0;
     int pos;
     do {
         pos=valueString.indexOf(',');                                           //數出字串中','的位置，找不到則回傳-1
         if(pos != -1){                                
            valueArray[j][i] = valueString.substring(0, pos).toInt();
            valueString = valueString.substring(pos+1, valueString.length());
            i++;
           }
         else{
            if(valueString.length()>0) {
              valueArray[j][i++] = valueString.toInt();              
              }  
            }
          if(i%3==0){i=0;j++;}  
         }while (pos >=0);
     while(temp<=(100-(i+1)*(j+1))){      //100為矩陣總數
         valueArray[j][i++] = 0;         
         if(i%3==0){i=0;j++;}
         temp++;} 
                           
}

void Copytoparameter(int valueArray1[][3], int valueArray2[][3]){
  for (int i=0;i<75;i++){
      for(int j=0; j<3;j++){valueArray2[i][j]=valueArray1[i][j];} 
       
    }  
  }
void Copytoseason(int k, int CTLumparameter_four[][24][3], int CTLumparameter[ ][3]){
  for (int i=0;i<24;i++){
      for(int j=0; j<3;j++){CTLumparameter[i][j]=CTLumparameter_four[k][i][j];}    
    }  
  }
