//soner 1 declear
const int soner1_VccPin = 13;
const int soner1_trigger = 12;
const int soner1_echo = 11;
const int soner1_GroundPin = 10;

//soner 2 declear
const int soner2_VccPin = 7;
const int soner2_trigger = 6;
const int soner2_echo = 5;
const int soner2_GroundPin = 4;

//Buzz declear
const int Buzz_vcc = 3;       // for soner 1
const int Buzz_gnd = 2;
const int Buzz2_vcc = A1;     // for soner 2
const int Buzz2_gnd = A0;
const int Buzz3_vcc = 8;     // for moscirisor
const int Buzz3_gnd = 9;

int soner1_dist;
int soner1_time_taken;

int soner2_dist;
int soner2_time_taken;

int msensor = A2; // moisture sensor is connected with the analog pin A1 of the Arduino
int msensor_vcc = A4; 
int msensor_gnd = A3; 
int msvalue = 0; // moisture sensor value 
boolean flag = false;


void soner1_calculate_distance(int soner1_trigger, int soner1_echo)
{
  digitalWrite(soner1_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(soner1_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(soner1_trigger, LOW);
  
  soner1_time_taken = pulseIn(soner1_echo, HIGH);
  soner1_dist= soner1_time_taken*0.034/2;
  if (soner1_dist>300)
  soner1_dist=300;
}

void soner2_calculate_distance(int soner2_trigger, int soner2_echo)
{
  digitalWrite(soner2_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(soner2_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(soner2_trigger, LOW);
  
  soner2_time_taken = pulseIn(soner2_echo, HIGH);
  soner2_dist= soner2_time_taken*0.034/2;
  //if (soner2_dist>300)
  //soner1_dist=300;
}


void setup() {
  Serial.begin(9600);

  // Buzzer bip power
  pinMode(Buzz_vcc,OUTPUT);
  digitalWrite(Buzz_vcc,LOW);
  pinMode(Buzz_gnd,OUTPUT);
  digitalWrite(Buzz_gnd,LOW);

  pinMode(Buzz2_vcc,OUTPUT);
  digitalWrite(Buzz2_vcc,LOW);
  pinMode(Buzz2_gnd,OUTPUT);
  digitalWrite(Buzz2_gnd,LOW);

  pinMode(Buzz3_vcc,OUTPUT);
  digitalWrite(Buzz3_vcc,LOW);
  pinMode(Buzz3_gnd,OUTPUT);
  digitalWrite(Buzz3_gnd,LOW);
  

  //Soner 1 setup
  pinMode(soner1_VccPin, OUTPUT) ;    //tell pin 13 it is going to be an output
  digitalWrite(soner1_VccPin, HIGH) ; //tell pin 13 to output HIGH (+5V)
  pinMode(soner1_echo, INPUT);     //tell pin 11 it is going to be an input
  pinMode(soner1_trigger, OUTPUT);    //tell pin 12 it is going to be an output
  pinMode(soner1_GroundPin, OUTPUT) ; //tell pin 10 it is going to be an output
  digitalWrite(soner1_GroundPin,LOW) ;//tell pin 10 to output LOW (0V, or ground)
  

  //Soner 2 setup
  pinMode(soner2_VccPin, OUTPUT) ;    //tell pin 13 it is going to be an output
  digitalWrite(soner2_VccPin, HIGH) ; //tell pin 13 to output HIGH (+5V)
  pinMode(soner2_echo, INPUT);     //tell pin 11 it is going to be an input
  pinMode(soner2_trigger, OUTPUT);    //tell pin 12 it is going to be an output
  pinMode(soner2_GroundPin, OUTPUT) ; //tell pin 10 it is going to be an output
  digitalWrite(soner2_GroundPin,LOW) ;//tell pin 10 to output LOW (0V, or ground)  


  // moisture sensor setup
  pinMode(msensor, INPUT);
  pinMode(msensor_vcc, OUTPUT) ;
  digitalWrite(msensor_vcc, HIGH) ; 
  pinMode(msensor_gnd, OUTPUT) ;
  digitalWrite(msensor_gnd,LOW) ;
  pinMode(Buzz3_vcc, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //front obstrucle decteting with soner 1
  soner1_calculate_distance(soner1_trigger,soner1_echo);
  if (soner1_dist<70)
  {
    //Serial.print(soner1_dist); 
    //Serial.println("\nObject Alert");
    digitalWrite(Buzz_vcc,HIGH);
    for (int i=soner1_dist; i>0; i--)
      delay(10);
    digitalWrite(Buzz_vcc,LOW);
    for (int i=soner1_dist; i>0; i--)
      delay(10);
  }

  //gap in next step detecting with sonet 2
  soner2_calculate_distance(soner2_trigger,soner2_echo);
  digitalWrite(Buzz2_vcc,LOW);
  if (soner2_dist>110)
  {
     //Serial.print(soner2_dist); 
     //Serial.println("\ngap found");
     digitalWrite(Buzz2_vcc,HIGH);
     digitalWrite(Buzz2_gnd,LOW);
     delay(500);
  }

  // mostarisor sensor part
  msvalue = analogRead(msensor);
  digitalWrite(Buzz3_vcc, LOW);
  Serial.println(msvalue);
    if ( (msvalue >= 900  ) && ( flag == false ) )
  {
    digitalWrite(Buzz3_vcc, LOW); 
    flag = true; 
    delay(1000); 
  }
    if ( (msvalue < 900  ) && ( flag == true ) )
  {
    digitalWrite(Buzz3_vcc, HIGH); 
    flag = false; 
    delay(2000); 
  }
    delay(100); 

  

}
