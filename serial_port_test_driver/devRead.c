#include"header.h"
#include"declaration.h"

ssize_t devRead(struct file *filp,char __user *buff,size_t buffsz,loff_t *loffptr)
{
     //int i=0,j=0,ret=0,noctr=0,nocsr=0,oiq;
    //loff_t lsize;
    Dev *ldevp;
    Qset *lqsetp;
    volatile unsigned long addrbit;
    unsigned char check_byte,data_byte=0x01;
    int count=1,ret=0,ret2,nocsr=0;
    //unsigned long j1,j2,tsclli,tsclle;
    //j1=jiffies;
    //tvar2=jiffies;

    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
    
    //	rdtscll(tsclli);
   
    #ifdef DEBUG
    printk(KERN_INFO "buffer size: %lu bytes\n",buffsz);
    #endif
    
    ldevp=filp->private_data;
    #ifdef DEBUG
    printk(KERN_INFO "ldev address is: %p\n",ldevp);
    #endif
    
    lqsetp=ldevp->sqset;
   
     outb(0x03,LCR);    //configure LCR
     outb(0x00,IER);    //configure IER
     outb(0x00,FCR);   //configure FCR
     
     //checking bits of LSR
     addrbit=inb(LSR);
     check_byte=(unsigned char)addrbit;
     ret2=test_bit(0,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "DR bit is %d",ret2);
     #endif
     ret2=test_bit(1,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "OE bit is %d",ret2);
     #endif
     ret2=test_bit(2,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "PE bit is %d",ret2);
     #endif
     ret2=test_bit(3,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "FE bit is %d",ret2);
     #endif
     ret2=test_bit(4,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "BI bit is %d",ret2);
     #endif
     ret2=test_bit(5,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "THRE bit is %d",ret2);
     #endif
     ret2=test_bit(6,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "TEMT bit is %d",ret2);
     #endif
     ret2=test_bit(7,&addrbit);       
     #ifdef DEBUG
     printk(KERN_INFO "ERR_RCVR bit is %d",ret2);
     #endif
     
	/*check_byte=(unsigned char)addrbit;
	while(!(check_byte & 0x01))
	{
	   addrbit=inb(LSR);
	   check_byte=(unsigned char)addrbit;
	}*/
     
     addrbit=inb(MSR);
     ret=test_bit(4,&addrbit);     //CTS is 0 initially

//METHOD 1
    /*
     while(data_byte!='\0')
      {  
         
	 //wait for transmitter ack
	 while(!ret)
	  {
            addrbit=inb(MSR)
     	    ret=test_bit(4,&addrbit);	    
	  }
	 ret=!ret;

 	 data_byte=inb(RBR);
       	 #ifdef DEBUG
     	 printk(KERN_INFO "data_byte rec is %c",data_byte);
	 #endif
         ret2=copy_to_user(buff+nocsr,&data_byte,1);
         
	 addrbit=inb(MCR);     
	 test_and_set_bit(1,&addrbit);   //0 initially
         outb((unsigned char)addrbit,MCR);
	 udelay(1);
	 test_and_clear_bit(1,&addrbit);
         outb((unsigned char)addrbit,MCR);

	 nocsr++;
       }

      */ 

//METHOD 2

	 addrbit=inb(MCR);     
	 test_and_clear_bit(1,&addrbit);   //0 initially
         outb((unsigned char)addrbit,MCR);
     
     while(data_byte!='\0')
      {  
         
	 //wait for transmitter ack
	 if(count%2!=0)                  //for odd count wait for 1
              {
		 while(!ret)
		  {
        	    addrbit=inb(MSR);
     		    ret=test_bit(4,&addrbit);	    
		  }
               }
	  else                      
              {
		 while(ret)
		  {
        	    addrbit=inb(MSR);
     		    ret=test_bit(4,&addrbit);	    
		  }
               }


 	 data_byte=inb(RBR);
       	 #ifdef DEBUG
     	 printk(KERN_INFO "data_byte rec is %c",data_byte);
	 #endif
         ret2=copy_to_user(buff+nocsr,&data_byte,1);
         
	 addrbit=inb(MCR);     
	 test_and_change_bit(1,&addrbit);   //0 initially
         outb((unsigned char)addrbit,MCR);
         
	 count++;
	 nocsr++;
       }
	 return (nocsr-1);
}
