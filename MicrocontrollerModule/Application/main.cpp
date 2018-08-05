#include <iostream>

#include "NetworkModule/TCPClient.h"
#include <thread>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "MotorModule/StepperMotor.h"
#include <mutex>
#include"NetworkModule/Inbox.h"
#include"NetworkModule/Outbox.h"
#include "NetworkModule/NetworkManager.h"


void controlTask(Inbox* myInbox, Outbox* myOutbox){
    std::string  psi_D;
    std::string  task1;
    StepperMotor myStepper;
    myOutbox->updateOutbox("20","30");
    while(true){
        if (myInbox->isInboxUnread()){
            myInbox->readInbox(psi_D,task1);
            if (task1 == "OFF"){
                
                myStepper.turnOff();
            }
            else if(task1 == "CW"){
                myStepper.turnClockwise(myInbox);
            }
            else if(task1 ==  "CCW"){
                myStepper.turnCounterClockwise(myInbox);
            }
            else if(task1 == "Hold")
            {
            }
            else 
            {
            }
        }
        usleep(100);
    }
}


int main()
{
    Outbox myOutbox;
    Inbox myInbox;
    NetworkManager myNetworkManager(&myOutbox,&myInbox);
    std::thread t1(&NetworkManager::androidCommunicationTask,&myNetworkManager);
    t1.detach();
    thread t2(controlTask,&myInbox,&myOutbox);
    t2.detach();
    while (true){
        usleep(100);
    }

}
