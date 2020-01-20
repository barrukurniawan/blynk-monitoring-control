#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trigPin  D8
#define echoPin  D7
#define ledrendah D2
#define ledtinggi D3

char ssid[] = "wifi-name";
char pass[] = "password-wifi";
char auth[] = "N5ODWRJ5xcgDVGM3UQs0xGRDVxc7_fb9"; // auth code from blynk

long duration;
int distance;

BlynkTimer timer;

BLYNK_WRITE(V1)
{
  int nilai = random(1,999);
  
  int pinValue = param.asInt();
  if (pinValue == 1) {
    Blynk.tweet("Bendungan dibuka! \n #IoT " + String(nilai));
    Serial.println("send tweet! " + String(nilai));    
  } else {
    Serial.println("Off tweet");
  }

}

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
  } else if (distance >= 3000){
    Blynk.tweet("Waw ketinggian air capai lebih dari 2000cm :)\n #arduino #IoT #blynk @blynk_app");
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
  
//  Blynk.tweet("Hey, Sobat UNAS!! \nWe are Bendungan UNAS!");

  timer.setInterval(2000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
