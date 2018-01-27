#include"header.h"
#include"declaration.h"

ssize_t devWrite(struct file *filp,const char __user *buff,size_t buffsz,loff_t *loffptr)
{
    Dev *ldev=NULL;
    Qset *lsqset=NULL;
    int noi,noq,i=0,ret=0,noctw=0,nocsw=0,ret2;
    unsigned long j1,j2,tsclli,tsclle;
    unsigned volatile long addrbit;
    unsigned char fetch_set,fetch_clear;
 
    j1=jiffies;
    tvar1=jiffies;
   
    //rdtsc(tschi,tscli);
    rdtscll(tsclli);
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
    
    #ifdef DEBUG
    printk(KERN_INFO "buffer limit: %lu bytes\n",buffsz);
    #endif
    
     ldev=filp->private_data;
     #ifdef DEBUG
     printk(KERN_INFO "ldev address is %p\n",ldev);
     #endif

      if(buffsz>device_size)
      {
         #ifdef DEBUG
         printk(KERN_INFO "partial write will occur");
         #endif
         buffsz=device_size; 
      }
    
    noi=buffsz/(register_no*register_size);
    if(buffsz%(register_no*register_size)>0)
    noi++;
    
    noq=buffsz/(register_size);
    if((buffsz%register_size)>0)
    noq++;

    #ifdef DEBUG
    printk(KERN_INFO "noi: %d \n",noi);
    printk(KERN_INFO "noq: %d \n",noq);
    #endif
   
    //if(down_interruptible(&ldev->sem))  
      // return -ERESTARTSYS;
  
    lsqset=createScull(noi,noq);      
    ldev->sqset=lsqset; 
          
      while(buffsz)
       {
            if(ret==0)
            {   
             if(buffsz>register_size)
             noctw=register_size;
             else
             noctw=buffsz;
            }
 
            if(i==register_no)
             {
               ldev->sqset=ldev->sqset->next;
               i=0;
             }

             ret=copy_from_user(ldev->sqset->data[i],buff+nocsw,noctw);
             /*if(ret>0)                                                    //will work if ret=4   
             {
                i--;
                noctw=ret;
             }*/
             nocsw=nocsw+(noctw-ret);   
              
             #ifdef DEBUG
             printk(KERN_INFO "i:%d noctw: %d  nocsw: %d\n",i,noctw,nocsw);
             #endif
             
              buffsz=buffsz-(noctw-ret);
              *loffptr=nocsw;
              data_size=*loffptr;
              filp->f_pos=nocsw;
              i++;
       }
          
          
          addrbit=inb(PORTADDR+2);  
          ret2=test_bit(0,&addrbit);   //strobe_bit
	  #ifdef DEBUG
          printk(KERN_INFO "strobe bit value at 0x37A is %d",ret2);
          #endif
          	  
	 /* test_and_set_bit(0,&addrbit);   //strobe bit becomes 1      
	  fetch_set=(unsigned char)addrbit;
      
	  outb(fetch_set,PORTADDR+2); 
          
	  test_and_clear_bit(0,&addrbit);
	  fetch_clear=(unsigned char)addrbit;
	  
	  outb(*(char*)(ldev->sqset->data[0]),PORTADDR);	
	  
	  outb(fetch_clear,PORTADDR+2); 
	  mdelay(1000);                   //1 sec low pulse
 	  outb(fetch_set,PORTADDR+2);*/ 
          	  


	  addrbit=inb(PORTADDR+1);  
          ret2=test_bit(7,&addrbit); //busy bit 
	  #ifdef DEBUG
          printk(KERN_INFO "busy bit value at 0x379 is %d",ret2);
          #endif
       
       ldev->data_size=nocsw;
       ldev->sqset=lsqset;
       
      //up(&ldev->sem);        
          
    #ifdef DEBUG
    printk(KERN_INFO "filepos f_pos at: %lld\n",filp->f_pos);
    printk(KERN_INFO "filepos loff  at: %lld\n",*(loffptr));
    printk(KERN_INFO "data_size on device is: %d\n",data_size);
    #endif
    
    j2=jiffies;
    #ifdef DEBUG
    printk(KERN_INFO "j2->%lu and j1->%lu\n",j2,j1);
    #endif

    //rdtsc(tsche,tscle);
    rdtscll(tsclle);
    #ifdef DEBUG
    printk(KERN_INFO "machine cycles used in fun is %lu\n",tsclle-tsclli);
    #endif

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return nocsw;
}

