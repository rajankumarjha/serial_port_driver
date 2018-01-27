#include"header.h"
#include"declaration.h"

ssize_t devRead(struct file *filp,char __user *buff,size_t buffsz,loff_t *loffptr)
{
    //int i=0,j=0,ret=0,noctr=0,nocsr=0,oiq;
    //loff_t lsize;
    Dev *ldevp;
    Qset *lqsetp;
    volatile unsigned long addrbit;
    unsigned char check_byte,data_byte;
    int count =0;
    //Dev ldev;
    
    //unsigned long j1,j2,tsclli,tsclle;
    //j1=jiffies;
    //tvar2=jiffies;

    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
    
    	//rdtscll(tsclli);

    #ifdef DEBUG
    printk(KERN_INFO "buffer size: %lu bytes\n",buffsz);
    #endif
    
    ldevp=filp->private_data;
    #ifdef DEBUG
    printk(KERN_INFO "ldev address is: %p\n",ldevp);
    #endif
    
    lqsetp=ldevp->sqset;
    
    addrbit=inb(PORTADDR+1);
    check_byte=(unsigned char)addrbit;
    #ifdef DEBUG
    printk(KERN_INFO "value at 0x379 is : %x\n",check_byte);
    #endif
    
    addrbit=inb(PORTADDR+1);
    check_byte=(unsigned char)addrbit;
    #ifdef DEBUG
    printk(KERN_INFO "value at 0x379 is : %x\n",check_byte);
    #endif
   
    while(!(check_byte & 0x80))
    {
    
    addrbit=inb(PORTADDR+1);
    check_byte=(unsigned char)addrbit;
    #ifdef DEBUG
    printk(KERN_INFO "value of status register 0x379 is : %x\n",check_byte);
    #endif

    count++;
    if(count==10)
     break;
    
    }

    data_byte=inb(PORTADDR);
    #ifdef DEBUG
    printk(KERN_INFO "data_byte at 0x378 is : %x\n",data_byte);
    #endif
    return data_byte;  
 }
    #if 0
    #ifdef DEBUG
    printk(KERN_INFO "filepos f_pos at : %lld\n",filp->f_pos);
    printk(KERN_INFO "filepos loff  at: %lld\n",*(loffptr));
    printk(KERN_INFO "data_size on device is: %d\n",data_size);
    #endif
     
     // if(down_interruptible(&ldevp->sem))
       //   return -ERESTARTSYS;        

      lsize=data_size-filp->f_pos;

      i=((filp->f_pos)/(register_size));
      if(i>=register_no)
        i=i%register_no;

      j=(filp->f_pos)/(register_size*register_no);

      while(j)
      {
        ldevp->sqset=ldevp->sqset->next;
        j--;
      }
      
      oiq=filp->f_pos%register_size;
      #ifdef DEBUG
      printk(KERN_INFO "oiq is %d\n",oiq);
      #endif

      while(lsize)
       {
             if(ret==0)
             {
              if(lsize>register_size)
              noctr=register_size-oiq;
              else
              noctr=lsize;
             }
 
             if(i==register_no)
              {
                ldevp->sqset=ldevp->sqset->next;
                i=0;
              }

             ret=copy_to_user(buff+nocsr,ldevp->sqset->data[i]+oiq,noctr);

             /*if(ret>0)
             {
                i--;
                noctr=ret;
             }*/

             nocsr=nocsr+(noctr-ret);
               
             #ifdef DEBUG
             printk(KERN_INFO "i:%d noctr: %d  nocsr: %d\n",i,noctr,nocsr);
             #endif

             lsize=lsize-(noctr-ret);
             *loffptr=filp->f_pos+nocsr;
             i++;
             oiq=0;
       }

    filp->f_pos=filp->f_pos+nocsr;
    ldevp->sqset=lqsetp;
     
    //up(&ldevp->sem);   

    #ifdef DEBUG
    printk(KERN_INFO "file_pos at: %lld\n",filp->f_pos);
    printk(KERN_INFO "file_pos at: %lld\n",*(loffptr));
    #endif

    j2=jiffies;
    #ifdef DEBUG
    printk(KERN_INFO "j1->%lu and j2->%lu\n",j1,j2);
    #endif

    if(time_after(tvar1,tvar2))      //true when tvar1 comes after tvar2
     {
    	#ifdef DEBUG
    	printk(KERN_INFO "tvar1 comes before tvar2\n");
    	#endif
     }

    if(time_before(tvar1,tvar2))    
     {
    	#ifdef DEBUG
    	printk(KERN_INFO "tvar1 comes before tvar2\n");
    	#endif
     }
    	rdtscll(tsclle);
    	#ifdef DEBUG
        printk(KERN_INFO "machine cycles used in fun is %lu\n",tsclle-tsclli);
        #endif

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return nocsr;

}
#endif
