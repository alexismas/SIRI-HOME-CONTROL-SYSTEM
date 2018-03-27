#include <Wire.h>

#define SLAVE_ADDRESS 0x12

int dataReceived = 0;
bool irdetect = false;
int detect;
int envoi ;
int pass = 0;



double in_min = 0.55;
double in_max = 1;
double out_min = 0;
double out_max = 50;
double temp;
int lumi;




void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
    pinMode(3, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, INPUT);

    

}

void loop() {
    delay(100);
 
   temp = analogRead(0);
    
  temp = temp * 5/1024; // value to Volts
  //Serial.print(temp);
  //Serial.print(" V = ");
  temp = (temp - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 // Serial.print(temp);
  //Serial.println(" ° ");

   lumi = analogRead(2);
  //Serial.println(lumi);
  lumi = map(lumi, 250,800,255,0);
  


  
              
 detect = analogRead(1);

 if( detect == LOW)
 {
  irdetect = true;
 }
 else
 {
  irdetect = false;
  pass = 0;
 }

 

  if(dataReceived ==0) // initialisation
  {
    digitalWrite(3, LOW);
    digitalWrite(9, LOW);
    digitalWrite(5, LOW);
     digitalWrite(6, HIGH);
     
  }
  
  if(lumi > 200) // vérification du capteur de luminosité
  {
    soleil();
  }

  if(lumi<200)
  {
    analogWrite(3, 0); // 
    analogWrite(9, 0); // 
    if(dataReceived ==1)
    {
      digitalWrite(3, HIGH); // led 1
    }
    if(dataReceived ==2)
    {
      digitalWrite(3, LOW); // led1
    }
    if(dataReceived ==3)
    {
      digitalWrite(9, HIGH); // led2
    }
    if(dataReceived ==4)
    {
      digitalWrite(9, LOW); //led2
    }
    
   }
  

  
    if(dataReceived ==5)
  {
    digitalWrite(5, HIGH); // door open

    digitalWrite(6, LOW); //
  }
  if(dataReceived ==6)
  {
     digitalWrite(6, HIGH);//door close
    digitalWrite(5, LOW); 
  }
}

void receiveData(int byteCount){
    while(Wire.available()) {
        dataReceived = Wire.read();
        Serial.print("Donnee recue : ");
        Serial.println(dataReceived);
    }
}

void sendData(){
    //int envoi = dataReceived + 1;
  
    //envoi = 20;
    envoi = (int)temp;
    
    if((irdetect)&&(pass == 0))
    {
      irdetect=false;
      pass = 1;
      
      envoi = 200; // some one inside
    }
    Serial.print("envoi : ");
     Serial.println(envoi);
    Wire.write(envoi);
   
}

void soleil()
{
   analogWrite(3,lumi);
  analogWrite(9,lumi);
  
}

