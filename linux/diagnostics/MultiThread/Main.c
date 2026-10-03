#include "stdio.h"
#include <pthread.h>
#include <unistd.h>

#include "Tio.h"

/***************************************************************/
void* Timer0(void* arg) 
{
	while(1)
	{
		TioWaitForInterrupt (0, 1000);
		printf ("To\n");
	}
}

/***************************************************************/
void* Timer1(void* arg) 
{
	while(1)
	{
		TioWaitForInterrupt (1, 1000);
		printf ("T1\n");
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
        	fprintf(stderr, "pthread_create failed: %s\n", strerror(rc));
        	return -1;
    	}
    	
    	rc = pthread_create(&thread1, NULL, Timer1, NULL);
    	if (rc != 0) {
        	fprintf(stderr, "pthread_create failed: %s\n", strerror(rc));
        	return -1;
    	}
    	
	while (1)
	{
		sleep (1);
		
	}
	return 0;
}

