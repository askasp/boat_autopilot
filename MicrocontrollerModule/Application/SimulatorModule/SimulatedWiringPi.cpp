#include "SimulatedWiringPi.h"

void pinMode(int pin,int outin){
    std::string pinmode;
    if (outin){
        pinmode = "OUTPUT";
    }
    else{
        pinmode = "INPUT";
    } 
    std::cout << "Setting Pin: "<<pin << " as " <<pinmode << std::endl;
}

void digitalWrite(int pin,int status){
    std::cout << "Setting Pin: "<< pin << " to " << status << std::endl;
}

void wiringPiSetup(){
    std::cout << "Setting up gpios" << std::endl;
}

