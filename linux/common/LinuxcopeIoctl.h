#include <linux/ioctl.h>

#define LINUXCOPE_IOC_MAGIC 0xE0

#define OPEN_EVENT_REQUEST_CODE		_IOW(LINUXCOPE_IOC_MAGIC, 1, int)
#define LOG_EVENT_REQUEST_CODE		_IOW(LINUXCOPE_IOC_MAGIC, 2, int)

typedef struct OPEN_EVENT_REQUEST
{
	char Name[8];
	uint32_t Id;
}OPEN_EVENT_REQUEST;

typedef struct LOG_EVENT_REQUEST
{
	uint32_t Value;
	uint64_t Timetag;
}LOG_EVENT_REQUEST;



