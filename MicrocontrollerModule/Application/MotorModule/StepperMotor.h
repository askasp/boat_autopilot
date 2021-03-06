//include "/home/ask/git/jumpnow/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/wiringPi.h"
#pragma once
#include <iostream>
#include <cstdlib>
#include <mutex>
#include "../NetworkModule/Inbox.h"
#include "../NetworkModule/Outbox.h"
#include <unistd.h>


class StepperMotor
{
    private:
    int msSleep;
    int currentPosition;
    double maxPosition;
    double minPosition;
    const int enablePin = 1;
    const int directionPin = 4;
    const int pulsePin = 5;

    public:
    StepperMotor();
    void turnOff();
    void turnClockwise(Inbox* myInbox);
    void turnCounterClockwise(Inbox* myInbox);
};




