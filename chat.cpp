#include "chat.h"

using namespace std;

void addSocket(SocketList **socketList, string sender, SOCKET socket)
{
    log("소켓 리스트 추가");
    SocketList *base;

    // because of declared double pointer
    if ( *socketList == NULL )
        *socketList = new SocketList();

    base = *socketList;

    string newSender = sender;
    SOCKET newSocket = socket;

    SocketList *temp = new SocketList();
    temp->sender = newSender;
    temp->socket = newSocket;

    // Queue
    while ( base->nextPointer != NULL )
    {
        // Find point
        base = base->nextPointer;
    }

    base->nextPointer = temp;
    log("추가 완료");
    return;
}

void delSocket(SocketList *socketList, string sender)
{
    log(sender + "를(을) 소켓 리스트에서 삭제");

    if ( socketList == NULL )
    {
        log("리스트가 비어있음");
        return;
    }

    SocketList *base = socketList->nextPointer;
    SocketList *prePointer = NULL;

    while ( base != NULL )
    {
        if ( sender.compare(base->sender) == 0 )
        {
            prePointer->nextPointer = base->nextPointer;
            delete base;
        }
        else
        {
            prePointer = base;
            base = base->nextPointer;
        }
    }

    log(sender + "를(을) 소켓 리스트에서 삭제 완료");
    return;
}

SOCKET getSocket(SocketList *socketList, string sender)
{
    SOCKET result;

    SocketList *cursor = socketList->nextPointer;

    while ( cursor != NULL )
    {
        if ( sender.compare(cursor->sender) == 0 )
        {
            result = cursor->socket;
            cursor = NULL;
            log(sender + " 의 소켓 반환");
        }
        else
        {
            if ( cursor->nextPointer != NULL )
                cursor = cursor->nextPointer;
            else
                cursor = NULL;
                log(sender + " 의 소켓 없음");
        }
    }

    return result;
}

SOCKET *getAllSocket(SocketList *socketList)
{
    int i;
    int length = 0;
    SOCKET *result;

    SocketList *cursor = socketList;

    while ( cursor->nextPointer != NULL )
    {
        length++;
        cursor = cursor->nextPointer;
    }

    if ( length != 0 )
    {
        result = new SOCKET[length];

        cursor = socketList;
        for ( i = 0 ; i < length ; i++ )
        {
            result[i] = cursor->nextPointer->socket;
            cursor = cursor->nextPointer;
        }
    }
    else
    {
        log("소켓이 비어있음");
        result = NULL;
    }

    log("모든 소켓 반환");
    return result;
}

