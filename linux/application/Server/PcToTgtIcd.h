#define PC_TO_TGT_HTTP_PORT				8000
#define PC_TO_TGT_TCP_PORT				5100

typedef enum E_PC_TO_TGT_CODE
{
	RECORD_CONTROL_REQUEST_CODE			= 1,
	READ_EVENTS_REQUEST_CODE			= 2,
	LAST_REQUEST_CODE
}E_PC_TO_TGT_CODE;

#define TGT_TO_PC_MAGIC  0xCAFE2DAD

/***************************************************/
typedef struct PC_TO_TGT_HEADER
{
	uint32_t	Magic;
	E_PC_TO_TGT_CODE Code;
	int32_t	Length;
}PC_TO_TGT_HEADER;

/***************************************************/
typedef struct PC_TO_TGT_RECORD_CONTROL_REQUEST
{
	PC_TO_TGT_HEADER Header;
	uint32_t Control;
}PC_TO_TGT_RECORD_CONTROL_REQUEST;

/***************************************************/
typedef struct PC_TO_TGT_READ_EVENTS_REQUEST
{
	PC_TO_TGT_HEADER Header;
}PC_TO_TGT_READ_EVENTS_REQUEST;

/***************************************************/
typedef union PC_TO_TGT_REQUEST_U
{
	PC_TO_TGT_RECORD_CONTROL_REQUEST			RecordControlRequest;
	PC_TO_TGT_READ_EVENTS_REQUEST				ReadEventsRequest;
}PC_TO_TGT_REQUEST_U;

