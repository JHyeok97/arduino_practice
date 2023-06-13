#include <SoftwareSerial.h>
#include <Wire.h>
#include <AHT20.h>

AHT20 aht20;
SoftwareSerial BTSerial(4, 5);

void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    Wire.begin();
}

void loop()
{
    if (aht20.available() == true)
    {
        float temp = aht20.getTemperature();
        float hum = aht20.getHumidity();

        BTSerial.print("Temperature: ");
        BTSerial.print(temp, 2);
        BTSerial.print("C\t");
        BTSerial.print("Humidity: ");
        BTSerial.print(hum, 2);
        BTSerial.print("% RH");

        Serial.println();
    }

    if (BTSerial.available())
    {
        Serial.write(BTSerial.read());
    }

    if (Serial.available())
    {
        BTSerial.write(Serial.read());
    }

    delay(2000);
}