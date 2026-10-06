#define THREAD_NAME_LENGTH     8
#define LINUXCOPE_MAX_INSTANCE 32

typedef enum E_LINUXCOPE_ERROR_CODE
{
	LINUXCOPE_OK				= 0,
	LINUXCOPE_NOT_FOUND			= 1,
	LINUXCOPE_IOCTL_FAILED			=2
}E_LINUXCOPE_ERROR_CODE;

int LinuxcopeOpen (int Instance, char *ThreadName);
int LinuxcopeLogEvent (int Instance,int Value);


