#define BLYNK_TEMPLATE_ID "TMPL6VJn6bT9r"
#define BLYNK_TEMPLATE_NAME "Wifi Controlled Car"
#define BLYNK_AUTH_TOKEN "tg7dzm9-mw3Gn71dwzXIbFLNF9EoGM5_"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 

#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
#define motor D6

bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
bool sprayActivated = 0;


char auth[] = "tg7dzm9-mw3Gn71dwzXIbFLNF9EoGM5_";
char ssid[] = "local"; //Enter your WIFI name
char pass[] = "local123"; //Enter your WIFI passowrd
 
 
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(motor, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  left = param.asInt();
}
 
BLYNK_WRITE(V3) {
  right = param.asInt();
}
 
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}

BLYNK_WRITE(V5){
  sprayActivated = param.asInt(); // Read the value from Blynk
  // if (sprayState == 1) {
  //   sprayActivated = true;
  // } else {
  //   sprayActivated = false;
  // }
}
 
void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (sprayActivated == 1) {
    dcMotor();

  }else if(sprayActivated==0)
  {
    dcStop();
  }else if  (forward == 0 && backward == 0 && left == 0 && right == 0 && sprayActivated==0) {
    carStop();
    Serial.println("carstop");
  } 
}

void loop() {
  Blynk.run(); 
  smartcar();
}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void dcMotor(){
digitalWrite(motor, HIGH);
Serial.println("Water out");
}

void dcStop()
{
  digitalWrite(motor,LOW);
}