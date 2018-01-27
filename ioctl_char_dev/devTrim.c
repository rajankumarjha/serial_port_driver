#include"header.h"
#include"declaration.h"

int devTrim(Dev *devlp)
{
    int l;
    Qset *lqset=NULL;
    Qset *slast=NULL;
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
        
    if(!devlp)
    {
      #ifdef DEBUG
      printk(KERN_INFO "Device not found\n");
      #endif
      goto RET;
    }
    
    if(!devlp->sqset)
    {
      #ifdef DEBUG
      printk(KERN_INFO "Device found but nothing to trim\n");
      #endif
      goto RET;
    }

    if(down_interruptible(&devlp->sem))
      return -ERESTARTSYS;

    slast=lqset=devlp->sqset;
    while(lqset)
    {
        while(lqset->next)
        {
          slast=lqset;
          lqset=lqset->next; 
        }
        
        for(l=register_no-1;l>=0;l--)
        {
           if(lqset->data[l])
           {
             kfree(lqset->data[l]);
             lqset->data[l]=NULL;   
           }            
        } 

        kfree(lqset->data); 
        lqset->data=NULL;
        
        if(slast->next)
       	 {
           kfree(slast->next);
           slast->next=NULL;
         }
        else
         {
            kfree(slast);
            devlp->sqset=NULL;
         }
 
        slast=lqset=devlp->sqset;
    }    

    up(&devlp->sem);
   
    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return 0;
   
  RET:
      #ifdef DEBUG
      printk(KERN_INFO "%s :End\n",__func__);
      #endif
      return 0;
}

