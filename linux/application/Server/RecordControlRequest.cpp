#include "stdio.h"
#include "string.h"

#include "RecordControlRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordControlRequest::CRecordControlRequest()
{
	m_RequestId = RECORD_CONTROL_REQUEST_CODE;

}


CRecordControlRequest::~CRecordControlRequest()
{
}

int CRecordControlRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_RECORD_CONTROL_REQUEST *pRequestMsg = (PC_TO_TGT_RECORD_CONTROL_REQUEST *)pRequest;
	TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg = (TGT_TO_PC_RECORD_CONTROL_REPLY *)pReply;

	pReplyMsg->Header.Code = RECORD_CONTROL_REPLY_CODE;
	pReplyMsg->Header.Length = sizeof(TGT_TO_PC_RECORD_CONTROL_REPLY);
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;

	return 0;
}

