#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>

#include "Linuxcope.h"
#include "../../common/LinuxcopeIoctl.h"

static int sHandle[LINUXCOPE_MAX_INSTANCE];
static uint32_t sEventId[LINUXCOPE_MAX_INSTANCE];

/**********************************************************************************/
int LinuxcopeOpen (int Instance, char *ThreadName)
{
	OPEN_EVENT_REQUEST Request;
	int rc;
	
	sHandle[Instance] = open("/dev/linuxcope", O_RDWR);
	if (sHandle[Instance] <=0)
	{
		printf ("LinuxcopeOpen failed. %s\n",strerror(errno));
		return LINUXCOPE_NOT_FOUND;
	}
	
	memset (&Request.Name,0,THREAD_NAME_LENGTH);
	strcpy (Request.Name, ThreadName);
	rc = ioctl (sHandle[Instance], OPEN_EVENT_REQUEST_CODE, &Request);
	if (rc != 0)
		return LINUXCOPE_IOCTL_FAILED;

	printf ("Request.Id=%d\n",Request.Id);
	sEventId[Instance] = Request.Id;

	return LINUXCOPE_OK;
}

/**********************************************************************************/
int LinuxcopeLogEvent (int Instance,int Value)
{
	LOG_EVENT_REQUEST Request;
	struct timespec ts;
	int rc;
	
	clock_gettime(CLOCK_REALTIME, &ts);

	Request.Value = Value;
	Request.Timetag = ts.tv_sec * 1E9 + ts.tv_nsec;
	Request.Id = sEventId[Instance];
	rc = ioctl (sHandle[Instance], LOG_EVENT_REQUEST_CODE, &Request);
	if (rc != 0)
		return LINUXCOPE_IOCTL_FAILED;

	return LINUXCOPE_OK;
}
