#define MIDI_CHANNEL  144
#define ANALOG_CHANNEL  159
#define MAX_VELOCITY  127

#define BUTTON_INPUT_DELAY_MS 100

#define BUTTON_COUNT  6

int button_pin[] =  {9, 8, 7, 6, 4, 3};
int button_note[] = {77, 78, 79, 80, 81, 82};
bool event_handled[BUTTON_COUNT] = {false};

#define ANALOG_PIN    13

int last_analog_value = 0;
  
void setup() 
{
    Serial.begin(31250);
    for (int i = 0; i < BUTTON_COUNT; i++)
        pinMode(button_pin[i], INPUT_PULLUP);
}

bool button_pushed(int pin_number)
{
    return !digitalRead(pin_number);
}

void loop() 
{
    delay(BUTTON_INPUT_DELAY_MS);
    handle_button_pins();
    //handle_analog_pin();
}

void handle_button_pins()
{
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        if (button_pushed(button_pin[i]) && !event_handled[i])
        {
            sendNote(MIDI_CHANNEL+i, button_note[i], MAX_VELOCITY);
            event_handled[i] = true;
        }
        else if (!button_pushed(button_pin[i]) && event_handled[i])
        {
            event_handled[i] = false;
        }
    }  
}

void handle_analog_pin()
{
    int analog_value = analogRead(ANALOG_PIN);
    analog_value = map(analog_value, 0, 1023, 0, 127);
    analog_value = constrain(analog_value, 0, 127);

    if (abs(analog_value - last_analog_value) > 4)
    {
        sendNote(ANALOG_CHANNEL, 86, analog_value);
        last_analog_value = analog_value;
    }

}

void sendNote(int channel, int note, int velocity)
{
  Serial.write(channel);
  Serial.write(note);
  Serial.write(velocity);
}

