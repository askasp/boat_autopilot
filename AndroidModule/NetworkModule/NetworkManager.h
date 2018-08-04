#include "OutMessage.h"
#include "InMessage.h"
#include <vector>
#include <string>
#include "TCPServer.h"
#include <sstream>


class NetworkManager{
    public:
        NetworkManager(OutMessage *mOutMessage, InMessage *mInMessage);
       void networkLoop();

    private:
        OutMessage *myOutMessage;
        InMessage *myInMessage;
        void sendOutMessage();
        bool receivedInMessage();
        void connect(string IP);
//        TCPClient myTcpClient;
        TCPServer myTCPServer;
        bool isConnected;
        std::mutex write;
        std::mutex read;
        int nrReaders; 
};
