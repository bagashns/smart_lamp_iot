#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6_xJRHLVL"
#define BLYNK_TEMPLATE_NAME "Sistem Penerangan Otomatis iSurf"
#define BLYNK_AUTH_TOKEN "7CV9oDHWkch5XWhUWP1j4O8QWt3keyOo"
#define lampu 33
#define trig 12
#define echo 27

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "mono";
char pass[] = "iotsamsungg";

unsigned long interval;

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(lampu, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  int counting = 0;
  if (millis() - interval > 1000){
    counting++;
    if (counting >= 1000) counting = 0;
    interval = millis();
  }
  Blynk.run();

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.0342 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  distance = constrain(distance, 2, 50);

  int brightness = map(distance, 2, 50, 255, 0);

  analogWrite(lampu, brightness);

  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, brightness);

  delay(100);
}