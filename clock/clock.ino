#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();
}
void loop()
{
    int hour, min;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("hour : ");
    while (Serial.available() == 0)
    {
    }
    hour = Serial.parseInt();
    Serial.println(hour);
    lcd.print(hour);

    lcd.setCursor(0, 1);
    lcd.print("min :");
    while (Serial.available() == 0)
    {
    }
    min = Serial.parseInt();
    Serial.println(min);
    lcd.print(min);
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(degree(hour, min));

    lcd.setCursor(0, 1);
    lcd.print("Retry?");
    while (Serial.available() == 0)
    {
    }
    String str = Serial.readString();
    if (str != "yes")
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("retry!!!!!!");
    }
    delay(1000);
}

float degree(int hour, int min)
{
    float t_degree = 0;

    if (hour >= 12)
    {
        hour = hour % 12;
    }
    // 각도 계산 식
    float degree_result = (min * 6 - (min + hour * 60) * 0.5);

    if (degree_result > 180) // 각도가 180이 넘으면 작은 각으로 계산
    {
        t_degree = (float)(360 - degree_result);
    }
    else if (degree_result < 0) // 시침이 분침을 넘어가면 음수가 나오므로 - 해줌
    {
        t_degree = (float)-degree_result;
    }
    else // 일반적인 각도 계산
    {
        t_degree = (float)degree_result;
    }

    return t_degree;
}