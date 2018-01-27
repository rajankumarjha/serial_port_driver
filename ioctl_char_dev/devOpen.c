#include"header.h"
#include"declaration.h"

int devOpen(struct inode *inodep,struct file *filp)
{
    
    Dev *devlp;
    int ret;
   // static int s=0;

    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
   // if(s==0)
   { 
    devlp=container_of(inodep->i_cdev,Dev,c_dev);
    if(!devlp)
    {
      #ifdef DEBUG
      printk(KERN_INFO "container_of:\n");
      #endif
      goto ERR; 
    }
   // s++;
    filp->private_data=devlp;          //storing local pointer inside private data part of struct file(preserve the device)    
   } 
    
      #ifdef DEBUG
      printk(KERN_INFO "devlp address is %p\n",devlp);
      #endif
      #ifdef DEBUG
      printk(KERN_INFO "devlp address is %p\n",filp->private_data);
      #endif
    // check access mode

    if((filp->f_flags & O_ACCMODE)==O_WRONLY)                    //?? doubt true for both read and write only mode
     {
           ret=devTrim(devlp);
          // ret=devTrim(filp->private_data);
     }

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return 0;
 
  ERR:   
    	#ifdef DEBUG
    	printk(KERN_ERR "%s end with Error\n",__func__);
    	#endif
    	return -1;
}

