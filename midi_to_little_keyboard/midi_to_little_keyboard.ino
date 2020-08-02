#define  GPIO2_PREFER_SPEED  1
#include <DIO2.h>

#include <MIDI.h>

#include <FastLED.h>
CRGB leds[1];

MIDI_CREATE_DEFAULT_INSTANCE();

int note[] = {-1,-1};
bool lastnote = 0;

long timer = 0;
long delayT = 1000;

int midiOffset = 41;//the midi note which the lowest key corresponds to

bool ledon= true;


void setup() {
  for (int scan = 10; scan >= 3; scan--) {
    pinMode2(scan, INPUT);
  }
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  
  Serial.begin(115200);

   FastLED.addLeds<WS2812B,13,GRB>(leds, 1).setCorrection(TypicalLEDStrip);
   FastLED.setBrightness(100);
 
  timer = millis() + delayT;
}

void loop() {
  MIDI.read();

  if (timer < millis()) {
    timer = millis() + delayT;
    if (ledon)    leds[0] = CRGB::Purple;
    else leds[0] = CRGB::Black;
    FastLED.show(); 
    ledon=!ledon;
    //digitalWrite2(13, !digitalRead2(13));
  }

  for (int scan = 0; scan < 8; scan++) {//30==14 , 23==21
    if (digitalRead2(scan + 14)) {
      for (int read = 0; read <= 8; read++) {//11=3 , 18=10
        if (read + scan  * 8  == note[0]  || read + scan  * 8 == note[1] ) {
          digitalWrite2(read + 4, HIGH);
        }
        else pinMode2(read + 4, INPUT);
      }
    }
  }
}

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (pitch >= midiOffset && pitch < midiOffset + 32) {
    note[lastnote] = pitch - midiOffset;
    lastnote=!lastnote;
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  if (pitch >= midiOffset && pitch < midiOffset + 32) {
    if(note[0] == pitch - midiOffset)note[0]=-1;
    if(note[1] == pitch - midiOffset)note[1]=-1;
  }
}
