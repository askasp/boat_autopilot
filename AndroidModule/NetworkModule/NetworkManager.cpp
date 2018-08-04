#include "NetworkManager.h"
#include <thread>

NetworkManager::NetworkManager(Outbox *mOutbox, Inbox *mInbox)
    :myOutbox(mOutbox),myInbox(mInbox)
{
    isConnected = false;
    myTCPServer.setup(11999);
    std::thread t1(&TCPServer::receive,&myTCPServer);
    t1.detach();
}

void  NetworkManager::sendOutbox(){
    (myTCPServer.Send(myOutbox->State + " " + myOutbox->Psi_d));
}

bool NetworkManager::updateInbox(){
    string msg = myTCPServer.getMessage();
    if(msg != ""){
        std::cout << msg << std::endl;
        std::stringstream ss(msg);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> results(begin, end);
        QString temp = QString::fromStdString(results[0]);
        QString temp1 = QString::fromStdString(results[1]);
        myInbox->Psi = temp.toInt();
        myInbox->SteeringAngle=temp1.toInt();
        myInbox->notifyQML();
        return true;
    }
    return false;
}

void NetworkManager::RpiCommunicationTask(){
    while(1){
        if (updateInbox()){
            sendOutbox();
        }
        usleep(10000);
    }
}



