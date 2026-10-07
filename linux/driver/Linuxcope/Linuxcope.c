#include <linux/init.h>
#include <linux/module.h>
#include "../../common/LinuxcopeIoctl.h"
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DEVICE_NAME "linuxcope"
#define CLASS_NAME "linuxcope"

#define EVENT_NAME_LENGTH     8
#define FILE_PATH			"/mnt/ramdisk/linuxcope.bin"

typedef struct EVENT_DESC {
    char Name[EVENT_NAME_LENGTH];
	u32  Id;
	struct list_head node;
}EVENT_DESC;

static spinlock_t sTableLock;
static spinlock_t sLogLock;
static int sMajorNumber;
static struct class *sCharClass;
static struct device *sCharDevice;
static struct file *sFilp;
static loff_t sPos;
static int sRecordControl = 0;

static LIST_HEAD(sEventList);

/*********************************************************************************/
static inline int list_count_nodes(const struct list_head *head)
{
    const struct list_head *pos;
    int count = 0;

    list_for_each(pos, head)
        count++;

    return count;
}

/*********************************************************************************/
static long LinuxcopeIoctl (struct file *file,unsigned int IoctlCode,unsigned long IoctlParam)
{
	OPEN_EVENT_REQUEST OpenEventRequest;
	LOG_EVENT_REQUEST LogEventRequest;
	RECORD_CONTROL_REQUEST RecordControlRequest;
	struct EVENT_DESC *pEvent;
	ssize_t bytes;

	int rc;
	bool Found = false;

	switch (IoctlCode)
	{
	case OPEN_EVENT_REQUEST_CODE:
		rc = copy_from_user(&OpenEventRequest, (void*)IoctlParam, sizeof(OPEN_EVENT_REQUEST));
		//Add event to table 
		spin_lock(&sTableLock); //Enter critical section
		
		//Scan the list and look for the requested event name 
		list_for_each_entry(pEvent, &sEventList, node) {
        	// Process entry without sleeping
			if (strcmp (pEvent->Name, OpenEventRequest.Name)==0)
			{
				Found = true;
				printk ("Event %s already in list\n",pEvent->Name);
				break;
			}
    	}

		if (Found==false)
		{
			//Allocate event descriptor
			pEvent = kmalloc(sizeof(EVENT_DESC), GFP_KERNEL);
			//Copy name from request to descriptor
			memcpy (pEvent->Name, OpenEventRequest.Name, EVENT_NAME_LENGTH);
			pEvent->Id = list_count_nodes(&sEventList);
			//Add to the end of the list
			list_add_tail(&pEvent->node, &sEventList);
		}
		
		spin_unlock(&sTableLock); //Exit critical section
		OpenEventRequest.Id =pEvent->Id;
		rc=copy_to_user((void*)IoctlParam, &OpenEventRequest, sizeof(OPEN_EVENT_REQUEST));
		break;
	
	case LOG_EVENT_REQUEST_CODE:
		rc = copy_from_user(&LogEventRequest, (void*)IoctlParam, sizeof(LOG_EVENT_REQUEST));
		spin_lock(&sLogLock); //Enter critical section
		
		bytes=kernel_write(sFilp, &OpenEventRequest, sizeof(OpenEventRequest), &sPos);
		printk ("bytes=%ld\n",bytes);

		spin_unlock(&sLogLock); //Exit critical section
		break;

	case RECORD_CONTROL_REQUEST_CODE:
		rc = copy_from_user(&RecordControlRequest, (void*)IoctlParam, sizeof(RECORD_CONTROL_REQUEST));
		if (RecordControlRequest.Value == 1)
		{
			sFilp=filp_open(FILE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (IS_ERR(sFilp)) 
			{
				printk ("Failed to open %s\n",FILE_PATH);
			}
			else
			{
				sPos = 0;
				sRecordControl = 1;
			}
		}
		else
		{
			sRecordControl = 0;
			filp_close (sFilp,NULL);
		}
		break;
	}
	

	return 0;
}

/**********************************************************************************/
static int LinuxcopeOpen (struct inode *inode, struct file *fl)
{
	printk("-->LinuxcopeOpen\n");
	printk("<--LinuxcopeOpen\n");
	return 0;
}

/**********************************************************************************/
static int LinuxcopeRelease (struct inode *inode, struct file *fl)
{
	printk("-->LinuxcopeRelease\n");
	printk("<--LinuxcopeRelease\n");
	return 0;
}

/**********************************************************************************/
static struct file_operations sDrvOperations =
{
	unlocked_ioctl: LinuxcopeIoctl,
	open	: LinuxcopeOpen,
	release : LinuxcopeRelease,
	owner	: THIS_MODULE
};

/**********************************************************************************/
static int LinuxcopeInit(void)
{
	sMajorNumber=register_chrdev(0, "linuxcope", &sDrvOperations);
	if (sMajorNumber < 0)
	{
		printk("LinuxcopeInit: register_chrdev failed\n");
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
	
	spin_lock_init(&sTableLock);
	spin_lock_init(&sLogLock);
	
 	return 0;
}

/**********************************************************************************/
static void LinuxcopeExit(void)
{
	device_destroy(sCharClass, MKDEV(sMajorNumber, 0));
	class_destroy(sCharClass);
	unregister_chrdev(sMajorNumber, DEVICE_NAME);
	printk(KERN_INFO "Linuxcope: Module unloaded successfully\n");
	 	
}



/**********************************************************************************/
module_init(LinuxcopeInit);
module_exit(LinuxcopeExit);
