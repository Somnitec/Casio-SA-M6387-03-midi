
int note = 0;

long timer = 0;
long delayT = 1000;



void setup() {
  Serial.begin(9600);
  for (int scan = 10; scan >= 3; scan--) {
    pinMode(scan, INPUT);
  }
  timer = millis() + delayT;
}

void loop() {
  if (timer < millis()) {
    timer = millis() + delayT;
    note=(note+1)%32 ;
    digitalWrite(13, !digitalRead(13));
    Serial.println(note);

  }

  int posleftright = 0;
  int posupdown = 0;
  for (int scan = 0; scan < 8; scan++) {//30==14 , 23==21
    if (digitalRead(scan + 14)) {
      for (int read = 0; read <= 8; read++) {//11=3 , 18=10

        /*
          Serial.print("posleftright ");
          Serial.print(scan);
          Serial.print(" posupdown ");
          Serial.print(read);
          Serial.print(" added ");
          Serial.println(scan + read  * 8 + 1);
        */

        if (read + scan  * 8 + 1 == note+1) {
          digitalWrite(read+3, HIGH);
        }
        else pinMode(read+3, INPUT);
      }
      /*
        if (posleftright + (posupdown - 1) * 8 == note) {
        //Serial.print("posleftright ");
        //Serial.print(posleftright);
        //Serial.print(" posupdown ");
        //Serial.println(posupdown);
        digitalWrite(read, HIGH);
        delayMicroseconds(190);//to make sure it is read, windows should be 190 uS
        pinMode(read, INPUT);
        }
        }*/
    }
  }


  /*
    if (digitalRead(14)) {
      digitalWrite(pin, HIGH);
      digitalWrite(13, HIGH);
      //delayMicroseconds(190);
      //digitalWrite(pin, HIGH);
    }
    else {
      pinMode(pin, INPUT);
    }
    } else {
    pinMode(pin, INPUT);
    digitalWrite(13, LOW);
    }

  */
}
