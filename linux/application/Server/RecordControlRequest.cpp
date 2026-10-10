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
	printf ("sizeof(TGT_TO_PC_RECORD_CONTROL_REPLY)=%d\n",sizeof(TGT_TO_PC_RECORD_CONTROL_REPLY));
}

/*****************************************************************************************************/
CRecordControlRequest::~CRecordControlRequest()
{
}

/*****************************************************************************************************/
int CRecordControlRequest::ReadEvents (TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg)
{
	int NofRecords=0;
	FILE *Handle;
	EVENT_RECORD Record,*pDst;
	int rc;

	LinuxcopeAdminReadEvents ((int *)&pReplyMsg-> NofEvents, 
								(LINUXCOPE_ADMIN_EVENT_DESC *)&pReplyMsg->Event);
	
	Handle = fopen (FILE_PATH,"rb");
	if (Handle==NULL)
	{
		printf ("Failed to open %s\n",FILE_PATH);
		return -1;
	}

	printf ("sizeof(EVENT_RECORD)=%d\n",sizeof(EVENT_RECORD));
	while (1)
	{
		rc=fread (&Record,1,sizeof(EVENT_RECORD),Handle);
		if (rc!=sizeof(EVENT_RECORD))
			break;

		pDst = &pReplyMsg->Record[NofRecords];
		memcpy (pDst, &Record, sizeof(EVENT_RECORD));
		NofRecords++;
	}
	fclose (Handle);

	pReplyMsg->NofRecords = NofRecords;
	for (int i=0;i<NofRecords;i++)
	{
		printf ("Id=%d Value=%d\n",pReplyMsg->Record[i].Id, pReplyMsg->Record[i].Value);
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

