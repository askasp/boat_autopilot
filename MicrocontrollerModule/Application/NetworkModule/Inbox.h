

#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include<sstream>
#include <iterator>
#include <vector>

class Inbox
{
    private:
        std::string psiDesired;
        std::string task;
        std::mutex inboxMutex;
        bool isUnread;
    public:
        std::string rawMsg = "";
        Inbox();
        void updateInbox(std::string rawMsgIn);
        bool isInboxUnread();
        void readInbox(std::string& psi_D, std::string& task1);
};

