#ifndef __CHAT_H__
#define __CHAT_H__

#include <winsock2.h>
#include <string>
#include <thread>
#include "common.h"

// 연결된 소켓들 리스트
typedef struct __SocketList
{
    string sender;
    SOCKET socket;
    struct __SocketList *nextPointer;
} SocketList;

void addSocket(SocketList **, string, SOCKET);
void delSocket(SocketList *, string);
SOCKET getSocket(SocketList *, string);
SOCKET *getAllSocket(SocketList *);

// chat에서 사용할 메세지 구조체
typedef struct __Message
{
    string dateTime;
    string sender;
    string receipient;
    string contents;
} Message;

class Server
{
public:
    bool isBind;
    bool isListen;

private:
    string ip;
    string port;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN serverAddr;

    SocketList *socketList;

    SOCKET acceptSocket;
    sockaddr acceptAddr;
public:
    Server(string, string);
    ~Server();
    static string getMyIP();
    void startup(); // thread : function for to accept client
    void processMessage(); // thread : function for to process "Message"
};

class Client
{
public:
    bool isConnect;
private:
    string ip;
    string port;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN serverAddr;
public:
    Client(string, string);
    ~Client();

};

#endif // __CHAT_H__
