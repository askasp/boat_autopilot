
#include "Inbox.h"

Inbox::Inbox(){
    psiDesired = "0";
    task = "0";
    isUnread = false;
}

void Inbox::updateInbox(std::string rawMsgIn)
{   
    inboxMutex.lock();
    std::stringstream ss(rawMsgIn);
    rawMsg=rawMsgIn;

    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    task = vstrings[0];
    psiDesired= vstrings[1];
    isUnread = true;
    inboxMutex.unlock();
}

bool Inbox::isInboxUnread(){
    inboxMutex.lock();
    bool tmp = isUnread;
    inboxMutex.unlock();
    return tmp;
}

void Inbox::readInbox(std::string& psiD, std::string& task1){
    inboxMutex.lock();
    psiD = psiDesired;
    task1= task;
    isUnread = false;
    inboxMutex.unlock();
}
