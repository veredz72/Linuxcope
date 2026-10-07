
#include "stdio.h"

#include "BaseProtocol.h"
#include "Catalog.h"
#include "TcpServer.h"
#include "RecordControlRequest.h"

/****************************************************************************/
CBaseProtocol::CBaseProtocol()
{
	m_pPcToTgtRequest = new PC_TO_TGT_REQUEST_U;
	m_pTgtToPcReply = new TGT_TO_PC_REPLY_U;
	m_pCatalog = new CCatalog;
	m_pTcpServer = new CTcpServer();

	RegisterRequests();
}

/****************************************************************************/
CBaseProtocol::~CBaseProtocol()
{
}

/****************************************************************************/
int CBaseProtocol::RegisterRequests(void)
{
	CRecordControlRequest  *pRecordControlRequest = new CRecordControlRequest();
	m_pCatalog->RegisterObject(pRecordControlRequest->GetId(), pRecordControlRequest);
	
	return 0;
}

/****************************************************************************/
int CBaseProtocol::Handle(int Code)
{
	if (m_pCatalog->GetObjectPtr(Code) == 0)
	{
		printf("GetObjectPtr(%d) is null\n", Code);
		return 0;
	}

	CPcRequest *pRequest = (CPcRequest *)m_pCatalog->GetObjectPtr(Code);
	pRequest->Execute(m_pPcToTgtRequest, m_pTgtToPcReply);

	return 0;
}