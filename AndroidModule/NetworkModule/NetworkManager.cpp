#include "TCPClient.h"
#include "NetworkManager.h"
#include <string>
#include <sstream>

NetworkManager::NetworkManager(OutMessage *mOutMessage, InMessage *mInMessage):myOutMessage(mOutMessage),myInMessage(mInMessage)
{
    isConnected = false;
}

bool NetworkManager::sendOutMessage(){
return (myTcpClient.Send(myOutMessage->State + " " + myOutMessage->Psi_d));
}

void NetworkManager::receiveInMessage(){
    string msg = myTcpClient.receive();
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
    }
}
    

void NetworkManager::connect(string IP){
    while(!isConnected){ 
    if(myTcpClient.setup("127.0.0.1",11999))
    {
    isConnected = true;
    }
    sleep(1);
    }
}

void NetworkManager::networkLoop(){
    connect("hei");
 
    while(1){
        if (!sendOutMessage()){
            isConnected =false;
            myTcpClient.closeSocket();
            connect("hei");
            sendOutMessage();
        } 
        receiveInMessage();
        usleep(10000);
    }
}




