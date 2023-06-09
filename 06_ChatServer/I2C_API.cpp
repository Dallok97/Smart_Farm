#include <iostream>
using namespace std;

#include "I2C_API.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

// ====================  I2C_SHT20 ========================
// 생성자
I2C_SHT20::I2C_SHT20(int addr) {
    mDevId = addr;
    mTemp = 0.0;
    mHumi = 0.0;

    mFd = wiringPiI2CSetup(addr);
    if (mFd < 0)
        printf("Device not Found..!\n");

    wiringPiI2CWrite(mFd, SHT20_I2C_CMD_SOFT_RESET);
    delay(50);
}

// 소멸자
I2C_SHT20::~I2C_SHT20()
{

}

// 멤버 함수
float I2C_SHT20::measureTemp(void)
{
    int aData[2];
    int value;

    wiringPiI2CWrite(mFd, SHT20_I2C_CMD_MEASURE_TEMP);
    delay(260);

    aData[0] = wiringPiI2CRead(mFd);   // 상위비트
    aData[1] = wiringPiI2CRead(mFd);   // 하위비트

    // 측정된 데이터를 계산
    value = (aData[0]<<8) | aData[1];
    mTemp = -46.85 + 175.72/65536*(int)value;

    return mTemp;
}

float I2C_SHT20::measureHumi(void)
{
    int aData[2];
    int value;

    wiringPiI2CWrite(mFd, SHT20_I2C_CMD_MEASURE_HUMI);
    delay(260);

    aData[0] = wiringPiI2CRead(mFd);   // 상위비트
    aData[1] = wiringPiI2CRead(mFd);   // 하위비트

    // 측정된 데이터를 계산
    value = (aData[0]<<8) | aData[1];
    mHumi = -6.0 + 125.0/65536*(int)value;

    return mHumi;
}

float I2C_SHT20::getTemp(void)
{
    return mTemp;
}

float I2C_SHT20::getHumi(void)
{
    return mHumi;
}


// ====================  I2C_RGB ========================
int I2C_PCA9685::mNum = 0;
int I2C_PCA9685::mFd = 0;
int I2C_PCA9685::mDevId = 0;
// 생성자
I2C_PCA9685::I2C_PCA9685(int addr, int pinNum) {
    mDevId = addr;
    mPinNum = pinNum;
    mValue = 0;
    // mGreenValue = 0;

    wiringPiSetupGpio();

    if (mNum <= 0) {
        mFd = pca9685Setup(PIN_BASE, addr, HERTZ);  // 50Hz , 20ms
        if (mFd < 0)
            printf("Device not Found..!\n");

        pca9685PWMReset(mFd);
        mNum++;
    }
}

// 소멸자
I2C_PCA9685::~I2C_PCA9685()
{
    mNum--;
}

// 멤버 함수
int I2C_PCA9685::getPwm(void)
{
    return mValue;
}

void I2C_PCA9685::setPwm(int value)
{
    mValue = value;
    pwmWrite(PIN_BASE + mPinNum, mValue);  // dutyrate, 12bit
}


void I2C_PCA9685::setPwm(bool value)
{
    if (value == true) setPwm(4096);
    else setPwm(1);
}