Server::Server(string ip, string port)
{
    this->ip = ip;
    this->port = port;
    this->isBind = false;

    if ( WSAStartup ( MAKEWORD(2, 2), &this->wsaData ) != 0 )
    {
        log("IP : " + this->ip + " PORT : " + this->port);
        log("서버 WSA Start Up 실패");
        return;
    }

    this->hSocket = socket( PF_INET, SOCK_STREAM, 0 );
    if ( this->hSocket == INVALID_SOCKET )
    {
        log("IP : " + this->ip + "PORT : " + this->port);
        log("서버 소켓 생성 실패");
        return;
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    this->serverAddr.sin_port = htons(stoi(port));

    if ( bind( this->hSocket, (LPSOCKADDR)&this->serverAddr, sizeof(this->serverAddr) ) != ERROR_SUCCESS )
    {
        log("IP : " + this->ip + "PORT : " + this->port);
        log("서버 IP/PORT 바인딩 실패");
        this->isBind = false;
        return;
    }
    else
    {
        this->isBind = true;
    }
}

Server::~Server()
{
    closesocket(this->hSocket);
    WSACleanup();
}

string Server::getMyIP()
{
    WSADATA wsadata;
    WSAStartup( MAKEWORD(2,2), &wsadata );
    IN_ADDR addr = {0,};

    char localhostname[MAX_PATH];

    if(gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)//호스트 이름 얻어오기
    {
        return NULL;
    }
    HOSTENT *ptr = gethostbyname(localhostname);//호스트 엔트리 얻어오기
    while(ptr && ptr->h_name)
    {
        if(ptr->h_addrtype == PF_INET)//IPv4 주소 타입일 때
        {
            memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//메모리 복사
            break;//반복문 탈출
        }
        ptr++;
    }

    WSACleanup();

    return (string)inet_ntoa(addr);//IPv4 주소를 문자열로 출력
}

void Server::startup()
{
    log("*************** 서버 시작 ***************");
    if ( this->isBind )
    {
        if ( listen ( this->hSocket, SOMAXCONN ) != ERROR_SUCCESS )
        {
            log("IP : " + this->ip + "PORT : " + this->port);
            log("서버 Listen 실패");
            this->isListen = false;
            delete this;
            return;
        }
        else
        {
            this->isListen = true;
        }
    }

    while ( this->isListen )
    {
        int length = sizeof(this->acceptAddr);
        this->acceptSocket = accept( this->hSocket, &acceptAddr, &length );

        if ( this->acceptSocket == INVALID_SOCKET )
        {
            log("client accept 실패");
            continue;
        }
        else
        {
            // 아이디(송신자)를 받아야함
            char *sender;
            int len = 0;
            int comResult;
            comResult = recv( this->acceptSocket, (char*)&len, sizeof(int), 0 );

            // 사이즈에 맞게 메모리 할당
            if ( comResult > 0 )
                sender = new char[len];
            else
            {
                log("클라이언트 송신자 사이즈 받기 실패");
                continue;
            }

            comResult = recv( this->acceptSocket, (char*)sender, len, 0 );
            if ( comResult > 0 )
            {
                addSocket( &this->socketList, (string)sender, this->acceptSocket);
            }
            else
            {
                log("클라이언트 송신자 받기 실패");
                continue;
            }
        }
    }

    return;
}

void Server::processMessage()
{
    // 수시로 체크해서 처리해줘야 함
    while ( 1 == 1 )
    {
        SocketList *cursor = this->socketList->nextPointer;
        while ( cursor != NULL )
        {
            // 해당 소켓이 정상인지 확인 후
            if ( cursor->socket == INVALID_SOCKET )
            {
                delSocket(this->socketList, cursor->sender);
                log("접속된 소켓들 중 유효하지 않는 소켓 발견되어 삭제");
                continue;
            }

            // 해당하는 소켓의 Message 구조체 수신을 알아봐야한다.
            int len = 0;
            Message *msg;

            if ( recv( cursor->socket, (char*)&len, sizeof(int), 0 ) > 0 )
            {
                msg = new Message[len];
                if ( recv ( cursor->socket, (char*)msg, len, 0 ) > 0 )
                {
                    // 메세지 받았고, 클라이언트 찾아서 보내줘야 함
                    string sender = msg->sender;
                    string receipient = msg->receipient;
                    string contents = msg->contents;

                    send( getSocket(this->socketList, receipient), (char*)msg, len, 0 );
                }
            }

            cursor = cursor->nextPointer;
        }
    }
    return;
}

Client::Client(string ip, string port)
{
    this->ip = ip;
    this->port = port;

    if ( WSAStartup( MAKEWORD(2, 2), &wsaData ) != 0 )
    {
        log("클라이언트 WSA Startup 실패");
        return;
    }

    this->hSocket = socket( PF_INET, SOCK_STREAM, 0 );
    if ( this->hSocket == INVALID_SOCKET )
    {
        log("클라이언트 소켓 생성 실패");
        return;
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_addr.s_addr = inet_addr( ip.c_str() );
    this->serverAddr.sin_port = htons( stoi(port) );

    if ( connect( this->hSocket, (LPSOCKADDR)&this->serverAddr, sizeof(this->serverAddr) ) != ERROR_SUCCESS )
    {
        log("클라이언트 서버연결 실패");
        this->isConnect = false;
        return;
    }
    else
    {
        this->isConnect = true;
    }
}

Client::~Client()
{
    closesocket(this->hSocket);
    WSACleanup();
}

