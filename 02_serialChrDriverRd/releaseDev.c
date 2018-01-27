#include "headers.h"
#include "decleration.h"

int releaseDev(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Begin:%s\n",__func__);
	printk(KERN_INFO "End:%s\n",__func__);
	return 0;
}
