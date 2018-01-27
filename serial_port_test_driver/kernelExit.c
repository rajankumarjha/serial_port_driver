#include"header.h"
#include"declaration.h"

//MODULE_LICENSE("GPL");


static void __exit kernel_exit(void);
module_exit(kernel_exit);

static void __exit kernel_exit(void)
{
    int nd;
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
 
    //device unregister method 1
    /*
      unregister_chrdev(majorno,DEVNAME);
    */

	/* ------------ release    ---------- */
	release_region(PORTADDR, 3);

         
    for(nd=0;nd<nod;nd++)
    {
      del_timer(&(D_dev+nd)->tmr);
    }

    for(nd=0;nd<nod;nd++)
    {
      cdev_del(&(D_dev+nd)->c_dev);
    }

    kfree(D_dev);

    //device unregister method 2
    for(nd=0;nd<nod;nd++)
    {
      devid=MKDEV(majorno,nd);
      unregister_chrdev_region(devid,nod);
      //unregister_chrdev_region(devid,1);            not working why ???
    }
    
    #ifdef DEBUG
    printk(KERN_INFO "Bye for now\n");
    #endif
    
    #ifdef DEBUG
    printk(KERN_INFO "%s : End\n",__func__);
    #endif
}

