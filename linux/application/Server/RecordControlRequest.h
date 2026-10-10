
#ifndef _CRecordControlRequest
#define _CRecordControlRequest

#include "PcRequest.h"

#define FILE_PATH			"/mnt/ramdisk/linuxcope.bin"

struct TGT_TO_PC_RECORD_CONTROL_REPLY;
struct LINUXCOPE_ADMIN_EVENT_DESC;

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