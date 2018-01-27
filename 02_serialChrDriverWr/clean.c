#include "headers.h"
#include "decleration.h"

extern dev_t devId;
extern int majorno;
extern int minorno;
extern int devno;      /* number of bare scull devices */
extern struct myDev *myDevices;

static void __exit helloKernel_exit(void)
{
	//unregister_chrdev_region(devId,1);
	delMyDevices();
	printk(KERN_ALERT "GoodBye! Kernel! unregister done!\n");
}

int delMyDevices(void)
{
	int i;
	for(i=0;i<devno;i++)
        {
		devId = MKDEV(majorno, i);
                cdev_del(&myDevices[i].cdev);
		unregister_chrdev_region(devId,1);
        }
        kfree(myDevices);

	return 0;
}

module_exit(helloKernel_exit);
