#include "stdio.h"
#include "stdbool.h"

#include "LinuxcopeAdmin.h"


/***************************************************************/
int main(void)
{
	int rc;
	
	rc=LinuxcopeAdminOpen ();
	if (rc!=0)
	{
		printf ("LinuxcopeAdminOpen failed\n");
		return -1;
	}
	
    	LinuxcopeAdminRecordControl (true);

	return 0;
}

