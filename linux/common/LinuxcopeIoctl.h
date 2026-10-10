#include <linux/ioctl.h>

#define LINUXCOPE_IOC_MAGIC 0xE0

#define OPEN_EVENT_REQUEST_CODE		_IOW(LINUXCOPE_IOC_MAGIC, 1, int)
#define LOG_EVENT_REQUEST_CODE		_IOW(LINUXCOPE_IOC_MAGIC, 2, int)
#define RECORD_CONTROL_REQUEST_CODE _IOW(LINUXCOPE_IOC_MAGIC, 3, int)
#define READ_EVENTS_REQUEST_CODE	_IOW(LINUXCOPE_IOC_MAGIC, 4, int)

typedef struct OPEN_EVENT_REQUEST
{
	char Name[8];
	uint32_t Id;
}OPEN_EVENT_REQUEST;

typedef struct LOG_EVENT_REQUEST
{
	uint32_t Id;
	uint32_t Value;
	uint64_t Timetag;
}LOG_EVENT_REQUEST;

typedef struct RECORD_CONTROL_REQUEST
{
	uint32_t Value;
	uint64_t Timetag;
}RECORD_CONTROL_REQUEST;

typedef struct READ_EVENTS_REQUEST
{
	uint32_t NofEvents;
	OPEN_EVENT_REQUEST Event[16];
}READ_EVENTS_REQUEST;

