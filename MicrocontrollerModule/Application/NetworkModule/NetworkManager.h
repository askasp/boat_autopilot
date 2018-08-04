#include "Inbox.h"
#include "Outbox.h"

#include "Outbox.h"
#include "TCPClient.h"
#include "Inbox.h"
#include <vector>
#include <string>


class NetworkManager{
    public:
        NetworkManager(Outbox *mOutbox, Inbox *mInbox);
       void androidCommunicationTask();

    private:
        Outbox *myOutbox;
        Inbox *myInbox;
        bool sendOutbox();
        void updateInbox();
        void connectToAndroidServer();
        TCPClient myTcpClient;
        bool isConnected;
        std::mutex write;
        std::mutex read;
        int nrReaders; 
        std::string IP;
};
