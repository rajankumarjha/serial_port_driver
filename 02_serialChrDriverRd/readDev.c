#include "headers.h"
#include "decleration.h"

//========================================================================================
//                      printData on qunatums
//========================================================================================
int printQunatumData1(struct myQset *qs, int noi)
{
        int i, j;
        printk(KERN_INFO "\n");
        for(j=0;j<noi;j++)
        {
                if(j<(noi-1))
                {
                        for(i=0;i<8;i++)
                        {
                                printk(KERN_INFO "%.4s",(char*)qs->data[i]);
                        }
                        qs = qs->next;
                }
                else
                {
                        printk(KERN_INFO "%.4s",(char*)qs->data[0]);
                }
        }
        return 0;
}
//========================================================================================
//                      readDev::read data from qunatums
//========================================================================================
ssize_t readDev(struct file *filep, char __user *buff, size_t dataCount, loff_t *loff)
{
	//int nocsr=0, ret, noi, i=0, rQuantums, qSetPos=0, rBytes=0;
	//struct myDev *dvs;
	//struct myQset *qs;
	//unsigned volatile long addrByte = 0x00;
        unsigned char rBYTE = 0x00;

	printk(KERN_INFO "Begin:%s\n",__func__);
#if 0
	dvs = filep->private_data;
       	qs = dvs->data;	
	printk(KERN_INFO "filep->f_pos:%lld  sizeof buff:%lu ,dataCount:%ld, *loff:%lld data_size:%ld\n",filep->f_pos, strlen(buff),dataCount,*loff, dvs->size);

	noi = (dvs->size)/(no_of_registers*size_of_registers); /* items/qset node required */

	rQuantums = (dvs->size)/size_of_registers;
        printk(KERN_INFO "noi%d rQuantums:%d\n",noi,rQuantums);
	//----------------------------------------------------------------
	qSetPos = *loff/size_of_registers; 
	rBytes = (dvs->size)-*loff;
	memset(buff, '\0', dataCount);
	//----------------------------------------------------------------
	wait_for_completion(&dvs->comp);                //wait for write completion
	//----------------------------------------------------------------
	while(rQuantums>=8)
        {
                for(i=(0+qSetPos);i<8;i++)
                {
                        ret = copy_to_user(buff+nocsr,(char*)qs->data[i],size_of_registers);
                        //ret = copy_to_user(buff+nocsr,(char*)qs->data[i+qSetPos], size_of_registers);
                        if(!ret)
                        {
                                nocsr = nocsr + size_of_registers;
                                *loff = nocsr;
                                filep->f_pos = nocsr;
                                printk(KERN_INFO "nocsr:%d\n",nocsr);
                        }
                }
		qSetPos -= 8;if(qSetPos<0)qSetPos=0;
		rQuantums -=8;
                qs = qs->next;
        }

        //printk(KERN_INFO "rQuantums%d\n",rQuantums);
	if(rQuantums<8)
	{
		//if(((dvs->size)-nocsr)>4)
		if((rBytes-nocsr)>4)		//remaining Bytes
                {      
		        i = 0+qSetPos;
		        //i = 0;
			while(i<(rQuantums))
                        {	
                        	//ret = copy_to_user(buff+nocsr,(char*)qs->data[i], size_of_registers);
                        	ret = copy_to_user(buff+nocsr,(char*)qs->data[i], size_of_registers);
                        	if(!ret)
                        	{       
					nocsr = nocsr + size_of_registers;
                        		*loff = nocsr;
                                	filep->f_pos = nocsr;
                        		//printk(KERN_INFO "remainsBytes:%lld nocsr:%d *loff:%lld \n",(dvs->size)-nocsr-(*loff), nocsr, *loff);
                        		printk(KERN_INFO "remainsBytes:%d nocsr:%d *loff:%lld \n",rBytes-nocsr, nocsr, *loff);
                        	}
				i++;
			}
                }
		//if(((dvs->size)-nocsr-(*loff))<4)
		//if(((dvs->size)-nocsr)<4)
		if((rBytes-nocsr)<4)
                {       
			printk(KERN_INFO "x rBytes:%d\n",rBytes-nocsr);
			printk(KERN_INFO "(char*)qs->data[i]: %.2s\n",(char*)qs->data[i]);
                        //ret = copy_to_user(buff+nocsr,(char*)qs->data[i],(dvs->size)-nocsr-(*loff));
                        //ret = copy_to_user(buff+nocsr,(char*)qs->data[i],(dvs->size)-nocsr);
                        ret = copy_to_user(buff+nocsr,(char*)qs->data[i],rBytes-nocsr);
                        if(!ret)
                        {       
				nocsr = nocsr + ((dvs->size)-nocsr);
                        	*loff = nocsr;
                                filep->f_pos = nocsr;
                        	//printk(KERN_INFO "remainsBytes:%lld nocsr:%d *loff:%lld \n",(dvs->size)-nocsr-(*loff), nocsr, *loff);
                        	printk(KERN_INFO "remainsBytes:%ld nocsr:%d *loff:%lld \n",(dvs->size)-nocsr, nocsr, *loff);
                        }
                }
	}
        dvs->size = nocsr;
        printk(KERN_INFO "nocsr:%d *loff:%lld dvs->size:%ld\n", nocsr, *loff,dvs->size);
        qs = dvs->data;
#endif
        //----------------------------------------------------------
	//              write data to serial ports
        //----------------------------------------------------------
        outb(0x03, LCR);        /*select 8 bits data 1:0=11 and 1 stop bit 2:2=0*/
        outb(0x00, IER);        /*disable Interrupt Enable reg.*/
        outb(0x00, FCR);        /*disable fifo control reg.*/
        while(rBYTE!='\0')
        {
                while(!(rBYTE & 0x01))
                {
                        rBYTE = inb(LSR);
                }
        rBYTE = inb(RBR);                      /*received data from register*/
        printk(KERN_INFO "RECEIVED BYTES:%08X\n",rBYTE);
        }
	//----------------------------------------------------------------
	printk(KERN_INFO "End:%s\n",__func__);
	//return nocsr;
	return 0;
}
