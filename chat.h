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
    static void *startup(void *); // thread : function for to accept client
    static void *processMessage(void *); // thread : function for to process "Message"
};

class Client
{
public:
    bool isConnect;
private:
    string ip;
    string port;
    string sender;

    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN serverAddr;
public:
    Client(string, string, string);
    ~Client();

};

#endif // __CHAT_H__
