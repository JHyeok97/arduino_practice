#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int trigPin = 2;
int echoPin = 4;
int speakerPin = 8;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    lcd.init();
    lcd.backlight();
}

void loop()
{

    long duration, distance;
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH); // trigPin에서 초음파 발생
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // echoPin 이 HIGH를 유지한 시간을 저장 한다.
    distance = ((float)(340 * duration) / 1000) / 2;
    Serial.print("Duration:"); // 시리얼모니터에 Echo가 HIGH인 시간을 표시
    Serial.print(duration);
    Serial.print("\nDIstance:"); // 물체와 초음파 센서간 거리를 표시
    Serial.print(distance);
    Serial.println("mm\n");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Duration:"); // 시리얼모니터에 Echo가 HIGH인 시간을 표시
    lcd.print(duration);
    lcd.setCursor(0, 1);
    lcd.print("DIstance:"); // 물체와 초음파 센서간 거리를 표시
    lcd.print(distance);
    lcd.print("mm");
    if (distance < 10)
    {
        tone(speakerPin, 35, 1000);
    }
    else if (distance < 2000)
    {
        tone(speakerPin, 35, distance * 2);
        delay(distance * 10);
    }
}

/*void tone(int distance){
    if(distance < 1000)
}*/