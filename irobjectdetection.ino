/*
 * Copyright (c) 2023 Altay Atik - altayatik@yahoo.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <Arduino.h>

const int inputPin = 2;

unsigned long timerStart;
bool objectRemoved = false;
bool countdownFinished = false;
unsigned long timerdownStart;

const int red = 10;
const int yellow = A2;
const int green = A5;

int total_time = 59; //time for led to turn red
int wait_to_return = 3000; //cooldown for short abandons
int time_up = 1500; //minutes to wait after 1 hour is up


void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  timerStart = millis();
}

void loop() {
  if (!objectRemoved) {
    unsigned long elapsedTime = millis() - timerStart;
    int minutes = (elapsedTime / 1000) / 60; 
    int seconds = (elapsedTime / 1000) % 60;
    Serial.print("Time: ");
    Serial.print(minutes);
    Serial.print(":");
    if (seconds < 10) {
      Serial.print("0");
    }
    if ((digitalRead(inputPin) == LOW) && (seconds > total_time)){
      Serial.println("time up, take 15");
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      return;
    }
    Serial.println(seconds);
    if (digitalRead(inputPin) == LOW) {
      Serial.println("Person in Range");
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
    } else {
      Serial.println("Person not in Range");
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay(wait_to_return); //wait 5 minutes for person to return
      if (digitalRead(inputPin) == HIGH) {
        objectRemoved = true;
        timerdownStart = millis();
        Serial.println("Range Abandoned");
        Serial.println("Return in 15");
        digitalWrite(red, HIGH);
        digitalWrite(yellow, LOW);

        //START THE 15 MINUTE WAIT
        delay(time_up); //wait 15 minutes
        Serial.println("Return in Range");
        Serial.println("Reset device");
        digitalWrite(red, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(green, HIGH);
        delay(18000);
      }
    }
  }
}
