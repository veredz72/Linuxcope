#include "stdio.h"
#include <pthread.h>
#include <unistd.h>

#include "Tio.h"
#include "Linuxcope.h"

#define INSTANCE_0 1
#define INSTANCE_1 3

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
		//printf ("To\n");
		//LinuxcopeLogEvent (INSTANCE_0,1);
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
		//printf ("T1\n");
		//LinuxcopeLogEvent (INSTANCE_1,1);
	}
}

/***************************************************************/
int main(void)
{
	int rc;
	pthread_t thread0,thread1;
	pthread_attr_t attr;
	struct sched_param param;
	
	pthread_attr_init(&attr);
	
	rc=TioOpen ();
	if (rc!=TIO_OK)
	{
		printf ("TioOpen failed\n");
		return -1;
	}
	
	rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    	if (rc != 0) {
        	printf ("pthread_attr_setinheritsched failed");
        	return -1;
    	}
    	
	rc = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    	if (rc != 0) {
        	printf("pthread_attr_setschedpolicy failed (Are you running with sudo?)");
        	return -1;
    	}
    
    	param.sched_priority = 99;
    	rc = pthread_attr_setschedparam(&attr, &param);
    	if (rc!= 0) {
		printf("pthread_attr_setschedparam failed");
		return -1;
    	}
    
	rc = pthread_create(&thread0, &attr, Timer0, NULL);
    	if (rc != 0) {
        	printf("pthread_create failed\n");
        	return -1;
    	}
    	
    	rc = pthread_create(&thread1, &attr, Timer1, NULL);
    	if (rc != 0) {
        	printf("pthread_create failed\n");
        	return -1;
    	}
    	
	pthread_join(thread0, NULL);
	return 0;
}

