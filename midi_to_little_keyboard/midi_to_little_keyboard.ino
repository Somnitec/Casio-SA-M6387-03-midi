#define  GPIO2_PREFER_SPEED  1
#include <DIO2.h>

int note = 0;

long timer = 0;
long delayT = 1000;



void setup() {
  Serial.begin(9600);
  for (int scan = 10; scan >= 3; scan--) {
    pinMode2(scan, INPUT);
  }
  timer = millis() + delayT;
}

void loop() {
  if (timer < millis()) {
    timer = millis() + delayT;
    note = (note + 1) % 32 ;
    digitalWrite2(13, !digitalRead2(13));
    Serial.println(note);

  }

  //if (digitalRead(21) && digitalRead(20) && digitalRead(19))Serial.println("trigg");

    for (int scan = 0; scan < 8; scan++) {//30==14 , 23==21
      if (digitalRead2(scan + 14)) {
        for (int read = 0; read <= 8; read++) {//11=3 , 18=10
  
  
          if (read + scan  * 8 + 1 == note + 1) {
            digitalWrite2(read + 3, HIGH);
          }
          else pinMode2(read + 3, INPUT);
        }
      }
    }
}
