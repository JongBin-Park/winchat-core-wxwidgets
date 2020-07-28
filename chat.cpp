#include "chat.h"

using namespace std;

void initSockets( Sockets **list )
{
    if( *list == nullptr )
    {
        *list = new Sockets;
        (*list)->ptr = nullptr;
        log("Initialize socket list");
    }
    return;
}

SOCKET* getSocket( Sockets *list, string id )
{
    if( list == nullptr )
    {
        log("List is nullptr");
        return nullptr;
    }

    Sockets *cur = list;
    while( cur != nullptr )
    {
        if( cur->id.compare(id) == 0 )
        {
            log( "Find socket : " + cur->id );
            return cur->socket;
        }

        cur = cur->ptr;
    }
}

void addSocket( Sockets *list, string id, SOCKET *socket )
{
    if( list == nullptr )
    {
        log( "List is nullptr" );
        return;
    }

    Sockets *cur = list;
    while( cur->ptr != nullptr )
    {
        cur = cur->ptr;
    }
    Sockets *newSocket = new Sockets;
    newSocket->id = id;
    newSocket->socket = socket;
    newSocket->ptr = nullptr;

    cur->ptr = newSocket;

    log( "Add Socket : " + id );
}

void delSocket( Sockets *list, string id )
{
    if( list == nullptr )
    {
        log( "List is nullptr" );
        return;
    }

    Sockets *cur = list->ptr;
    Sockets *preCur = nullptr;
    while( cur != nullptr )
    {
        if( cur->id.compare(id) == 0 )
        {
            if( preCur == nullptr )
            {
                list->ptr = cur->ptr;
                delete cur;
                log( "Delete Socket : " + id );
            }
            else
            {
                preCur->ptr = cur->ptr;
                delete cur;
                log( "Delete Socket : " + id );
            }
        }

        cur = cur->ptr;
        preCur = cur;
    }
}

Server::Server(string ip, string port)
{
    // Initialize Status variable
    this->isListen = false;
    this->list = nullptr;
    initSockets(&this->list);

    // Initialize mutex
    pthread_mutex_init( &this->mutex, NULL );

    // Initialize server socket
    if( WSAStartup( MAKEWORD( 2, 2 ), &this->wsaData) != 0 )
    {
        log( "Failed WSAStartup()" );
        return;
    }

    hSocket = socket( PF_INET, SOCK_STREAM, 0 );
    if( hSocket == INVALID_SOCKET )
    {
        log( "Failed socket()" );
        return;
    }

    svrAddr.sin_family = AF_INET;
    svrAddr.sin_addr.s_addr = inet_addr( ip.c_str() );
    svrAddr.sin_port = htons( stoi(port) );

    if( bind( this->hSocket, (LPSOCKADDR)&this->svrAddr, sizeof( this->svrAddr ) ) != ERROR_SUCCESS )
    {
        log( "Failed bind()" );
        return;
    }

    if( listen( this->hSocket, SOMAXCONN ) != ERROR_SUCCESS )
    {
        log( "Failed listen()" );
        return;
    }
    else
    {
        this->isListen = true;
    }
}

Server::~Server()
{
    if( this->isListen )
    {
        closesocket( this->hSocket );
        WSACleanup();
        log("Clean server class");
    }
}

void Server::runThread(Server *server)
{
    pthread_create( &this->th1, NULL, &Server::startAccept, server);
    pthread_create( &this->th2, NULL, &Server::processMessage, server);
}

void* Server::startAccept(void *server)
{
    log("run Thread1 (startAccept)");

    Server *svr = (Server *)server;

    int len = 0;
    len = sizeof( svr->cntAddr );

    while( svr->isListen )
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

        svr->hCntSock = new SOCKET;
        *svr->hCntSock = accept( svr->hSocket, &svr->cntAddr, &len );

        // Parameter shared thread1, thread2 (Critical session)
        pthread_mutex_lock( &svr->mutex );
        if( *svr->hCntSock != INVALID_SOCKET )
        {
            // Get ID
            int length = 0;
            recv( *svr->hCntSock, (char*)&length, sizeof(int), 0 );

            log( to_string(length) + " 받음");

            char *recvID = NULL;
            recvID = new char[length];
            recv( *svr->hCntSock, (char*)recvID, length, 0 );

            if( sizeof(recvID) > 0 )
            {
                log( "Get ID : " + (string)recvID );
                addSocket( svr->list, (string)recvID, svr->hCntSock );
                log( "Add ID : " + (string)recvID );
            }
        }
        pthread_mutex_unlock( &svr->mutex );
    }
    return NULL;
}

