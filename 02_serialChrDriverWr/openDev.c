#include "headers.h"
#include "decleration.h"

int openDev(struct inode *inodep, struct file *filep)
{
	struct myDev *ldev;
	printk(KERN_INFO "Begin:%s\n",__func__);
	ldev = container_of(inodep->i_cdev,struct myDev, cdev);
	filep->private_data = ldev;	//store it for use
	if((filep->f_flags & O_ACCMODE)==O_WRONLY)
	{	
		printk(KERN_INFO "O_WRONLY!!\n");
		if(ldev->size)
		{
			printk(KERN_INFO "triming::ldev->size:%ld\n",ldev->size);
			trimDev(ldev);
		}
		else
			printk(KERN_INFO "Nothing to trim::ldev->size:%ld\n",ldev->size);

		//goto fail;
	}
	else if((filep->f_flags & O_ACCMODE)!=O_RDONLY)
	{
		printk(KERN_INFO "O_RDONLY!!\n");
	}

	printk(KERN_INFO "End:%s\n",__func__);
	return 0;
//fail:
//	trimDev(ldev);
//	return -1;
}
