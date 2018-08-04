#include "Outbox.h"
#include "Inbox.h"
#include <vector>
#include <string>
#include "TCPServer.h"
#include <sstream>


class NetworkManager{
    public:
        NetworkManager(Outbox *mOutbox, Inbox *mInbox);
       void RpiCommunicationTask();

    private:
        Outbox *myOutbox;
        Inbox *myInbox;
        void sendOutbox();
        bool updateInbox();
        TCPServer myTCPServer;
        bool isConnected;
        std::mutex write;
        std::mutex read;
        int nrReaders; 
};
