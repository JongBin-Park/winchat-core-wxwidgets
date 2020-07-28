#ifndef __CHAT_H__
#define __CHAT_H__

#include <winsock2.h>
#include <pthread.h>
#include <string>

#include "common.h"

using namespace std;

typedef struct __Message
{
    string from;
    string to;
    string contents;
} Message;

// Queue
typedef struct __Sockets
{
    string id;
    SOCKET *socket;
    struct __Sockets *ptr;
} Sockets;
// Queue function
void initSockets(Sockets **);
SOCKET* getSocket(Sockets *, string);
void addSocket(Sockets *, string, SOCKET *);
void delSocket(Sockets *, string);

class Server
{
public:
    // Status variable
    pthread_t th1;
    pthread_t th2;
    pthread_mutex_t mutex;

    bool isListen;
private:
    // Member variable
    Sockets *list;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN svrAddr;

    SOCKET *hCntSock;
    sockaddr cntAddr;

public:
    // Member function
    Server(string, string);
    ~Server();
    void runThread(Server *svr);
    static void* startAccept(void *);
    static void* processMessage(void *);
    void stopThread(Server *svr);
};

class Client
{
public:
    // Status variable
    pthread_t th1;
    pthread_t th2;
    pthread_mutex_t mutex;

    bool isConnect;
private:
    // Member variable
    string id;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN svrAddr;

public:
    // Member function
    Client(string, string, string);
    ~Client();
    void runThread(Client *cnt);
    static void* startReceive(void *);
    void sendMessage(string, string);
    void stopThread(Client *cnt);

};


#endif // __CHAT_H__
