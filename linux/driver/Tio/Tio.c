
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/ktime.h>

#include "../../common/TioIoctl.h"

MODULE_LICENSE("Dual BSD/GPL");

#define N_INTERRUPTS 2

static wait_queue_head_t sWaitQueue[N_INTERRUPTS];
static u32 sInterruptFlag[N_INTERRUPTS] = {0};
int sMajorNumber;
struct class *sCharClass;
struct device *sCharDevice;

#define FILE_PATH			"/mnt/ramdisk/tio.bin"

#define NUM_CHANNELS 2
#define DEVICE_NAME "tio"
#define CLASS_NAME "tio"

static u32 PERIOD_NS [2] = { (1000LL * 1000LL), (2500LL * 1000LL)};/* 1 ms = 1,000,000 ns */

struct rt_timer_ctx {
    struct hrtimer timer;
    int id;                 /* e.g., 0 for Timer0, 1 for Timer1 */
    ktime_t period_kt;      /* Individual period for this timer */
    /* Add wait_queue_head_t, atomic_t event_flag, etc. per instance here */
};

static struct rt_timer_ctx timers[2];

/*********************************************************************************/
static int LinuxcopeLogEvent (uint32_t Id, uint32_t Value, uint64_t Timetag)
{		
	printk ("%d,%lld\n",Id*2, Timetag);
	
	return 0;
}

/**********************************************************************************/
static long TioIoctl (struct file *file,unsigned int IoctlCode,unsigned long IoctlParam)
{
	WAIT_FOR_INTERRUPT_REQUEST WaitForInterruptRequest;
	int rc;
	u32 IntId;

	switch (IoctlCode)
	{
	case WAIT_FOR_INTERRUPT_REQUEST_CODE:
		rc = copy_from_user(&WaitForInterruptRequest, (void*)IoctlParam, sizeof(WAIT_FOR_INTERRUPT_REQUEST));
		IntId = WaitForInterruptRequest.Interrupt;
		wait_event_interruptible(sWaitQueue[IntId], sInterruptFlag[IntId] != 0);
		sInterruptFlag[IntId] = 0;

		break;
	}
	
	return 0;
}

/**********************************************************************************/
static int TioOpen (struct inode *inode, struct file *fl)
{
	printk("-->TioOpen\n");
	printk("<--TioOpen\n");
	return 0;
}

/**********************************************************************************/
static int TioRelease (struct inode *inode, struct file *fl)
{
	printk("-->TioRelease\n");
	printk("<--TioRelease\n");
	return 0;
}

/**********************************************************************************/
static struct file_operations sDrvOperations =
{
	unlocked_ioctl: TioIoctl,
	open	: TioOpen,
	release : TioRelease,
	owner	: THIS_MODULE
};

/**********************************************************************************/
static enum hrtimer_restart TioTimerCallback (struct hrtimer *t)
{
    struct rt_timer_ctx *ctx = container_of(t, struct rt_timer_ctx, timer);
    u32 TmrId = ctx->id;
    
    LinuxcopeLogEvent (TmrId, 0, ktime_get_real_ns());
    
    wake_up_interruptible (&sWaitQueue[TmrId]);
    sInterruptFlag[TmrId]=1;
    
    hrtimer_forward_now(t, ctx->period_kt);
    
    return HRTIMER_RESTART;
}

/**********************************************************************************/
static int TioInit(void)
{
	int i;

	sMajorNumber=register_chrdev(0, "tio", &sDrvOperations);
	if (sMajorNumber < 0)
	{
		printk("TioInit: register_chrdev failed\n");
		return -1;
	}
	
	sCharClass = class_create(CLASS_NAME); //U20.04: THIS_MODULE, CLASS_NAME
	if (IS_ERR(sCharClass))
	{
		printk("TioInit: class_create failed rc=%ld\n",PTR_ERR(sCharClass));
		unregister_chrdev(sMajorNumber, DEVICE_NAME);
		return PTR_ERR(sCharClass);
	}

	sCharDevice = device_create(sCharClass, NULL, MKDEV(sMajorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(sCharDevice))
	{
		printk("TioInit: device_create failed rc=%ld\n",PTR_ERR(sCharDevice));
		unregister_chrdev(sMajorNumber, DEVICE_NAME);
		return PTR_ERR(sCharClass);
	}
	
	for (i = 0; i < NUM_CHANNELS; i++) {
		init_waitqueue_head(&sWaitQueue[i]);
        	
		/* Timer 0: 1 ms period */
    		timers[i].id = i;
    		timers[i].period_kt = ns_to_ktime(PERIOD_NS[i]);
    		hrtimer_setup(&timers[i].timer, TioTimerCallback, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
		hrtimer_start(&timers[i].timer, timers[i].period_kt, HRTIMER_MODE_REL_HARD);
    	}
		
 	return 0;
}

/**********************************************************************************/
static void TioExit(void)
{
	int i;
		
    	for (i = 0; i < NUM_CHANNELS; i++) {
        	hrtimer_cancel(&timers[i].timer);
    	}
 
	device_destroy(sCharClass, MKDEV(sMajorNumber, 0));
	class_destroy(sCharClass);
	unregister_chrdev(sMajorNumber, DEVICE_NAME);
	printk(KERN_INFO "Tio: Module unloaded successfully\n");
}



/**********************************************************************************/
module_init(TioInit);
module_exit(TioExit);
