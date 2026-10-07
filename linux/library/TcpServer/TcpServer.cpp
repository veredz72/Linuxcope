// udp.cpp : Defines the entry point for the DLL application.
//

#include "TcpServer.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include <errno.h>
#include <arpa/inet.h>

/**********************************************************************/
int CTcpServer::Open (int Port)
{
	int rc;
	int sockAddrSize = sizeof (struct sockaddr_in);
	int enable = 1;

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket < 0)
	{
		printf ("CTcpServer::Open : socket failed\n");
		return -1;
	}

	memset ((char *) &m_ServerAddress, 0,sizeof (sockaddr_in)); 
    
	m_ServerAddress.sin_family = AF_INET; 
    m_ServerAddress.sin_port = htons (Port); 
 	m_ServerAddress.sin_addr.s_addr = htonl (INADDR_ANY);

	if (setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		printf("setsockopt(SO_REUSEADDR) failed");
		return -1;
	}

	if (bind (m_Socket, (struct sockaddr *)&m_ServerAddress, sockAddrSize)<0)
	{
		printf ("Open: bind failed. errno=%d %s\n", errno, strerror(errno));
		return -1;
	}

	if (listen (m_Socket,1)<0)
	{
		printf ("CTcpServer::Open : listen failed. errno=Unknown\n");
		return -1;
	}

	

	return 0;
}

/**********************************************************************/
int CTcpServer::AcceptConnection (void)
{
	socklen_t sockAddrSize = sizeof (struct sockaddr_in);
	sockaddr_in  ClientAddress;

	m_ListenSocket = accept(m_Socket, (struct sockaddr *) &ClientAddress, &sockAddrSize);
	if (m_ListenSocket < 0)
	{
		printf ("CTcpClient::AcceptConnection : accept failed. errno=Unknown\n");
		return -1;
	}

	printf("Ip=%s\n", inet_ntoa(ClientAddress.sin_addr));
	return 0;
}

/**********************************************************************/
int CTcpServer::Send (void *pBuffer, int Size)
{
	int rc;

	rc=send (m_ListenSocket,(char*)pBuffer,Size ,0);

	return rc;
}

/**********************************************************************/
int CTcpServer::Receive (void *pBuffer, int Size)
{
	int rc=0;

	rc=recv (m_ListenSocket,(char*)pBuffer,Size,0);

	return rc;
}

/**********************************************************************/
int CTcpServer::Close(void)
{
	int rc;

	rc = close(m_ListenSocket);
	return rc;
}
