
#include "FPS_GT511C3.h"

FPS_GT511C3 fps;

int door = D0; // output to control door driver

void setup() {
  pinMode(door, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  delay(100);
  fps.Open();
  fps.SetLED(true); // turn on led in scanner
}

void loop() {
  if (fps.IsPressFinger()) {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id < 200) { // if the fingerprint is in the database
      digitalWrite(door, HIGH);
      delay(100);
      digitalWrite(door, LOW);
      delay(2000);

      Serial.print("ID found");
      Serial.println(id);

    } else {
      Serial.println("not in database");

      for (int i = 0; i < 5; i++) { // blink the led a few times
        fps.SetLED(false);
        delay(100);
        fps.SetLED(true);
        delay(100);
      }
    }

  } else {
    Serial.println("scan finger");
  }

  delay(150);
}
