#include <LiquidCrystal_I2C.h>      // LiquidCrystal_I2C 헤더파일 호출
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD의 address 주소 및 크기 입력

int randNum[1000];

void setup() // 초기화
{
    Serial.begin(115200);
    lcd.init();      // LCD 초기화
    lcd.backlight(); // LCD 백라이트 함수
}
void loop() // 무한루프
{
    sort();
}

void sort()
{
    int temp;

    for (int i = 0; i < 1000; i++)
    {
        randNum[i] = random();
        Serial.println(randNum[i]);
    }

    for (int i = 0; i < 999; i++)
    {
        int min = i;
        for (int j = i + 1; j < 1000; j++)
        {
            if (randNum[min] >= randNum[j])
            {
                min = j;
            }
        }
        temp = randNum[i];
        randNum[i] = randNum[min];
        randNum[min] = temp;
    }

    lcd.clear(); // LCD 초기화

    lcd.setCursor(0, 0);
    for (int i = 0; i < 10; i++)
    {
        lcd.print(randNum[i]);
    }

    lcd.setCursor(0, 1);
    for (int i = 10; i >= 1; i--)
    {
        lcd.print(randNum[1000 - i]);
    }

    delay(3000);
}