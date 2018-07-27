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

void StepperMotor::turnClockwise(inMessage* my_inMessage){
        digitalWrite(enablePin,LOW);
        digitalWrite(directionPin,LOW);
        while(true){
            if (my_inMessage->getReceivedNewMessage() == true){
                return;
            }
            digitalWrite (pulsePin, HIGH) ; usleep(1000); //delay (1) ;
            digitalWrite (pulsePin,  LOW) ; usleep(1000);////delay (1) ;
        }
    }
void StepperMotor::turnCounterClockwise(inMessage* my_inMessage){
        digitalWrite(enablePin,LOW);
        digitalWrite(directionPin,HIGH);
        while(true){
            if (my_inMessage->getReceivedNewMessage() == true){
                return;
            }
            digitalWrite (pulsePin, HIGH) ; usleep(1000);//delay (1) ;
            digitalWrite (pulsePin,  LOW) ; usleep(1000);//delay (1) ;
        }
    }
