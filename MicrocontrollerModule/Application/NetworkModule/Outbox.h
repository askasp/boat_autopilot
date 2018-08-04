
#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include<sstream>
#include <iterator>
#include <vector>
class Outbox 
{
    private:
        std::mutex OutboxMutex;
        std::string psiNow;
        std::string psiFiltered;

    public:

        void updateOutbox(std::string psi_now,std::string psi_filtered);
        std::string getPsiNow();
        std::string getPsiFiltered();
};
