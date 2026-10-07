
#ifndef _CRecordControlRequest
#define _CRecordControlRequest

#include "PcRequest.h"

struct TGT_TO_PC_RECORD_CONTROL_REPLY;

class CRecordControlRequest : public CPcRequest
{
	private:
		int ReadEvents (TGT_TO_PC_RECORD_CONTROL_REPLY *pReplyMsg);

	public:
		CRecordControlRequest();
		virtual ~CRecordControlRequest();
		virtual int   Execute(void *pRequest, void *pReply);
};

#endif 