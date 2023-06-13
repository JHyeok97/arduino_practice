long levelTimeout = 500000; // 500ms
uint8_t bitmask = 0xFF;
uint8_t port = 0xFF;
int pin = 7;
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    byte temperature = 0;
    byte humidity = 0;

    read(&temperature, &humidity);

    Serial.print("Humidity : ");
    Serial.print(humidity);
    Serial.print("%, ");
    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.print("'C");
    Serial.println();

    delay(1000);
}

int read(byte *temperature, byte *humidity)
{
    int ret = 0;
    bitmask = digitalPinToBitMask(pin);
    port = digitalPinToPort(pin);

    byte data[40] = {0};
    sample(data);

    // 받은 data 처리

    Serial.println();

    *temperature = _temp(data);
    *humidity = _hum(data);
}
int sample(byte data[40])
{
    memset(data, 0, 40);
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(20);
    //
    digitalWrite(pin, HIGH);
    pinMode(pin, INPUT);
    delayMicroseconds(25);

    long t = levelTime(LOW, 10, 6);
    if (t < 30)
    {
        // return -1;
    }
    t = levelTime(HIGH, 10, 6);
    if (t < 50)
    {
        // return -1;
    }

    for (size_t i = 0; i < 40; i++)
    {
        t = levelTime(LOW, 10, 6);
        if (t < 24)
        {
            // return -1;
        }
        t = levelTime(HIGH, 10, 6);
        if (t < 11)
        {
            // return -1;
        }
        data[i] = (t > 40 ? 1 : 0);
    }

    t = levelTime(LOW, 10, 6);
    if (t < 24)
    {
        return -1;
    }

    return 0;
}

long levelTime(byte level, int firstWait, int interval)
{
    unsigned long time_start = micros();
    long time = 0;

    uint8_t portState = level ? bitmask : 0;

    bool loop = true;
    for (int i = 0; loop; i++)
    {
        if (time < 0 || time > levelTimeout)
        {
            return -1;
        }

        if (i == 0)
        {
            if (firstWait > 0)
            {
                delayMicroseconds(firstWait);
            }
        }
        else if (interval > 0)
        {
            delayMicroseconds(interval);
        }
        time = micros() - time_start;

        // low상태에서 high 상태로 변할때 빠져 나가는 것
        loop = ((*portInputRegister(port) & bitmask) == portState);
    }

    return time;
}

int _hum(byte data[40])
{
    int hum = 0, j = 1;
    for (int i = 7; i >= 0; i--)
    {
        hum += data[i] * j;
        j *= 2;
    }

    return hum;
}
int _temp(byte data[40])
{
    int temp = 0, j = 1;
    for (int i = 23; i >= 16; i--)
    {
        temp += data[i] * j;
        j *= 2;
    }

    return temp;
}