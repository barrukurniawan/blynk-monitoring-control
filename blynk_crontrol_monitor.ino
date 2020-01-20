#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trigPin  D8
#define echoPin  D7
#define ledrendah D2
#define ledtinggi D3

char ssid[] = "wifi-name";
char pass[] = "password-wifi";
char auth[] = "ur-auth-code-from-blynk";

long duration;
int distance;

BlynkTimer timer;

void sendSensor()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
  Serial.println(distance);
  if (distance <= 80){
    digitalWrite(ledrendah, HIGH);
    digitalWrite(ledtinggi, LOW);
  } else if (distance >= 80) {
    digitalWrite(ledtinggi, HIGH);
    digitalWrite(ledrendah, LOW);
  } else if (distance >= 2000){
    Blynk.tweet("Waw ketinggian air capai lebih dari 2000cm!\n #arduino #IoT #blynk @blynk_app");
  }
  
  Blynk.virtualWrite(V5, distance);
  
}

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  pinMode(ledrendah, OUTPUT);
  pinMode(ledtinggi, OUTPUT);
  
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
