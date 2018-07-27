#include <iostream>

#include "NetworkModule/TCPServer.h"
#include <thread>
#include <sys/wait.h>
#include <string>
#include <vector>
#include "MotorModule/StepperMotor.h"
#include <mutex>
#include"NetworkModule/inMessage.h"
#include"NetworkModule/outMessage.h"


void controlLoop(inMessage* my_inMessage, outMessage* my_outMessage){
    std::string  psi_D;
    std::string  task1;
    StepperMotor step;
    my_outMessage->writeMessage("10","100");
    while(true){
        if (my_inMessage->getReceivedNewMessage() == true){
            my_inMessage->readMessage(psi_D,task1);
            if (task1 == "OFF"){
                
                step.turnOff();
            }
            else if(task1 == "CW"){
                step.turnClockwise(my_inMessage);
            }
            else if(task1 ==  "CCW"){
                step.turnCounterClockwise(my_inMessage);
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
    TCPServer myTcpServer;
    inMessage* my_inMessage = new inMessage();
    outMessage* my_outMessage = new outMessage();
 
    //TCPServer myTcpServer = new TCPServer(11999,my_inMessage,my_outMessage);
    //TCPServer *myTcpServer = new TCPServer();
    myTcpServer.setup(11999);
    thread t1(&TCPServer::TCPCommunicationLoop,&myTcpServer,my_inMessage,my_outMessage);
    t1.detach();
    //thread t2(receiveWrapper);
    thread t2(controlLoop,my_inMessage,my_outMessage);
    t2.detach();
    myTcpServer.receive();

    }
