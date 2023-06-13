#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>
#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial BTSerial(4, 5);
PulseSensorPlayground pulseSensor;

const int PulseWire = 0;
const int LED = 13;
int Threshold = 550;

void setup()
{
    BTSerial.begin(9600);
    Wire.begin();
    Serial.begin(9600);

    pulseSensor.analogInput(PulseWire);
    pulseSensor.blinkOnPulse(LED);
    pulseSensor.setThreshold(Threshold);

    if (pulseSensor.begin())
    {
        Serial.println("We create a pulseSensor Object !");
    }
}

void loop()
{
    if (pulseSensor.sawStartOfBeat())
    {
        int myBPM = pulseSensor.getBeatsPerMinute();
        Serial.print("BPM: ");
        Serial.println(myBPM);
        BTSerial.print("BPM: ");
        BTSerial.println(myBPM);
    }

    if (BTSerial.available())
    {
        Serial.write(BTSerial.read());
    }

    if (Serial.available())
    {
        BTSerial.write(Serial.read());
    }

    delay(20);
}