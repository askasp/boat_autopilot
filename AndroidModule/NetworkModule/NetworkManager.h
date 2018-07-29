#include "OutMessage.h"
#include "InMessage.h"
#include <vector>
#include <string>


class NetworkManager{
    public:
        NetworkManager(OutMessage *mOutMessage, InMessage *mInMessage);
       void networkLoop();

    private:
        OutMessage *myOutMessage;
        InMessage *myInMessage;
        bool sendOutMessage();
        void receiveInMessage();
        void connect(string IP);
        TCPClient myTcpClient;
        bool isConnected;
        std::mutex write;
        std::mutex read;
        int nrReaders; 
};
