#include "headers.h"
#include "decleration.h"
long ioctDev(struct file *filp, unsigned int cmd, unsigned long arg)
{
   	int retval = 0;
	printk(KERN_INFO "BEGINS:%s\n",__func__);
	printk(KERN_INFO "ENDS:%s\n",__func__);
	return retval;
}
