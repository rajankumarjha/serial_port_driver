#include"header.h"
#include"declaration.h"

loff_t devLlseek(struct file *filp,loff_t offset,int origin)
{
    Dev *ldev;
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
    
    ldev=filp->private_data;
    #ifdef DEBUG
    printk(KERN_INFO "ldev address is: %p\n",ldev);
    #endif

    #ifdef DEBUG
    printk(KERN_INFO "offset is %d and origin is %d\n",(int)offset,origin);
    #endif
    
    //if(down_interruptible(&ldev->sem))
      // return -ERESTARTSYS;

    switch(origin)
     {
         case 0:
    		#ifdef DEBUG
    		printk(KERN_INFO "SEEK_SET Mode\n");
                #endif 
                if(offset>=0)
                {
                	if(offset>=ldev->device_size)
                	 {
    				#ifdef DEBUG
    				printk(KERN_INFO "Offset too big\n");
                		#endif 
                	 }

                	else
                		filp->f_pos=offset;  
		}
                else
                 {
    			#ifdef DEBUG
    			printk(KERN_INFO "Offset is negative\n");
                	#endif 
                     
                 }    
                break;

         case 1:
    		#ifdef DEBUG
    		printk(KERN_INFO "SEEK_CUR Mode\n");
                #endif
                if(offset<0)
                 {      
                      if(filp->f_pos+offset<=0)
    			{
 				#ifdef DEBUG
    				printk(KERN_INFO "Offset too small\n");
                		#endif
                        }
                      else
                            filp->f_pos=filp->f_pos+offset;
                 }
                if(offset>0)
                 {      
                      if(filp->f_pos+offset>=device_size)
    			{
 				#ifdef DEBUG
    				printk(KERN_INFO "Offset too Big\n");
                		#endif
                        } 
                      else
			filp->f_pos=filp->f_pos+offset;  
                 }
                
                break;  
 
         case 2:
    		#ifdef DEBUG
    		printk(KERN_INFO "SEEK_END Mode\n");
                #endif  
                if(offset>0) 
                   {
 			#ifdef DEBUG
    			printk(KERN_INFO "Offset is positive\n");
                	#endif
                   }
                else
               	   filp->f_pos=data_size+offset;  

                break;
     }
     
    //up(&ldev->sem);
     
    #ifdef DEBUG
    printk(KERN_INFO "file_pos at: %lld\n",filp->f_pos);
    #endif    

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif

    return 0;

}

