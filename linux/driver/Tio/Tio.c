#include <linux/init.h>
#include <linux/module.h>
#include "../../common/TioIoctl.h"
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/platform_device.h>

MODULE_LICENSE("Dual BSD/GPL");

#define N_INTERRUPTS 2

static wait_queue_head_t sWaitQueue[N_INTERRUPTS];
static u32 sInterruptFlag[N_INTERRUPTS] = {0};
int sMajorNumber;
struct class *sCharClass;
struct device *sCharDevice;


#define NUM_CHANNELS 2
#define DEVICE_NAME "tio"
#define CLASS_NAME "tio"

struct channel_dev {
    int channel_id;
    int interval_ms;
    unsigned long tick_count;
    struct timer_list timer;
};

/* Two independent channel instances */
static struct channel_dev channels[NUM_CHANNELS];


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
static void TioTimerCallback (struct timer_list *t)
{
    	// from_timer recovers the specific struct channel_dev that owns *t */
	struct channel_dev *chan = from_timer(chan, t, timer);
	int TmrId = chan->channel_id;
	
	wake_up_interruptible(&sWaitQueue[TmrId]);
	sInterruptFlag[TmrId] = 1;
	
    chan->tick_count++;
    //printk("Channel %d expired! Tick count: %lu\n",TmrId, chan->tick_count);

    // Re-arm using each channel's independent period */
    mod_timer(&chan->timer, jiffies + msecs_to_jiffies(chan->interval_ms));
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
	
	sCharClass = class_create(THIS_MODULE, CLASS_NAME);
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
	
	// Channel 0: 500 ms interval */
	channels[0].channel_id = 0;
	channels[0].interval_ms = 500;
	channels[0].tick_count = 0;

	// Channel 1: 1500 ms interval */
	channels[1].channel_id = 1;
	channels[1].interval_ms = 1500;
	channels[1].tick_count = 0;
    	
	for (i = 0; i < NUM_CHANNELS; i++) {
		init_waitqueue_head(&sWaitQueue[i]);
        	timer_setup(&channels[i].timer, TioTimerCallback, 0);
        	mod_timer(&channels[i].timer, jiffies + msecs_to_jiffies(channels[i].interval_ms));
    	}


 	return 0;
}

/**********************************************************************************/
static void TioExit(void)
{
	int i;
	
    	for (i = 0; i < NUM_CHANNELS; i++) {
        	timer_delete_sync(&channels[i].timer);
    	}
 
	device_destroy(sCharClass, MKDEV(sMajorNumber, 0));
	class_destroy(sCharClass);
	unregister_chrdev(sMajorNumber, DEVICE_NAME);
	printk(KERN_INFO "Tio: Module unloaded successfully\n");
}



/**********************************************************************************/
module_init(TioInit);
module_exit(TioExit);
