#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int pos = 0;
int hight = 0;

byte state[8] = {
    B00000,
    B00000,
    B01110,
    B11011,
    B11100,
    B01110,
    B00000,
    B00000,
};

byte point[8] = {
    B00000,
    B00000,
    B10101,
    B01110,
    B01110,
    B10101,
    B00000,
    B00000,
};

void setup()
{

    Serial.begin(9600);
    pinMode(3, INPUT_PULLUP);

    digitalWrite(3, HIGH);
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, state);
    lcd.createChar(1, point);
}

void loop()
{

    lcd.setCursor(pos, hight);
    lcd.write(byte(0));

    if (hight <= 0)
    {
        hight = 0;
    }

    else if (hight >= 1)
    {
        hight = 1;
    }

    if (pos <= 0)
    {
        pos = 0;
    }

    else if (pos >= 15)
    {
        pos = 15;
    }

    int push = digitalRead(3);
    int posX = analogRead(A0);
    int posY = analogRead(A1);

    long randNumber1 = random(2);
    long randNumber2 = random(17);
    delay(100);

    /* *create */
    lcd.setCursor(randNumber2, randNumber1);
    lcd.write(byte(1));

    if (posY > 750)
    {
        lcd.setCursor(pos, hight);
        lcd.print(" ");
        pos++;
    }

    else if (posY < 150)
    {
        lcd.setCursor(pos, hight);
        lcd.print(" ");
        pos--;
    }

    else if (posX > 750)
    {
        lcd.setCursor(pos, hight);
        lcd.print(" ");
        hight--;
    }

    else if (posX < 150)
    {
        lcd.setCursor(pos, hight);
        lcd.print(" ");
        hight++;
    }
}