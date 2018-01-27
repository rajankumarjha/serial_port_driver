#include "headers.h"
#include "decleration.h"

//------------------------------------------------------------------
/*lseek(fd, offset, origin)*/ //origin: SEEK_SET, SEEK_CUR, SEEK_END
//------------------------------------------------------------------

loff_t llseekDev(struct file *filep, loff_t offset, int origin)
{
	struct myDev *dvs;

	printk(KERN_INFO "Begin:%s\n",__func__);
	dvs = filep->private_data;

	printk(KERN_INFO "filep->f_pos:%lld  dvs->size:%ld  offset:%lld origin:%d\n", filep->f_pos, dvs->size, offset, origin);
	switch(origin)
	{
		case SEEK_SET:		/*SEEK_SET*/
			filep->f_pos = offset;
			break;
		case SEEK_CUR:		/*SEEK_CUR*/
			filep->f_pos = filep->f_pos + offset;
			break;
		case SEEK_END:		/*SEEK_END*/
			filep->f_pos = dvs->size - offset;
			break;
	}
	printk(KERN_INFO "End:%s\n",__func__);
	return filep->f_pos;
}
