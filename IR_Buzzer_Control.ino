#include <IRremote.h>

#define MENU 0x77E14047
#define PLAY_PAUSE 0x77E12047
#define VOLUME_UP 0x77E1D047
#define VOLUME_DOWN 0x77E1B047
#define REWIND 0x77E11047
#define FAST_FORWARD 0x77E1E047

int RECV_PIN = 11;
int speakerPin = 2;

int numTones = 10;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
int i = 0;
long previousMillis = 0;
long maxTime = 2000;
long between = maxTime;
long beeplength = 50;

boolean isOn = false;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  irrecv.enableIRIn();
}

void loop() {
  
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > between + beeplength ) {
    previousMillis = currentMillis;  
    if(isOn)
    {
      tone(speakerPin, tones[i]);
    }
  } 
 
  if(currentMillis - previousMillis > beeplength) {
    noTone(speakerPin); 
  }
  if (irrecv.decode(&results)) {
    switch(results.value) 
    {
      case MENU:
          break;
      case PLAY_PAUSE:
          isOn = !isOn;
          break;
      case VOLUME_UP:
        i++;
         break;
      case VOLUME_DOWN:
        i--;
        break;
      case REWIND:
        between= between + 100;
        break;
      case FAST_FORWARD:
        between= between - 100;
        break;
    }
    if(i > numTones) {
      i = numTones;
    }
    
    if(between > maxTime) {
      between = maxTime;
    }
    
    if(i < 0) {
       i = 0;
    }
    if(between < 0) {
      between = 0;
    }
    irrecv.resume();
  }
}
