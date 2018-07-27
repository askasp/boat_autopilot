

#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include<sstream>
#include <iterator>
#include <vector>

class inMessage
{
    private:
        std::string psi_Desired;
        std::string task;
        std::mutex inMessageMutex;
        bool receivedNewMessage;
    public:
        std::string rawMsg = "";
        inMessage();
        void writeMessage(std::string rawMsgIn);
        bool getReceivedNewMessage();
        void readMessage(std::string& psi_D, std::string& task1);
};