void* Server::processMessage(void *server)
{
    log("run Thread2 (processMessage)");

    Server *svr = (Server *)server;

    int length = 0;

    while( svr->isListen )
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

        Sockets *cur = svr->list->ptr;

        // Parameter shared thread1, thread2 (Critical session)
        pthread_mutex_lock( &svr->mutex );

        while( cur != nullptr )
        {
            if( *cur->socket != INVALID_SOCKET && cur != nullptr )
            {
                if ( recv( *cur->socket, (char*)&length, sizeof(int), 0 ) > 0 )
                {
                    log( "Get message size : " + to_string(length) );
                    char *recvMsg = new char[length];
                    recv( *cur->socket, (char*)recvMsg, length, 0 );
                    Message *msg = (Message*)recvMsg;

                    log( "Receive message from client" );
                    log( "to : " + msg->to );
                    log( "from : " + msg->from );
                    log( "contents : " + msg->contents );

                    Sockets *tmp = svr->list->ptr;
                    while( tmp != nullptr)
                    {
                        if( msg->to.compare( tmp->id ) == 0 )
                        {
                            send( *cur->socket, (char*)&length, sizeof(int), 0 );
                            send( *cur->socket, (char*)recvMsg, length, 0 );
                            log("Send message to client");
                        }
                        tmp = tmp->ptr;
                    }
                    delete recvMsg;
                }

            }
            else
            {
                closesocket( *cur->socket );
                log( "Delete invalid socket");
            }
            cur = cur->ptr;
        }
        pthread_mutex_unlock( &svr->mutex );
    }
    return NULL;
}

void Server::stopThread(Server *server)
{
    pthread_cancel( server->th1 );
    pthread_cancel( server->th2 );
    pthread_join( server->th1, NULL );
    pthread_join( server->th2, NULL );

    return;
}

Client::Client(string ip, string port, string id)
{
    // Initialize Status variable
    this->isConnect = false;
    this->id = id;

    // Initialize mutex
    pthread_mutex_init( &this->mutex, NULL );

    // Initialize server socket
    if( WSAStartup( MAKEWORD( 2, 2 ), &this->wsaData) != 0 )
    {
        log( "Failed WSAStartup()" );
        return;
    }

    hSocket = socket( PF_INET, SOCK_STREAM, 0 );
    if( hSocket == INVALID_SOCKET )
    {
        log( "Failed socket()" );
        return;
    }

    svrAddr.sin_family = AF_INET;
    svrAddr.sin_addr.s_addr = inet_addr( ip.c_str() );
    svrAddr.sin_port = htons( stoi(port) );

    if( connect( this->hSocket, (LPSOCKADDR)&this->svrAddr, sizeof(this->svrAddr) ) != ERROR_SUCCESS )
    {
        log("Failed connect()");
        return;
    }
    else
    {
        int length = id.size();
        send( this->hSocket, (char*)&length, sizeof(int), 0 );
        send( this->hSocket, (char*)id.c_str(), length, 0 );

        this->isConnect = true;
    }
}

Client::~Client()
{
    if( this->isConnect )
    {
        closesocket( this->hSocket );
        WSACleanup();
        log("Clean client class");
    }
}

void Client::runThread(Client *cnt)
{
    pthread_create( &this->th1, NULL, &Client::startReceive, (void *)cnt );
}

void* Client::startReceive(void *client)
{
    log("run Thread1 (startReceive)");

    int length = 0;

    Client *cnt = (Client *)client;
    char *recvMsg;
    Message *msg;
    while( cnt->isConnect )
    {
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

        // Parameter shared (Critical session)
        pthread_mutex_lock( &cnt->mutex );
        if( recv( cnt->hSocket, (char*)&length, sizeof(int), 0 ) > 0 )
        {
            recvMsg = new char[length];

            recv( cnt->hSocket, (char*)recvMsg, length, 0 );
            msg = (Message *)recvMsg;

            log("Receive message from server");
            log("to : " + msg->to );
            log("from : " + msg->from );
            log("contents : " + msg->contents );

            delete recvMsg;
        }


        pthread_mutex_unlock( &cnt->mutex );
    }
}

void Client::sendMessage(string contents, string to)
{
    Message msg;
    msg.from = this->id;
    msg.to = to;
    msg.contents = contents;

    if( this->isConnect )
    {
        int length = 0;
        length = sizeof(msg);

        send( this->hSocket, (char*)&length, sizeof(int), 0 );
        send( this->hSocket, (char*)&msg, length, 0 );

        log("Send message");
        return;
    }
    else
    {
        log("Not connected");
        return;
    }
}

void Client::stopThread(Client *client)
{
    pthread_cancel( client->th1 );
    pthread_join( client->th1, NULL );

    return;
}
