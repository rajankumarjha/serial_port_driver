#include "headers.h"
#include "decleration.h"

dev_t devId =0;
int majorno =   MAJORNO;
int minorno =   0;
int devno   = 	DEVNO;      /* number of bare scull devices */

int no_of_registers = NUM_REGISTRES;
int size_of_registers = SIZ_REGISTRES;
int no_of_qSet = NUM_QSET;
int no_of_quantum = NUM_QUANTUM;
int devSize = DEV_SIZE;

module_param(devno, int, S_IRUGO);	/*give argument at run time insmod .ko devno=100*/
struct myDev *myDevices;        /* allocated in scull_init_module */
static struct file_operations fops = {
	open:openDev,
	release:releaseDev,
	read:readDev,
	write:writeDev,
	llseek:llseekDev,
	//unlocked_ioctl:ioctlDev
};

static int __init helloKernel_init(void)
{
	int ret,i;
	int err;
	unsigned volatile long addrByte = 0x00;
	printk(KERN_ALERT "Hello Kernel!I'm here for dev register!\n");
	printk(KERN_ALERT "devno:%d\n",devno);
	//------------------------------------------------------------
	//		traditional Method of registration
	//------------------------------------------------------------
	#ifdef METHOD_REGSITER_CHARDEV
		majorno = register_chrdev(majorno,DEVNAME,&fops);
		printk(KERN_INFO "majorno:%d\n",majorno);
	#endif
	//------------------------------------------------------------
	//	newer method dynamic allocation for major number
	//------------------------------------------------------------
	#ifdef METHOD_ALLOC_CHARDEV
		if(alloc_chrdev_region(&devId,0,1,DEVNAME) < 0)
		{
			return -1;
		}
		majorno = MAJOR(devId);
		minorno = MINOR(devId);
		printk(KERN_INFO "majorno:%d minorno:%d\n",MAJOR(devId),MINOR(devId));
	#endif
	myDevices = kmalloc(devno*sizeof(struct myDev), GFP_KERNEL);
	if (!myDevices) {
		ret = -ENOMEM;
		goto fail;  /* Make this more graceful */
	}
	memset(myDevices, 0, devno * sizeof(struct myDev));
	for (i = 0; i < devno; i++)	/* Initialize each device. */ 
	{
		cdev_init(&myDevices[i].cdev, &fops);
		myDevices[i].cdev.ops = &fops;
		myDevices[i].quantum = no_of_quantum;
		myDevices[i].qset = no_of_qSet;
		sema_init(&myDevices[i].sem, 1);
		init_completion(&myDevices[i].comp);
		devId = MKDEV(majorno, i);
		err = cdev_add (&myDevices[i].cdev, devId, 1);

		if (err)
			printk(KERN_NOTICE "Error %d adding scull%d", err, i);
		printk(KERN_INFO "majorno:%d minorno:%d\n",MAJOR(devId),MINOR(devId));
	}
	if(check_region(BASE_SERIAL_PORT_ADDRS,8)<0)
	{
		printk(KERN_INFO "PORT NOT AVAILABLE :%d\n", check_region(BASE_SERIAL_PORT_ADDRS,8));
		release_region(BASE_SERIAL_PORT_ADDRS,8);
		request_region(BASE_SERIAL_PORT_ADDRS,8,DEVNAME);
	}
	else
	{
		printk(KERN_INFO "PORT AVAILABLE :%d\n", check_region(BASE_SERIAL_PORT_ADDRS,8));
		request_region(BASE_SERIAL_PORT_ADDRS,8,DEVNAME);
	}
	//--------------------------------------------------------------------
	//			set serial baud rate
	//--------------------------------------------------------------------
	addrByte = inb(LCR);
	test_and_set_bit(7, &addrByte);
	outb(addrByte, LCR);	/*DLAB divisor latch access bits select*/
	outb(0x00, DMS);
	outb(0x0C, DLS);	/*divisor 0x0C:: baud rate = 9600*/
	test_and_clear_bit(7, &addrByte);
	outb(addrByte, LCR);	/*DLAB divisor latch access bits free*/
	//--------------------------------------------------------------------



	return 0;	/* succeed */
fail:
	delMyDevices();
	return ret;

}

module_init(helloKernel_init);
