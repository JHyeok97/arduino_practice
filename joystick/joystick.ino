#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(112500);
    pinMode(8, INPUT_PULLUP);
    lcd.init();
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print(analogRead(A1));
    lcd.print("   ");
    lcd.print(analogRead(A0));
    lcd.print("   ");
    lcd.setCursor(3, 1);
    lcd.println(digitalRead(8));
    delay(100);
}
