// C++ code
//

#include <string.h>

int 	val_temp =0;
int 	val_oxygene=0;
int 	val_ph;
int 	val_turb;	

int 	temp_sensor=A5;
int 	ph_sensor=A4;
int 	oxygen_sensor=A3;
int 	turbedite_sensor=A2;

int seuil_temp=24;// en °C
int seuil_ph=10; 
int seuil_oxugene=8; //mg/l
int seuil_turbedite=50;//(ppm particules par million) 

void setup()
{
  pinMode(temp_sensor,INPUT);
  pinMode(ph_sensor,INPUT);
  pinMode(oxygen_sensor,INPUT);
  pinMode(turbedite_sensor,INPUT);

  Serial.begin(9600);
}

void loop()
{
  char buffer4[4];
  char buffer [sizeof(int)*8+1];
  char data[100];
  
  val_temp=analogRead(temp_sensor);
  val_ph=analogRead(ph_sensor);
  val_oxygene=analogRead(oxygen_sensor);
  val_turb=analogRead(turbedite_sensor);
  //|| val_temp<5
  if (val_temp>seuil_temp ){
    itoa(val_temp,buffer,10); // convertion en string
      //Serial.println(val_temp);
    strcpy(buffer4,"");
    int tb=strlen(buffer); //ajout des 0 pour avoir 4 caractere dans le buffer
    for (int i=0;i<4-tb;i++){
      strcat(buffer4,"0");
    }
    strcat(buffer4,buffer);
    
  	strcpy(data, "1,"); //concatenation (1 pour temperature)
  	strcat(data, buffer4);
    Serial.write(data); //send data
  }
  //|| val_ph<7
  else if (val_ph>seuil_ph ){
    itoa(val_ph,buffer,10); // convertion en string
    
    strcpy(buffer4,"");
    int tb=strlen(buffer); //ajout des 0 pour avoir 4 caractere dans le buffer
    for (int i=0;i<4-tb;i++){
      strcat(buffer4,"0");
    }
    strcat(buffer4,buffer);
    
  	strcpy(data, "2,"); //concatenation (1 pour temperature)
  	strcat(data, buffer4);  
    Serial.write(data); //send data
  }
  else if (val_oxygene>seuil_oxugene){
    itoa(val_oxygene,buffer,10); // convertion en string
    
    strcpy(buffer4,"");
    int tb=strlen(buffer); //ajout des 0 pour avoir 4 caractere dans le buffer
    for (int i=0;i<4-tb;i++){
      strcat(buffer4,"0");
    }
    strcat(buffer4,buffer);
    
  	strcpy(data, "3,"); //concatenation (1 pour temperature)
  	strcat(data, buffer4);  
    Serial.write(data); //send data
  }
  else if (val_turb>seuil_turbedite){
    itoa(val_turb,buffer,10); // convertion en string
    
    strcpy(buffer4,"");
    int tb=strlen(buffer); //ajout des 0 pour avoir 4 caractere dans le buffer
    for (int i=0;i<4-tb;i++){
      strcat(buffer4,"0");
    }
    strcat(buffer4,buffer);
    
  	strcpy(data, "4,"); //concatenation (1 pour temperature)
  	strcat(data, buffer4);  
    Serial.write(data); //send data
  }
  else {
    Serial.write("0,0000"); //send data
  }
  //Serial.println(data);
  delay(1000); // Delay a little bit to improve simulation performance
}




