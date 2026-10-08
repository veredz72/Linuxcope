#include "stdio.h"
#include <pthread.h>
#include <unistd.h>

#include "Tio.h"
#include "Linuxcope.h"

#define INSTANCE_0 0
#define INSTANCE_1 1

/***************************************************************/
void* Timer0(void* arg) 
{
	int rc=0;
	
	rc=LinuxcopeOpen (INSTANCE_0, "Timer0");
	if (rc!=LINUXCOPE_OK)
	{
		printf ("LinuxcopeOpen failed\n");
		return NULL;
	}	
	while(1)
	{
		TioWaitForInterrupt (0, 1000);
		LinuxcopeLogEvent (INSTANCE_0,0);
		printf ("To\n");
		LinuxcopeLogEvent (INSTANCE_0,1);
	}
}

/***************************************************************/
void* Timer1(void* arg) 
{
	int rc=0;
	
	rc=LinuxcopeOpen (INSTANCE_1, "Timer1");
	if (rc!=LINUXCOPE_OK)
	{
		printf ("LinuxcopeOpen failed\n");
		return NULL;
	}
	
	while(1)
	{
		TioWaitForInterrupt (1, 1000);
		LinuxcopeLogEvent (INSTANCE_1,0);
		printf ("T1\n");
		LinuxcopeLogEvent (INSTANCE_1,1);
	}
}

/***************************************************************/
int main(void)
{
	int rc;
	pthread_t thread0,thread1;
	
	rc=TioOpen ();
	if (rc!=TIO_OK)
	{
		printf ("TioOpen failed\n");
		return -1;
	}
	
	rc = pthread_create(&thread0, NULL, Timer0, NULL);
    	if (rc != 0) {
        	fprintf(stderr, "pthread_create failed\n");
        	return -1;
    	}
    	
    	rc = pthread_create(&thread1, NULL, Timer1, NULL);
    	if (rc != 0) {
        	fprintf(stderr, "pthread_create failed\n");
        	return -1;
    	}
    	
	while (1)
	{
		sleep (1);
		
	}
	return 0;
}

