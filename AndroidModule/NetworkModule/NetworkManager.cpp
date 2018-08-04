#include "NetworkManager.h"
#include <thread>

NetworkManager::NetworkManager(OutMessage *mOutMessage, InMessage *mInMessage)
    :myOutMessage(mOutMessage),myInMessage(mInMessage)
{
    isConnected = false;
    myTCPServer.setup(11999);
    std::thread t1(&TCPServer::receive,&myTCPServer);
    t1.detach();
}

void  NetworkManager::sendOutMessage(){
    (myTCPServer.Send(myOutMessage->State + " " + myOutMessage->Psi_d));
}

bool NetworkManager::receivedInMessage(){
    string msg = myTCPServer.getMessage();
    if(msg != ""){
    
            std::stringstream ss(msg);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> results(begin, end);
             QString temp = QString::fromStdString(results[0]);
    QString temp1 = QString::fromStdString(results[1]);
    myInMessage->Psi = temp.toInt();
    myInMessage->SteeringAngle=temp1.toInt();

    myInMessage->notifyQML();
    return true;
    }
    return false;
}
    


void NetworkManager::networkLoop(){
    while(1){
        if (receivedInMessage()){
            sendOutMessage();
        }
        usleep(10000);
    }
}



