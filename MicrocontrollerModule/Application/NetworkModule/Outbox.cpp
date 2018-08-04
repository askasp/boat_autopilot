#include "Outbox.h"

void Outbox::updateOutbox(std::string psinow,std::string psifiltered){
    OutboxMutex.lock();
    psiNow = psinow;
    psiFiltered = psifiltered;
    OutboxMutex.unlock();
}
std::string Outbox::getPsiNow(){
    std::string tmp;
    OutboxMutex.lock();
    tmp = psiNow;
    OutboxMutex.unlock();
    return tmp;
}
std::string Outbox::getPsiFiltered(){
    std::string tmp;
    OutboxMutex.lock();
    tmp = psiFiltered;
    OutboxMutex.unlock();
    return tmp;
}
