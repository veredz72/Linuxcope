
typedef enum E_TGT_TO_PC_CODE
{
	RECORD_CONTROL_REPLY_CODE = 1,
    LAST_REPLY_CODE				
}E_TGT_TO_PC_CODE;

#define N_MAX_RECORDS    1024
#define N_MAX_EVENTS	 16

/***************************************************/
typedef struct TGT_TO_PC_HEADER
{
	uint32_t			Magic;
	E_TGT_TO_PC_CODE	Code;
	uint32_t			Length;
}TGT_TO_PC_HEADER;

/***************************************************/
typedef struct EVENT_RECORD
{
	uint32_t Id;
	uint32_t Value;
	uint32_t TimetagLsw;
	uint32_t TimetagMsw;
}EVENT_RECORD;

/***************************************************/
typedef struct EVENT_DESC
{
	uint32_t Name[2];
	uint32_t Id;
}EVENT_DESC;

/***************************************************/
typedef struct TGT_TO_PC_RECORD_CONTROL_REPLY
{
	TGT_TO_PC_HEADER	Header;
	uint32_t 			NofEvents;				//N Events in table 
	uint32_t 			NofRecords;				//N Events in log file 
	EVENT_DESC			Event[N_MAX_EVENTS];
	EVENT_RECORD		Record[N_MAX_RECORDS];
}TGT_TO_PC_RECORD_CONTROL_REPLY;

/***************************************************/
typedef union TGT_TO_PC_REPLY_U
{
	TGT_TO_PC_RECORD_CONTROL_REPLY			RecordControlReply;
}TGT_TO_PC_REPLY_U;

