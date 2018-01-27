#include "header.h"
#include "declaration.h"
#include "foper.h"

//MODULE_LICENSE("GPL");


EXPORT_SYMBOL(myModule);

static int __init kernel_init(void);
module_init(kernel_init);

int majorno,minorno,nod;
int register_size=REGSIZE;
int register_no=REGNO;
int device_size=DEVSIZE;
int data_size=DATASIZE;
int baud_rate=BAUDRATE;
dev_t devno,devid;
unsigned long tvar1,tvar2;
//Dev *D_dev[100];
Dev *D_dev;

//module_param(nod,int,S_IRUGO);

static int __init kernel_init(void)
{
    int ret,nd , pret;
    unsigned long j1,j2;
    nod=1;
    #ifdef DEBUG
    printk(KERN_INFO "%s: Begin \n",__func__);
    #endif
    
    #ifdef DEBUG
    printk("HELLO KERNEL\n");
    printk("nod is :%d\n",nod);
    #endif

    //device registration method 1
    /* 
    majorno=register_chrdev(MAJORNO,DEVNAME,&fops);
    printk(KERN_INFO "Major No. is %d\n",majorno);
    */
    
    //device registration method 2
     //nod=NOD;
    
     majorno=MAJOR(devno);
     minorno=MINOR(devno);
     
     #ifdef DEBUG
     printk(KERN_INFO "Initially Major No is %d ,and Minor No. is %d\n",majorno,minorno);
     #endif

    if(majorno==0)
    {
     ret=alloc_chrdev_region(&devno,minorno,nod,DEVNAME);           //dynamic allocation of major no.
     if(ret<0)
      {  
         #ifdef DEBUG
         printk(KERN_INFO "alloc_chrdev_region\n");
         #endif
         goto ERR;
      }
    
      majorno=MAJOR(devno);
      minorno=MINOR(devno);

      #ifdef DEBUG
      printk(KERN_INFO "After alloc-->Major No is %d ,and Minor No. is %d\n",majorno,minorno);
      #endif
    }
 
   else
    {
       ret=register_chrdev_region(devno,1,DEVNAME);             //for already known major no.
       if(ret<0)
       {
         #ifdef DEBUG
         printk(KERN_INFO "register_chrdev_region\n");
         #endif
         goto ERR;
       }
      
       majorno=MAJOR(devno);
       minorno=MINOR(devno);

       #ifdef DEBUG
       printk(KERN_INFO "Major No is %d ,and Minor No. is %d\n",majorno,minorno);
       #endif
    }  

   // get memory for scull device
     
	pret = check_region(PORTADDR,8) ;
	 #ifdef DEBUG
	 printk(KERN_INFO "pret : %d\n", pret);
	 #endif
	if(pret <0)
	{
                release_region(PORTADDR,8);
		request_region(PORTADDR, 8, DEVNAME);
	}

	if(pret == 0)
	{
//	kernel will release port addresses 
		request_region(PORTADDR, 8, DEVNAME);
	}

    D_dev=(struct Dev*)kmalloc(nod*sizeof(struct Dev),GFP_KERNEL);                //get free page mem from kernel
    if(!D_dev)
    {
         #ifdef DEBUG
         printk(KERN_INFO "kmalloc:\n");
         #endif
         goto ERR;
    }
     
     D_dev=(struct Dev*)memset(D_dev,'\0',nod*sizeof(struct Dev));
    
    // initialize device structure cdev
   
    for(nd=0;nd<nod;nd++)
    {   
       	cdev_init(&(D_dev+nd)->c_dev,&fops);
    	(D_dev+nd)->c_dev.ops=&fops;

        init_timer(& ((D_dev+nd)->tmr) );
    	(D_dev+nd)->register_size=register_size;
    	(D_dev+nd)->register_no=register_no;
    	(D_dev+nd)->device_size=device_size;
    	(D_dev+nd)->data_size=data_size;
        
        sema_init(&(D_dev+nd)->sem,1);
        
        devid=MKDEV(majorno,nd);
        
        #ifdef DEBUG
        printk(KERN_INFO "Before cdev_add Major No is %d ,and Minor No. is %d\n",MAJOR((D_dev+nd)->c_dev.dev),MINOR((D_dev+nd)->c_dev.dev));
        #endif
        
        ret= cdev_add(&(D_dev+nd)->c_dev,devid,1);    //add each and every nod to device table and update dev field in cdev
        if(ret<0)
        {
         
         #ifdef DEBUG
         printk(KERN_INFO "cdev_add:\n");
         #endif
         goto ERR;
        }   
       
        (D_dev+nd)->tmr.function=timerFunc;
        (D_dev+nd)->tmr.data=(unsigned long)1;
    	j1=jiffies;
	j2=j1 + (unsigned long)20000;
    	printk(KERN_INFO "j1=%lu",j1);
    	printk(KERN_INFO "j2=%lu",j2);

    	(D_dev+nd)->tmr.expires=(unsigned long)j2;
        add_timer(&(D_dev+nd)->tmr);
         
        #ifdef DEBUG
        printk(KERN_INFO "After cdev_add Major No is %d ,and Minor No. is %d\n",MAJOR((D_dev+nd)->c_dev.dev),MINOR((D_dev+nd)->c_dev.dev));
        #endif
        
        majorno=MAJOR(devid);
        minorno=MINOR(devid);

        #ifdef DEBUG
        printk(KERN_INFO "Major No is %d ,and Minor No. is %d\n",majorno,minorno);
        #endif
    }
      
        #ifdef DEBUG
        printk(KERN_INFO "%s: End \n",__func__);
        #endif
        return 0;

    ERR:
        #ifdef DEBUG
        printk(KERN_ERR "%s: End with Error\n",__func__);
        #endif
        return -1;
}

int myModule()
{
   #ifdef DEBUG
   printk(KERN_INFO "My first module called by another driver\n");
   #endif
   return 0;
}
