#include <Wire.h>
#include <MultiFuncShield.h>
#include <pitches.h>
#include <TimerOne.h>

// Buzz
const int BUZZER = 3;

// button
const int button1 = 15;
const int button2 = 16;
const int button3 = 17;

// Potentionmeter
const int Potentionmeter = 14;

// Little Star 음계
int LSmelody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};
// Little Star 박자
int LSbeats[] = {
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2,
    4, 4, 4, 4, 4, 4, 2};

// Three Bears 노래 음계
int TBmelody[] = {
    NOTE_C4,
    NOTE_C4,
    NOTE_C4,
    NOTE_C4,
    NOTE_C4,
    NOTE_E4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_C4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_C4,
    NOTE_C4,
    NOTE_C4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_C4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_C4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_C4,
    NOTE_G4,
    NOTE_G4,
    NOTE_G4,
    NOTE_A4,
    NOTE_G4,
    NOTE_C5,
    NOTE_G4,
    NOTE_C5,
    NOTE_G4,
    NOTE_E4,
    NOTE_D4,
    NOTE_C4,
};
// Three Bears 박자
int TBbeats[] = {
    4, 8, 8, 4, 4,
    4, 8, 8, 4, 4,
    8, 8, 4, 8, 8, 4,
    4, 4, 2,
    4, 4, 4, 4,
    4, 4, 2,
    4, 4, 4, 4,
    4, 4, 2,
    4, 4, 4, 4,
    8, 8, 8, 8, 2,
    4, 4, 4, 4,
    4, 4, 2};

// Plane 멜로디
int Pmelody[] = {
    NOTE_E4,
    NOTE_D4,
    NOTE_C4,
    NOTE_D4,
    NOTE_E4,
    NOTE_E4,
    NOTE_E4,
    NOTE_D4,
    NOTE_D4,
    NOTE_D4,
    NOTE_E4,
    NOTE_G4,
    NOTE_G4,
    NOTE_E4,
    NOTE_D4,
    NOTE_C4,
    NOTE_D4,
    NOTE_E4,
    NOTE_E4,
    NOTE_E4,
    NOTE_D4,
    NOTE_D4,
    NOTE_E4,
    NOTE_D4,
    NOTE_C4,
};
// Plane 박자
int Pbeats[] = {
    6, 8, 8, 8,
    8, 8, 4,
    8, 8, 4,
    8, 8, 4,
    6, 8, 8, 8,
    8, 8, 4,
    8, 8, 6, 8, 2};

void setup()
{
    Timer1.initialize();
    MFS.initialize(&Timer1);

    Serial.begin(115200);

    pinMode(BUZZER, OUTPUT);

    pinMode(button1, INPUT_PULLUP); // 스위치 1번
    pinMode(button2, INPUT_PULLUP); // 스위치 2번
    pinMode(button3, INPUT_PULLUP); // 스위치 3번
}

void loop()
{
    int buttonState1 = digitalRead(button1);
    int buttonState2 = digitalRead(button2);
    int buttonState3 = digitalRead(button3);

    // 1번 버튼 누르면
    if (buttonState1 == LOW)
    {
        ThreeBears();
    }

    // 2번 버튼 누르면
    if (buttonState2 == LOW)
    {
        Plane();
    }

    // 3번 버튼 누르면
    if (buttonState3 == LOW)
    {
        LittleStar();
    }
}

void ThreeBears()
{
    int idx = 0;
    char str[] = "THREE BEARS";
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, HIGH);
    digitalWrite(LED_3_PIN, HIGH);

    for (int i = 0; i < sizeof(TBmelody) / sizeof(int); i++) // Three Bears 노래 나옴
    {
        MFS.isrCallBack();
        int noteDuration = 1000 / TBbeats[i];
        tone(BUZZER, TBmelody[i], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER);
        MFS.write(str + idx);

        idx = (idx + 1) % (sizeof(str) - 1);
    }
}
void Plane()
{
    int idx = 0;
    char str[] = "PLANE";
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, LOW);
    digitalWrite(LED_3_PIN, HIGH);

    for (int i = 0; i < sizeof(Pmelody) / sizeof(int); i++) // Plane 노래 나옴
    {
        int noteDuration = 1000 / Pbeats[i];
        tone(BUZZER, Pmelody[i], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER);
        MFS.write(str + idx);

        idx = (idx + 1) % (sizeof(str) - 1);
    }
}
void LittleStar()
{
    int idx = 0;
    char str[] = "LITTLE STAR";
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, HIGH);
    digitalWrite(LED_3_PIN, LOW);

    for (int i = 0; i < sizeof(LSmelody) / sizeof(int); i++) // Little Star 노래 나옴
    {
        int noteDuration = 1000 / LSbeats[i];
        tone(BUZZER, LSmelody[i], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(BUZZER);
        MFS.write(str + idx);

        idx = (idx + 1) % (sizeof(str) - 1);
    }
}