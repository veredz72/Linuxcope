
typedef enum E_LINUXCOPE_ADMIN_ERROR_CODE
{
	LINUXCOPE_ADMIN_OK				= 0,
	LINUXCOPE_ADMIN_NOT_FOUND		= 1,
	LINUXCOPE_ADMIN_IOCTL_FAILED	= 2  
}E_LINUXCOPE_ADMIN_ERROR_CODE;

#ifdef __cplusplus
extern "C" {
#endif

int LinuxcopeAdminOpen (void);
int LinuxcopeAdminRecordControl (bool Enable);

#ifdef __cplusplus
}
#endif

