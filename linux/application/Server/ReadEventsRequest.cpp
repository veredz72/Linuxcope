#include "stdio.h"
#include "string.h"

#include "ReadEventsRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadEventsRequest::CReadEventsRequest()
{
	m_RequestId = READ_EVENTS_REQUEST_CODE;

}


CReadEventsRequest::~CReadEventsRequest()
{
}

int CReadEventsRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_READ_EVENTS_REQUEST *pRequestMsg = (PC_TO_TGT_READ_EVENTS_REQUEST *)pRequest;
	TGT_TO_PC_READ_EVENTS_REPLY *pReplyMsg = (TGT_TO_PC_READ_EVENTS_REPLY *)pReply;

	pReplyMsg->Header.Code = RECORD_CONTROL_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_READ_EVENTS_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;

	return 0;
}

