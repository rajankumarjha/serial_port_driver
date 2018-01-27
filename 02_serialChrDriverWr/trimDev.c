#include"headers.h"
#include"decleration.h"

int trimDev(struct myDev *ldev)
{
	int i, qset = ldev->qset;
	struct myQset *qs;
	struct myQset *qsNext; 
	qs = qsNext = ldev->data;
	printk(KERN_INFO "Begins:%s\n",__func__);

	printk(KERN_INFO "qset:%d\n",qset);
	while(qs!=NULL)
	{
		if(qs->data)
		{
			printk(KERN_INFO "qs->dara not null\n");
			for(i=0;i<qset;i++)
			{
				kfree(qs->data[i]);
				printk(KERN_INFO "i::%d\n",i);
			}
			kfree(qs->data);
			qs->data = NULL;
			qsNext = qs->next;
			kfree(qs);
			qs = qsNext;
			printk(KERN_INFO "DEBUG0\n");
		}
		else
			break;
	}
	ldev->size = 0;
	ldev->data = NULL;
	printk(KERN_INFO "End:%s\n",__func__);
	return 0;
}
