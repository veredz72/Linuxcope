#include <linux/init.h>
#include <linux/module.h>
#include "../../common/LinuxcopeIoctl.h"
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/platform_device.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DEVICE_NAME "linuxcope"
#define CLASS_NAME "linuxcope"

#define EVENT_NAME_LENGTH     8

typedef struct EVENT_TABLE
{
	char Name[EVENT_NAME_LENGTH];
	u32  Id;
}EVENT_TABLE;

static int sTableEntryId = 0;
static EVENT_TABLE sEventTable[32];
static spinlock_t sTableLock;
static spinlock_t sLogLock;
int sMajorNumber;
struct class *sCharClass;
struct device *sCharDevice;

/*********************************************************************************/
static long LinuxcopeIoctl (struct file *file,unsigned int IoctlCode,unsigned long IoctlParam)
{
	OPEN_EVENT_REQUEST OpenEventRequest;
	LOG_EVENT_REQUEST LogEventRequest;
	int rc;

	switch (IoctlCode)
	{
	case OPEN_EVENT_REQUEST_CODE:
		rc = copy_from_user(&OpenEventRequest, (void*)IoctlParam, sizeof(OPEN_EVENT_REQUEST));
		//Add event to table 
		spin_lock(&sTableLock); //Enter critical section
		sTableEntryId++;
		memcpy (sEventTable[sTableEntryId].Name, OpenEventRequest.Name, EVENT_NAME_LENGTH);		
		OpenEventRequest.Id = sTableEntryId; 
		spin_unlock(&sTableLock); //Exit critical section
		rc=copy_to_user((void*)IoctlParam, &OpenEventRequest, sizeof(OPEN_EVENT_REQUEST));
		break;
	
	case LOG_EVENT_REQUEST_CODE:
		rc = copy_from_user(&LogEventRequest, (void*)IoctlParam, sizeof(LOG_EVENT_REQUEST));
		spin_lock(&sLogLock); //Enter critical section
		
		spin_unlock(&sLogLock); //Exit critical section
		break;

	case RESET_TABLE_REQUEST_CODE:
		spin_lock(&sTableLock); //Enter critical section
		sTableEntryId = 0;
		spin_unlock(&sTableLock); //Exit critical section
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
