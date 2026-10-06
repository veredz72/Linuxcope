#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdbool.h>

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

	Request.Value = Enable;
	
	rc = ioctl (sHandle, RECORD_CONTROL_REQUEST_CODE, &Request);
	if (rc != 0)
		return LINUXCOPE_ADMIN_IOCTL_FAILED;

	return LINUXCOPE_ADMIN_OK;
}
