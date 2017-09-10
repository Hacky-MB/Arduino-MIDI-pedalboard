#define MIDI_CHANNEL 144
#define NOTE 77
#define MAX_VELOCITY 127

#define BUTTON_INPUT_DELAY_MS 200

#define BUTTON_PIN 2

bool note = false;
  
void setup() {
    Serial.begin(31250);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool button_pushed()
{
    return !digitalRead(2);
}

void loop() {
    delay(BUTTON_INPUT_DELAY_MS);
    if (button_pushed() && !note)
    {
      noteOn(MIDI_CHANNEL, NOTE, MAX_VELOCITY); 
      note = true;
    }
    else if (!button_pushed() && note)
    {
      note = false;
    }
}

void noteOn(byte channel, byte pitch, byte velocity)
{
    // 0x90 is the first of 16 note on channels. Subtract one to go from MIDI's 1-16 channels to 0-15
    //channel += 0x90 - 1;
  
    // Ensure we're between channels 1 and 16 for a note on message
    //if (channel >= 0x90 && channel <= 0x9F)
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write(velocity);
}

