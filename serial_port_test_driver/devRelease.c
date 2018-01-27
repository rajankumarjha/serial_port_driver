#include"header.h"
#include"declaration.h"

int devRelease(struct inode *inodep,struct file *filp)
{
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
 
    

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
   
    return 0;
}

