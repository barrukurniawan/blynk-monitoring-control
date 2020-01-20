// Deklarasi library
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trigPin  D8
#define echoPin  D7
#define ledrendah D2
#define ledtinggi D3

// Deklarasi variabel autentikasi
char ssid[] = "gigel.id";     // Wifi name
char pass[] = "cisanggiri14"; // Paswword Wifi
char auth[] = "N5ODWRJ5xcgDVGM3UQs0xGRDVxc7_fb9"; // Auth Code from Blynk

// deklarasi variabel sensor HC-SR04
long duration;
int distance;

// deklarasi timer Blynk
BlynkTimer timer;

// koding untuk terima nilai button V1 dan push tweet
BLYNK_WRITE(V1)
{
  int nilai = random(1,999); // deklarasi nilai random
  
  int pinValue = param.asInt(); // deklarasi value button V1 dari blynk
  if (pinValue == 1) {
    Blynk.tweet("Bendungan dibuka! \n #IoT #" + String(nilai));
    Serial.println("send tweet! " + String(nilai));    
  } else {
    Serial.println("Off tweet");
  }
}

void sendSensor()
{
  int random_air = random(1, 195);

  // deklarasi perhitungan sensor suara
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
  Serial.println(random_air);
  
  if (random_air <= 80){
    digitalWrite(ledrendah, HIGH);
    digitalWrite(ledtinggi, LOW);
  } else if (random_air >= 80) {
    digitalWrite(ledtinggi, HIGH);
    digitalWrite(ledrendah, LOW);
  } else if (random_air >= 3000){
    Blynk.tweet("Waw ketinggian air capai lebih dari 2000cm :)\n #arduino #IoT #blynk @blynk_app");
  }
  
  // post data ketinggian air ke blynk
  Blynk.virtualWrite(V5, random_air);
  
}

void setup()
{
  pinMode(trigPin, OUTPUT); // Ping, kirim pulse ke object
  pinMode(echoPin, INPUT); // Terima pulse pantulan dari object

  pinMode(ledrendah, OUTPUT); // deklarasi pin ledrendah sebagai output
  pinMode(ledtinggi, OUTPUT); // deklarasi pin ledtinggi sebagai output
  
  // Debug console (kecepatan baudrate komunikasi serial), standar esp8266 adalah 115200
  Serial.begin(115200);
  
  // autentikasi Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Blynk.tweet("Hey, Sobat UNAS!! \nWe are Bendungan UNAS!");
  
  timer.setInterval(2000L, sendSensor); // interval waktu update ke Blynk hitungan detik
}

void loop()
{
  Blynk.run();
  timer.run();
}
