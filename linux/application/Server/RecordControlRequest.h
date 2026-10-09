
#ifndef _CRecordControlRequest
#define _CRecordControlRequest

#include "PcRequest.h"

struct TGT_TO_PC_RECORD_CONTROL_REPLY;
struct LINUXCOPE_ADMIN_EVENT_DESC;

class CRecordControlRequest : public CPcRequest
{
	private:
		LINUXCOPE_ADMIN_EVENT_DESC *m_pEventsTable;
		int ReadEvents (TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg);

	public:
		CRecordControlRequest();
		virtual ~CRecordControlRequest();
		virtual int   Execute(void *pRequest, void *pReply);
};

#endif 