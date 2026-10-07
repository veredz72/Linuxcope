
#ifndef _CRecordControlRequest
#define _CRecordControlRequest

#include "PcRequest.h"

class CRecordControlRequest : public CPcRequest
{
	private:

	public:
		CRecordControlRequest();
		virtual ~CRecordControlRequest();
		virtual int   Execute(void *pRequest, void *pReply);
};

#endif 