#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "Tio.h"
#include "../../common/TioIoctl.h"

static int sHandle;

/**********************************************************************************/
int TioOpen (void)
{
	sHandle = open("/dev/tio", O_RDWR);
	if (sHandle <=0)
	{
		printf ("TioOpen failed. %s\n",strerror(errno));
		return TIO_NOT_FOUND;
	}

	return TIO_OK;
}

/**********************************************************************************/
int TioWaitForInterrupt (int Channel, int Timeout)
{
	int rc;
	WAIT_FOR_INTERRUPT_REQUEST Request;

	Request.Interrupt = Channel;
	Request.Timeout = Timeout;

	rc = ioctl (sHandle, WAIT_FOR_INTERRUPT_REQUEST_CODE, &Request);
	if (rc != 0)
		return TIO_WAIT_FOR_INT_FAILED;

	return TIO_OK;
}

