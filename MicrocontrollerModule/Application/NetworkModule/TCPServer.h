#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <mutex>
#include<sstream>
#include <iterator>
#include "inMessage.h"
#include "outMessage.h"

using namespace std;

#define MAXPACKETSIZE 4096

class TCPServer
{
	public:
//	TCPServer(int port, inMessage* m_inMessage,outMessage* m_outMessage);
	int sockfd, newsockfd, n, pid;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	pthread_t serverThread;
	char msg[ MAXPACKETSIZE ];
	static string Message;

	void setup(int port);
	string receive();
	string getMessage();
	void Send(string msg);
	void detach();
	void clean();

    void TCPCommunicationLoop(inMessage* min, outMessage* mout);
	private:
	inMessage *my_inMessage;
	outMessage *my_outMessage;
	static void * Task(void * argv);
};

#endif
