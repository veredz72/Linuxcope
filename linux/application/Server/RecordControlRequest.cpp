#include "stdio.h"
#include "string.h"

#include "LinuxcopeAdmin.h"
#include "RecordControlRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordControlRequest::CRecordControlRequest()
{
	m_RequestId = RECORD_CONTROL_REQUEST_CODE;
	m_pEventsTable = new LINUXCOPE_ADMIN_EVENT_DESC[16];
}

/*****************************************************************************************************/
CRecordControlRequest::~CRecordControlRequest()
{
}

/*****************************************************************************************************/
int CRecordControlRequest::ReadEvents (TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg)
{
	int NofEvents;

	LinuxcopeAdminReadEvents (&NofEvents, m_pEventsTable);
	for (int i=0;i<NofEvents;i++)
	{
		printf ("%d. %s %d\n",i, m_pEventsTable[i].Name, m_pEventsTable[i].Id);
	}

}

/*****************************************************************************************************/
int CRecordControlRequest::Execute(void *pRequest, void *pReply)
{
	PC_TO_TGT_RECORD_CONTROL_REQUEST *pRequestMsg = (PC_TO_TGT_RECORD_CONTROL_REQUEST *)pRequest;
	TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg = (TGT_TO_PC_RECORD_CONTROL_REPLY *)pReply;
	
	//Start record
	if (pRequestMsg->Control==1)
	{
		printf ("Start record\n");
		LinuxcopeAdminRecordControl (true);
		pReplyMsg->Header.Length = sizeof(TGT_TO_PC_HEADER);
	}
	else //Stop record: read all events 
	{
		printf ("Stop record\n");
		LinuxcopeAdminRecordControl (false);
		ReadEvents (pReplyMsg);
		pReplyMsg->Header.Length = sizeof(TGT_TO_PC_RECORD_CONTROL_REPLY);
	}

	pReplyMsg->Header.Code = RECORD_CONTROL_REPLY_CODE;
	pReplyMsg->Header.Magic = TGT_TO_PC_MAGIC;

	return 0;
}

