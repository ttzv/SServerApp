
SOCKET mainSocket;
SOCKET acceptSocket;

int TCP_INIT()
{
    WSADATA wsaData;

int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
if( result != NO_ERROR )
     printf( "Initialization error.\n" );



mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if( mainSocket == INVALID_SOCKET )
{
    std::cout<<"Error creating socket: "<<WSAGetLastError();
    WSACleanup();
    return 1;
}


sockaddr_in service;
memset( & service, 0, sizeof( service ) );
service.sin_family = AF_INET;
service.sin_addr.s_addr = inet_addr( "127.0.0.1" );
service.sin_port = htons( 10001 );


if( bind( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
{
    printf( "bind() failed.\n" );
    closesocket( mainSocket );
    return 1;

}


if( listen( mainSocket, 1 ) == SOCKET_ERROR )
     printf( "Error listening on socket.\n" );

acceptSocket = SOCKET_ERROR;
    return 1;
}

bool TCP_CON()
{
    while( acceptSocket == SOCKET_ERROR )
    {
        acceptSocket = accept( mainSocket, NULL, NULL );

    }
    mainSocket = acceptSocket;

    return true;
}

void TCP_readNewEQCoords (double& RA, double& DEC)
{
    bytesRecv = recv( mainSocket, recvbuf, 20, 0 );

    if (bytesRecv == 20)
    {
        int *intarr=(int *) recvbuf; //4-bajtowe liczby utworzone z 1-bajtowych znakow

        //for (int i=0;i<=19;i++) {cout<<"recv "<<i<<":"<<(long int)recvbuf[i]<<endl;}

        unsigned long int intRA = intarr[3];
        int intDEC = intarr[4];
        RA = (intRA * 0.00000008381903172) / 15; //RA w godzinach
        DEC = intDEC * 0.00000008381903172; //DEC w stopniach
        //cout<<"intRA: "<<intRA<<endl<<"intDEC: "<<intDEC<<endl<<"RAh: "<<RA<<endl<<"DECd: "<<DEC<<endl;
        //bytesSent = send( mainSocket, recvbuf, 24, 0 );
        //printf( "Bytes sent: %ld\n", bytesSent );
    }
}




