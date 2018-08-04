#include "StepperMotor.h"

#ifdef SIMULATOR
#include "../SimulatorModule/SimulatedWiringPi.h"
#endif
#ifndef SIMULATOR
#include <wiringPi.h>
#endif


StepperMotor::StepperMotor()
    {
        wiringPiSetup();
        pinMode (enablePin, OUTPUT) ;
        pinMode (directionPin, OUTPUT) ;
        pinMode (pulsePin, OUTPUT) ;
        digitalWrite(enablePin,HIGH);
    }
void StepperMotor::turnOff(){
        digitalWrite(enablePin,HIGH);
    }

void StepperMotor::turnClockwise(Inbox* myInbox){
        digitalWrite(enablePin,LOW);
        digitalWrite(directionPin,LOW);
        while(true){
            if (myInbox->isInboxUnread()){
                return;
            }
            digitalWrite (pulsePin, HIGH) ; usleep(1000); //delay (1) ;
            digitalWrite (pulsePin,  LOW) ; usleep(1000);////delay (1) ;
        }
    }
void StepperMotor::turnCounterClockwise(Inbox* myInbox){
        digitalWrite(enablePin,LOW);
        digitalWrite(directionPin,HIGH);
        while(true){
            if (myInbox->isInboxUnread()){
                return;
            }
            digitalWrite (pulsePin, HIGH) ; usleep(1000);//delay (1) ;
            digitalWrite (pulsePin,  LOW) ; usleep(1000);//delay (1) ;
        }
    }
