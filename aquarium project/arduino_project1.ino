// C++ code
// Slave Arduino

#include<Adafruit_LiquidCrystal.h>
#include <time.h>
#include <Servo.h>

/////////////////TIME var declaration

unsigned long previousMil = 0;
unsigned long currentMil =0;
const long period = 3000;

String s;
int days=0;
int day=28;
int month=11;
int year=2022;
int hour=19;
int min=56;
int sec=0;

////////////////
Servo servo_8;
char 	data[10]; //String data
const int buzzer = 9; // alarm input 
Adafruit_LiquidCrystal lcd_1(0);
unsigned long myTime;
void setup()
{
  lcd_1.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  servo_8.attach(8);
  Serial.begin(9600);

}


void loop()
{
  
  
  ///////////////////TIME SETUP////////////
    if(sec==60){
    min+=1;
    sec=0;
    if(min==60){
      hour+=1;
      min=0;
      if(hour==24){
        day+=1;
        days+=1;
        hour=0;
        if(day==31){
          month+=1;
          day=1;
          if(month==13){
            year+=1;
            month=1;
          }  
        }
      }
    }
  }
  
  currentMil = millis();

  if (currentMil - previousMil >= period) {
    previousMil = currentMil;
  }
    previousMil = currentMil;
  sec+=1;
  
 Serial.println(hour);
  Serial.println(":");
  Serial.println(min);
  Serial.println(":");
  Serial.println(sec);
///////////////////END TIME SETUP///////////////////

  char val_capt[4]; // valeur du capteur
  char sensor[1]; // le capteur 1 pour temp; 2 pour pH, 3 pour oxyg et 4 pour tubedité
  char Message_Affiche[100];// Message à afficher
 
  Serial.readBytes(data,6); //Read data
  Serial.println(data);

  char *ch = strtok(data, ","); // Split data
  if (ch != NULL) {
      strcpy(sensor,ch);
      ch = strtok(NULL, ",");
  }
  
  lcd_1.clear();
  if (strcmp(sensor, "0")==0){
    if (ch != NULL) {
          strcpy(val_capt,ch);
          ch = strtok(NULL, ",");
      }
        if(hour==19 && min==56 && sec==1){
        servo_8.write(180);

        //delay(4000);
        servo_8.write(0);
        //delay(4000);
    }
      strcat(Message_Affiche,"Tt est conforme");

  }
  if (strcmp(sensor, "1")==0){
      if (ch != NULL) {
          strcpy(val_capt,ch);
          ch = strtok(NULL, ",");
      }
      strcat(Message_Affiche,"Alert Temperature:");
  tone(buzzer, 1000,2000); // Send 1KHz sound signal...

  }
  if (strcmp(sensor, "2")==0){
      if (ch != NULL) {
          strcpy(val_capt,ch);
          ch = strtok(NULL, ",");
      }
      strcat(Message_Affiche,"Alert pH:");
  tone(buzzer, 1000,2000); // Send 1KHz sound signal...
 
  }
  if (strcmp(sensor, "3")==0){
      if (ch != NULL) {
          strcpy(val_capt,ch);
          ch = strtok(NULL, ",");
      }
      strcat(Message_Affiche,"Alert oxygene:");
  tone(buzzer, 1000,2000); // Send 1KHz sound signal...

  }
  if (strcmp(sensor, "4")==0){
      if (ch != NULL) {
          strcpy(val_capt,ch);
          ch = strtok(NULL, ",");
      }
      strcat(Message_Affiche,"Alert turbedite:");
  tone(buzzer, 1000,2000); // Send 1KHz sound signal...

  delay(1000);    
  }
  
  lcd_1.print(Message_Affiche);
  lcd_1.setCursor(0,1);
  lcd_1.print(val_capt);
  delay(1000); 
  
  
}








