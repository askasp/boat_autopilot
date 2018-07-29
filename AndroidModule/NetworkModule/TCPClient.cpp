#include "TCPClient.h"
TCPClient::TCPClient()
{
    sock = -1;
    port = 0;
    address = "";
    errorBuf2[0] ='c';
    errorBuf2[1] ='\0';
}

bool TCPClient::setup(string address , int port)
{
    if(sock == -1)
    {
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            cout << "Could not create socket" << endl;
        }

    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    }
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";
            return false;
        }
        addr_list = (struct in_addr **) he->h_addr_list;
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            server.sin_addr = *addr_list[i];
            break;
        }
    }
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return false;
    }
    return true;
}

bool TCPClient::Send(string data)
{
    if(sock != -1) 
    {
        if( send(sock , data.c_str() , strlen( data.c_str() ) ,MSG_NOSIGNAL) < 0)
        {

            cout << "Send failed : " << data << endl;
            return false;
        }
    }
    else
        return false;
    return true;
}

string TCPClient::receive(int size)
{
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));

    string reply;
    if (read(sock , buffer , size) < 0)
    {
        cout << "receive failed!" << endl;
        return errorBuf2;
    }
    buffer[size-1]='\0';
    reply = buffer;
    return reply;
}

string TCPClient::read2()
{
    char buffer[1] = {};
    string reply;
    while (buffer[0] != '\n') {
        if( recv(sock , buffer , sizeof(buffer) ,0) < 0)
        {
            cout << "receive failed!" << endl;
            return nullptr;
            
        }
        
        reply += buffer[0];
    }
    return reply;
}

bool TCPClient::closeSocket(){
    close(sock);
    sock = -1;
    return 0;
}



void TCPClient::exit()
{
    close( sock );
}
