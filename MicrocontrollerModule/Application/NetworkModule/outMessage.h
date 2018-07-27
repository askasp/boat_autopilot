
#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include<sstream>
#include <iterator>
#include <vector>
class outMessage 
{
    private:
        std::mutex outMessageMutex;
        std::string psi_Now;
        std::string psi_Filtered;

    public:

       void writeMessage(std::string psi_now,std::string psi_filtered);
       std::string getPsi_Now();
       std::string getPsi_Filtered();
};
