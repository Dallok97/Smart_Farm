#include <wiringPi.h>
#include "GPIO_PWM_API.h"

GPIO_LED::GPIO_LED(int pin):GPIO_LED(pin, LOW){}

GPIO_LED::GPIO_LED(int pin, bool value) {
    mPinNum = pin;
    mState = value;

    wiringPiSetupGpio();

    pinMode(mPinNum, OUTPUT);
    digitalWrite(mPinNum, mState);
}

// 소멸자
GPIO_LED::~GPIO_LED()
{
    digitalWrite(mPinNum, LOW);
}

// 멤버 함수
void GPIO_LED::ledWrite(bool value)
{
    mState = value;
    digitalWrite(mPinNum, mState);
}

bool GPIO_LED::ledRead(void)
{
    return digitalRead(mPinNum);
}



