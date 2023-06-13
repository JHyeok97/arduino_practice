#include <Wire.h>
#define dataaddress 0x38

unsigned long previousMillis = 0;
const unsigned long MEASURE_INTERVAL = 2000;

uint32_t temp = 0;
uint32_t hum = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("Humidity AHT20 examples");

    Wire.begin(); // Join I2C bus
    // Check if the AHT20 will acknowledge
    init();
}

void loop()
{
    float temp = getTemperature();
    float hum = getHumidity();

    unsigned long currentMillis = millis();
    // Print the results
    if (currentMillis - previousMillis >= MEASURE_INTERVAL)
    {
        Serial.print("Temperature: ");
        Serial.print(temp, 2);
        Serial.print(" C\t");
        Serial.print("Humidity: ");
        Serial.print(hum, 2);
        Serial.print("% RH");

        Serial.println();
    }
    delay(2000);
}

void readData()
{
    Wire.beginTransmission(dataaddress);
    Wire.write(0xAC); // 데이터 요청 명령어 전송
    Wire.write(0x33);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(100); // 데이터 응답 대기 시간
    if (Wire.requestFrom(dataaddress, (uint8_t)6) > 0)
    {
        Wire.read();

        uint32_t incoming = 0;

        incoming |= (uint32_t)Wire.read() << (8 * 2);
        incoming |= (uint32_t)Wire.read() << (8 * 1);

        uint8_t midByte = Wire.read();
        incoming |= midByte;

        hum = incoming >> 4;

        temp = (uint32_t)midByte << (8 * 2);
        temp |= (uint32_t)Wire.read() << (8 * 1);
        temp |= (uint32_t)Wire.read() << (8 * 0);
        temp = temp & ~(0xFFF00000);
    }
}
float getTemperature()
{
    readData();

    return ((float)temp / 1048576) * 200 - 50;
}
float getHumidity()
{
    readData();

    return ((float)hum / 1048576) * 100;
}

void init()
{
    Wire.beginTransmission(dataaddress); // aht20 센서 주소 설정
    Wire.write(0xBE);                    // 초기화 명령어 전송
    Wire.endTransmission();
    Wire.requestFrom(dataaddress, 1); // 응답 데이터 수신
    if (Wire.read() != 0x00)
    { // 응답 데이터 확인
        Serial.println("aht20 initialization failed");
        while (1)
            ; // 초기화 실패 시 프로그램 종료
    }
    Wire.beginTransmission(dataaddress);
    Wire.write(0x08); // 초기화 명령어 전송
    Wire.endTransmission();
    Wire.requestFrom(dataaddress, 1); // 응답 데이터 수신
    if (Wire.read() != 0x00)
    { // 응답 데이터 확인
        Serial.println("aht20 initialization failed");
        while (1)
            ; // 초기화 실패 시 프로그램 종료
    }
}