#include "outMessage.h"

void outMessage::writeMessage(std::string psi_now,std::string psi_filtered){
    outMessageMutex.lock();
    psi_Now = psi_now;
    psi_Filtered = psi_filtered;
    outMessageMutex.unlock();
}
std::string outMessage::getPsi_Now(){
    std::string tmp;
    outMessageMutex.lock();
    tmp = psi_Now;
    outMessageMutex.unlock();
    return tmp;
}
std::string outMessage::getPsi_Filtered(){
    std::string tmp;
    outMessageMutex.lock();
    tmp = psi_Filtered;
    outMessageMutex.unlock();
    return tmp;
}
