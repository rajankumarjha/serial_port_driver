#include "header.h"
#include "declaration.h"

ssize_t devWrite(struct file *filp,const char __user *buff,size_t buffsz,loff_t *loffptr)
{
    Dev *ldev=NULL;
    Qset *lsqset=NULL;
    int noi=0,noq=0,i=0,ret=0,noctw=0,nocsw=0,ret2,count=1;
 //   unsigned long j1,j2,tsclli,tsclle;
    unsigned volatile long addrbit;
    unsigned char check_byte;
    //int count=0;
  //  j1=jiffies;
   // tvar1=jiffies;
   
    //rdtsc(tschi,tscli);
    //rdtscll(tsclli);
    
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
          
          buffsz=nocsw;
          i=0;
          ldev->sqset=lsqset;
        
	//Configure Line Control Register
        //enable the RBR,THR,IER 
	outb(0x03,LCR);             //frame of 8 bit word length with one stop bit 
 
        //Disable Interrupt Enable Register
	outb(0x00,IER);
        
        //configure Fifo Control Register
	outb(0x00,FCR);            //enable 16450 mode (non-fifo)
        
	//checking the bits of Line Status Register
        addrbit=inb(LSR);  
        check_byte=(unsigned char)addrbit;
        ret2=test_bit(0,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "DR bit is %d\n",ret2);      //0
       	#endif
        ret2=test_bit(1,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "OE bit is %d\n",ret2);    //0
       	#endif
        ret2=test_bit(2,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "PE bit is %d\n",ret2);     //0
       	#endif
        ret2=test_bit(3,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "FE bit is %d\n",ret2);    //0
       	#endif
        ret2=test_bit(4,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "BI bit is %d\n",ret2);    //0
       	#endif
        ret2=test_bit(5,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "THRE bit is %d\n",ret2);    //1
       	#endif
        ret2=test_bit(6,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "TEMT bit is %d\n",ret2);    //1
       	#endif
        ret2=test_bit(7,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "ERR_RCVR bit is %d\n",ret2);   //0
       	#endif
 
        addrbit=inb(MCR);
        ret2=test_bit(1,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "RTS bit is %d\n",ret2);   //0 initially (PORT pin 7 volt--> -10V)
       	#endif
        addrbit=inb(MSR);
        ret2=test_bit(4,&addrbit);
  	#ifdef DEBUG
	printk(KERN_INFO "CTS bit is %d\n",ret2);   //0 initially (PORT pin 8 volt--> 0V)
       	#endif
        
	addrbit=inb(MSR);
        ret=test_bit(4,&addrbit);  //0 initially

 //METHOD 1
        /* while(buffsz)
           {
		#ifdef DEBUG
          	printk(KERN_INFO "char to write is %c\n",*(char*)(ldev->sqset->data[i]));
          	#endif
          	outb(*(char*)(ldev->sqset->data[i]),THR);	

	        addrbit=inb(LSR);
                check_byte=(unsigned char)addrbit;
		while(!(check_byte & 0x40))          //check TEMT bit,wait for TEMT to become 1(both THR and TSR to get empty)
	       	{
	          addrbit=inb(LSR);
                  check_byte=(unsigned char)addrbit;
	       	}
                
		//when both THR and TSR empty enable RTS to ack receiver
                
		addrbit=inb(MCR);
		test_and_set_bit(1,&addrbit);      //RTS=1(PORT volt--> 11V) will make CTS of DTE2 to 1
		outb((unsigned char)addrbit,MCR);     
                udelay(1);
		test_and_clear_bit(1,&addrbit);
		outb((unsigned char)addrbit,MCR);     
		
		if(i==register_no-1)
            	 {
            	   ldev->sqset=ldev->sqset->next;
            	   i=-1;
            	 }	
	        i++;
                buffsz=buffsz-1;
		
		//wait for reader to send ack
        	while(!ret)
		{
		  addrbit=inb(MSR)
        	  ret=test_bit(4,&addrbit);  
                }
		ret=!ret;
            }
       
       outb(0x00,THR);      //null char for ack
	        
		addrbit=inb(LSR);
                check_byte=(unsigned char)addrbit;
		while(!(check_byte & 0x40))         
	       	{
	          addrbit=inb(LSR);
                  check_byte=(unsigned char)addrbit;
	       	}
		addrbit=inb(MCR);
		test_and_set_bit(1,&addrbit);      
		outb((unsigned char)addrbit,MCR);     
                udelay(1);
		test_and_clear_bit(1,&addrbit);
		outb((unsigned char)addrbit,MCR);     
	   */
 //METHOD 2
             
	        addrbit=inb(MCR);
	        test_and_set_bit(1,&addrbit);
	        outb((unsigned char)addrbit,MCR);
	        
		//addrbit=inb(MCR);
	        //test_and_clear_bit(1,&addrbit);
	        //outb((unsigned char)addrbit,MCR);
        	
		addrbit=inb(MSR);
		ret2=test_bit(1,&addrbit);
  		#ifdef DEBUG
		printk(KERN_INFO "RTS bit after set is %d\n",ret2);   //0 initially (PORT pin 8 volt--> 0V)
       		#endif
               

	 /*while(buffsz)
           {
		#ifdef DEBUG
          	printk(KERN_INFO "char to write is %c\n",*(char*)(ldev->sqset->data[i]));
          	#endif
          	outb(*(char*)(ldev->sqset->data[i]),THR);	

	        addrbit=inb(LSR);
                check_byte=(unsigned char)addrbit;
		while(!(check_byte & 0x40))          //check TEMT bit,wait for TEMT to become 1(both THR and TSR to get empty)
	       	{
	          addrbit=inb(LSR);
                  check_byte=(unsigned char)addrbit;
	       	}
                
		//when both THR and TSR empty enable RTS to ack receiver
                
		addrbit=inb(MCR);
		test_and_change_bit(1,&addrbit);      //for first run RTS=1(PORT volt--> 11V) will make CTS of DTE2 to 1
		outb((unsigned char)addrbit,MCR);     
		
		if(i==register_no-1)
            	 {
            	   ldev->sqset=ldev->sqset->next;
            	   i=-1;
            	 }	
	        i++;
                buffsz=buffsz-1;
		
		//wait for reader to send ack
                if(count%2!=0)                 //for odd runs
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
	         count++;	   
            }
                
		outb(0x00,THR);     
		addrbit=inb(LSR);
                check_byte=(unsigned char)addrbit;
		while(!(check_byte & 0x40))          
	       	{
	          addrbit=inb(LSR);
                  check_byte=(unsigned char)addrbit;
	       	}
		addrbit=inb(MCR);
		test_and_change_bit(1,&addrbit);      
		outb((unsigned char)addrbit,MCR);     

		addrbit=inb(MCR);
		test_and_clear_bit(1,&addrbit);      
		outb((unsigned char)addrbit,MCR);     
*/
       ldev->data_size=nocsw;
       ldev->sqset=lsqset;
      //up(&ldev->sem);        
          
    #ifdef DEBUG
    printk(KERN_INFO "filepos f_pos at: %lld\n",filp->f_pos);
    printk(KERN_INFO "filepos loff  at: %lld\n",*(loffptr));
    printk(KERN_INFO "data_size on device is: %d\n",data_size);
    #endif
    
    /*j2=jiffies;
    #ifdef DEBUG
    printk(KERN_INFO "j2->%lu and j1->%lu\n",j2,j1);
    #endif*/

    //rdtsc(tsche,tscle);
    /*rdtscll(tsclle);
    #ifdef DEBUG
    printk(KERN_INFO "machine cycles used in fun is %lu\n",tsclle-tsclli);
    #endif*/

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
    return nocsw;
}

