
#ifndef _CReadEventsRequest
#define _CReadEventsRequest

#include "PcRequest.h"

class CReadEventsRequest : public CPcRequest
{
	private:

	public:
		CReadEventsRequest();
		virtual ~CReadEventsRequest();
		virtual int   Execute(void *pRequest, void *pReply);
};

#endif 