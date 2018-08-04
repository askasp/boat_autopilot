
#include "NetworkManager.h"
#include "TCPClient.h"
#include "Inbox.h"
#include "Outbox.h"

NetworkManager::NetworkManager(Outbox *mOutbox, Inbox *mInbox)
    :myOutbox(mOutbox),myInbox(mInbox)
{
    isConnected = false;
    std::string noe ="20";
    IP = "192.168.43.1";  //Simulator variable is set from makefile by changing the compiler
    #ifdef SIMULATOR
        IP="127.0.0.1";
    #endif

}

bool NetworkManager::sendOutbox(){
return (myTcpClient.Send(myOutbox->getPsiNow() + " " + myOutbox->getPsiFiltered()));
}

void NetworkManager::updateInbox(){
    string msg = myTcpClient.receive();
    if(msg != "" && msg!=myInbox->rawMsg){
        std::cout << msg << std::endl;
        myInbox->updateInbox(msg);
    }
}


void NetworkManager::connectToAndroidServer(){
    while(!isConnected){ 
    if(myTcpClient.setup(IP,11999))
    {
    isConnected = true;
    }
    sleep(1);
    }
}

void NetworkManager::androidCommunicationTask(){
    connectToAndroidServer();
    while(1){
        if (!sendOutbox()){
            isConnected =false;
            myTcpClient.closeSocket();
            connectToAndroidServer();
        }
        updateInbox();
        usleep(1000);
    }
}




