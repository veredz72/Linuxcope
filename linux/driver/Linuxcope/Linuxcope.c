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


/*********************************************************************************/
static long LinuxcopeIoctl (struct file *file,unsigned int IoctlCode,unsigned long IoctlParam)
{
	/*WAIT_FOR_INTERRUPT_REQUEST WaitForInterruptRequest;
	int rc;
	u32 IntId;

	//printk("--> TioIoctl\n");

	switch (IoctlCode)
	{
	case WAIT_FOR_INTERRUPT_REQUEST_CODE:
		rc = copy_from_user(&WaitForInterruptRequest, (void*)IoctlParam, sizeof(WAIT_FOR_INTERRUPT_REQUEST));
		IntId = WaitForInterruptRequest.Interrupt;
		wait_event_interruptible(sWaitQueue[IntId], sInterruptFlag[IntId] != 0);
		sInterruptFlag[IntId] = 0;

		break;
	}*/
	
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
	int Major;
	struct class *pCharClass;
	struct device *pCharDevice;

	Major=register_chrdev(0, "linuxcope", &sDrvOperations);
	if (Major < 0)
	{
		printk("LinuxcopeInit: register_chrdev failed\n");
		return -1;
	}
	
	pCharClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(pCharClass))
	{
		printk("TioInit: class_create failed rc=%ld\n",PTR_ERR(pCharClass));
		unregister_chrdev(Major, DEVICE_NAME);
		return PTR_ERR(pCharClass);
	}

	pCharDevice = device_create(pCharClass, NULL, MKDEV(Major, 0), NULL, DEVICE_NAME);
	if (IS_ERR(pCharDevice))
	{
		printk("TioInit: device_create failed rc=%ld\n",PTR_ERR(pCharDevice));
		unregister_chrdev(Major, DEVICE_NAME);
		return PTR_ERR(pCharClass);
	}
	
 	return 0;
}

/**********************************************************************************/
static void LinuxcopeExit(void)
{
	
	 	
}



/**********************************************************************************/
module_init(LinuxcopeInit);
module_exit(LinuxcopeExit);
