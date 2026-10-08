#include "string.h"
#include "stdio.h"
#include "unistd.h"

#include "Main.h"
#include "TcpProtocol.h"
#include "LinuxcopeAdmin.h"

/**********************************************************************************/
int main(void)
{
	LinuxcopeAdminOpen ();

	CBaseProtocol *pTcpProtocol = new CTcpProtocol();

	pTcpProtocol->Init();

	while (1) { sleep(1); };

	return 0;
}
