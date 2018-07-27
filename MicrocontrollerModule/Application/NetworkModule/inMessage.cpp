
#include "inMessage.h"

inMessage::inMessage(){
    psi_Desired = "0";
    task = "0";
    receivedNewMessage = false;
}

void inMessage::writeMessage(std::string rawMsgIn)
{   
    inMessageMutex.lock();
    std::stringstream ss(rawMsgIn);
    rawMsg=rawMsgIn;

    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    task = vstrings[0];
    psi_Desired= vstrings[1];
    receivedNewMessage = true;
    inMessageMutex.unlock();
}

bool inMessage::getReceivedNewMessage(){
    inMessageMutex.lock();
    bool tmp = receivedNewMessage;
    inMessageMutex.unlock();
    return tmp;
}

void inMessage::readMessage(std::string& psi_D, std::string& task1){
    inMessageMutex.lock();
    psi_D = psi_Desired;
    task1= task;
    receivedNewMessage = false;
    inMessageMutex.unlock();
}
