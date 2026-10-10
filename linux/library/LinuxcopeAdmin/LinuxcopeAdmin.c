#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>

#include "LinuxcopeAdmin.h"
#include "../../common/LinuxcopeIoctl.h"

static int sHandle;

/**********************************************************************************/
int LinuxcopeAdminOpen (void)
{
	sHandle = open("/dev/linuxcope", O_RDWR);
	if (sHandle <=0)
	{
		printf ("LinuxcopeAdminOpen failed. %s\n",strerror(errno));
		return LINUXCOPE_ADMIN_NOT_FOUND;
	}

	return LINUXCOPE_ADMIN_OK;
}

/**********************************************************************************/
int LinuxcopeAdminRecordControl (bool Enable)
{
	int rc;
	RECORD_CONTROL_REQUEST Request;
	struct timespec ts;

	if (Enable==true)
	{
		clock_gettime(CLOCK_REALTIME, &ts);
		Request.Timetag = ts.tv_sec * 1E9 + ts.tv_nsec;
	}
	Request.Value = Enable;
	
	rc = ioctl (sHandle, RECORD_CONTROL_REQUEST_CODE, &Request);
	if (rc != 0)
		return LINUXCOPE_ADMIN_IOCTL_FAILED;

	return LINUXCOPE_ADMIN_OK;
}

/**********************************************************************************/
int LinuxcopeAdminReadEvents (int *NofEvents, LINUXCOPE_ADMIN_EVENT_DESC *pDesc)
{
	READ_EVENTS_REQUEST Request;
	LINUXCOPE_ADMIN_EVENT_DESC *pDst = pDesc;
	int rc;

	//Send request to read events list 
	rc = ioctl (sHandle, READ_EVENTS_REQUEST_CODE, &Request);
	if (rc != 0)
		return LINUXCOPE_ADMIN_IOCTL_FAILED;

	*NofEvents = Request.NofEvents;
	for (int i=0;i<Request.NofEvents; i++)
	{
		strcpy (pDst->Name, Request.Event[i].Name);
		pDst->Id =  Request.Event[i].Id;
		pDst++;
	}
	return LINUXCOPE_ADMIN_OK;
}
