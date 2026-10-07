
#include "pthread.h"
#include "stdio.h"

#include "TcpProtocol.h"
#include "TcpServer.h"
#include "PcToTgtIcd.h"
#include "TgtToPcIcd.h"

/****************************************************************************/
CTcpProtocol::CTcpProtocol()
{
}


/****************************************************************************/
CTcpProtocol::~CTcpProtocol()
{
}

/****************************************************************************/
int CTcpProtocol::Open()
{
	m_pTcpServer->Open(PC_TO_TGT_TCP_PORT);
	printf("Waiting for host connection...\n");

	m_pTcpServer->AcceptConnection();
	printf("Connection established\n");

	return 0;
}

/****************************************************************************/
int CTcpProtocol::Init()
{
	pthread_t ThreadId;
	pthread_attr_t ThreadAttr;
	struct sched_param SchedParam;

	pthread_attr_init(&ThreadAttr);
	pthread_attr_setstacksize(&ThreadAttr, 1024 * 10);
	pthread_create(&ThreadId, 0, (void* (*)(void*))&(Thread), this);

	return 0;
}

/****************************************************************************/
int CTcpProtocol::Reply(void)
{
	int rc;

	TGT_TO_PC_HEADER	*pHeader = (TGT_TO_PC_HEADER *)m_pTgtToPcReply;
	uint32_t Rest = pHeader->Length;
	char *pSrc = (char*)m_pTgtToPcReply;

	while (Rest > 0)
	{
		rc = m_pTcpServer->Send(pSrc, Rest);
		Rest -= rc;
		pSrc += rc;
	}

}

/****************************************************************************/
int CTcpProtocol::Loop()
{
	PC_TO_TGT_HEADER *pHeader = (PC_TO_TGT_HEADER *)m_pPcToTgtRequest;
	int rc;
	char *pDst = (char*)m_pPcToTgtRequest;
	int Rest;
	uint32_t *p;

	while (1)
	{
		pDst = (char*)m_pPcToTgtRequest;
		rc = m_pTcpServer->Receive(pDst, sizeof(PC_TO_TGT_HEADER));
		if (rc == 0)
		{
			printf("Host disconnected.\n");
			m_pTcpServer->AcceptConnection();
			continue;
		}
		pDst += sizeof(PC_TO_TGT_HEADER);
		Rest = pHeader->Length - rc;

		while (Rest > 0)
		{
			rc = m_pTcpServer->Receive(pDst, Rest);
			Rest = Rest - rc;
			pDst += rc;
		}

		if (pHeader->Code >= LAST_REQUEST_CODE)
			printf("Code=%x\n", pHeader->Code);
		else
		{
			Handle(pHeader->Code);
			Reply();
		}
	}
}

/****************************************************************************/
int CTcpProtocol::Thread(void *lpParam)
{
	CTcpProtocol *pTcpProtocol = (CTcpProtocol *)lpParam;

	pTcpProtocol->Open();
	pTcpProtocol->Loop();

	return 0;
}