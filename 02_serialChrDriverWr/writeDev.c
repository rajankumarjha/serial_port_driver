#include "headers.h"
#include "decleration.h"

//========================================================================================
//			get the new qset node
//========================================================================================
struct myQset * getAddNewItems(struct myQset *strtQset)
{
	struct myQset *nwQset;
	if(!strtQset->next)
	{
		nwQset = kmalloc(sizeof(struct myQset), GFP_KERNEL);
		memset(nwQset,0,sizeof(struct myQset));
		strtQset->next = nwQset;
	}
	else
	{
		return strtQset;
	}
	return nwQset; 
}       
//========================================================================================
//			printData on qunatums
//========================================================================================
int printQunatumData(struct myQset *qs, int lsize)
{
	int i=0, rBytes = 0 , rQuantums;
	rQuantums = lsize/size_of_registers;
	if ((lsize%size_of_registers)!=0)
		rQuantums++;
	rBytes = lsize;
	while(rQuantums>=8)
	{
        	for(i=0;i<8;i++)
       		{
          		printk(KERN_INFO "%.4s",(char*)qs->data[i]);
			rBytes -= 4;
          	}
		rQuantums -=8;
                qs = qs->next;
	}
	if(rQuantums<8)
	{
		if(rBytes>4)
		{
			i = 0;
			while(i<(rQuantums-1))
			{
				printk(KERN_INFO "%.4s",(char*)qs->data[i]);
				rBytes -= 4;
				i++;
			}
		}
		if(rBytes<4)
		{
			if(rBytes==1)
			{
				printk(KERN_INFO "%.1s",(char*)qs->data[i]);
			}
			if(rBytes==2)
			{
				printk(KERN_INFO "%.2s",(char*)qs->data[i]);
			}
			if(rBytes==3)
			{
				printk(KERN_INFO "%.3s",(char*)qs->data[i]);
			}
		}
	}
	return 0;
}
//=========================================================================================
//			kernel dev write calls
//=========================================================================================
ssize_t writeDev(struct file *filep, const char __user *buff, size_t dataCount, loff_t *f_pos)
{
	struct myDev *dvs;
	struct myQset *qs;
	int quantum, qset, ret, noi, r_noi, i, j, k , rQuantums, lsize;			//noi: number of items

	int nocsw = 0;
	printk(KERN_INFO "Begin:%s\n",__func__);
	dvs = filep->private_data;
	quantum = dvs->quantum;
	qset = dvs->qset;
	lsize = dataCount;
	//-----------------------------------------------------------------
	//		three step checks
	//-----------------------------------------------------------------
	if((filep->f_flags & O_ACCMODE)!=O_WRONLY)	/*check if it opened in write mode*/
        {
                printk(KERN_INFO "error! f_flag not O_WRONLY!!\n");
                goto out;
        }
	if(!buff || (dataCount <=0))			/*check if buff is not null*/
	{
		printk(KERN_INFO "error! buff is null!!\n");
                goto out;
	}
	//-----------------------------------------------------------------
	printk(KERN_INFO "sizeof buff:%lu ,dataCount:%ld\n",strlen(buff),dataCount);
	noi = dataCount/(no_of_registers*size_of_registers); /* items/qset node required */
	if((dataCount%no_of_registers*size_of_registers)!=0)
		noi++;
	
	rQuantums = dataCount/size_of_registers;
	if ((dataCount%size_of_registers)!=0)
		rQuantums++;

	printk(KERN_INFO "noi%d rQuantums:%d\n",noi,rQuantums);
	//---------------------------------------------------------------------------------------------------
	if (down_interruptible(&dvs->sem))		//semaphore to avoid multiple writes one at a time
      		return -ERESTARTSYS;
	//---------------------------------------------------------------------------------------------------
	//wait_for_completion(&dvs->comp);		//wait for completion
	//----------------------------------------------------------------get Number of items/linkedList node
	for(i=0;i<noi;i++)
	{
		if(i==0)				/* Allocating first qset */
		{
			qs = dvs->data;
			qs = dvs->data = kmalloc(sizeof(struct myQset), GFP_KERNEL);
			memset(qs,0,sizeof(struct myQset));
		}
		else					/* Allocating rest of qset */
		{
			qs = getAddNewItems(qs);
		}
	}
	//------------------------allocate memory for each quantums------------------------------------------------
	qs = dvs->data;					/* get the original start node*/
	for(i=0;i<noi;i++)				/*get qSet Array!!*/
	{
		if(!qs){
			goto out;
		}

		qs->data = kmalloc(no_of_registers * sizeof(char *), GFP_KERNEL);
		memset(qs->data, 0, no_of_registers * sizeof(char *));

		for(j=0;j<8;j++)
		{
			qs->data[j]=kmalloc(size_of_registers * sizeof(char *), GFP_KERNEL);
			lsize-=size_of_registers;
		}
		qs = qs->next;				/* for next poiting qsets */
	}
	//------------------------write data to each quantums------------------------------------------------
	qs = dvs->data;
	lsize = dataCount;
	noi = (dataCount/(no_of_registers*size_of_registers));
	for(k=0;k<noi;k++)				/*get qSet Array!!*/
	{
		for(i=0;i<8;i++)
		{
			ret = copy_from_user((char*)qs->data[i],buff+nocsw,size_of_registers);
			if(!ret)
			{
				nocsw = nocsw + size_of_registers;
				*f_pos = nocsw;
				filep->f_pos = nocsw;	
				lsize-=size_of_registers;
			}
		}
		qs = qs->next;
	}
	r_noi = (dataCount%(no_of_registers*size_of_registers));
	if((r_noi)!=0)
	{
		rQuantums = lsize/size_of_registers;
                for(k=0;k<rQuantums;k++)
                {
			ret = copy_from_user((char*)qs->data[k],buff+nocsw,size_of_registers);
			if(!ret)
			{
				nocsw = nocsw + size_of_registers;
				*f_pos = nocsw;
				printk(KERN_INFO "nocsw:%d *f_pos:%lld \n",nocsw, *f_pos);
			}
                        lsize-=size_of_registers;
                }
                if(lsize%size_of_registers!=0)
                {
			ret = copy_from_user((char*)qs->data[k++],buff+nocsw,lsize);
			if(!ret)
			{
				nocsw = nocsw + lsize;
				*f_pos = nocsw;
				printk(KERN_INFO "nocsw:%d *f_pos:%lld \n",nocsw, *f_pos);
			}
                        lsize-=size_of_registers;
                }
	}
	//----------------------------------------------------------
	//		write data to serial ports
	//----------------------------------------------------------
	outb(0x03, LCR);	/*select 8 bits data 1:0=11 and 1 stop bit 2:2=0*/
	outb(0x00, IER);	/*disable Interrupt Enable reg.*/
	outb(0x00, FCR);	/*disable fifo control reg.*/
	outb(0xFB, THR);	/*send data to Transmit and hold register*/

	//outb(*(unsigned char*)qs->data[0],BASE_SERIAL_PORT_ADDRS);
	dvs->size = nocsw;
	qs = dvs->data;
	lsize = dataCount;

	//complete(&dvs->comp);		/*done completion only allow once read for one writeDev*/
	complete_all(&dvs->comp);	/*done completion for all other readDev*/
	up(&dvs->sem);		/**release semaphore*/
	printQunatumData(qs, lsize);	/*see if data is correctly stored in quantums*/
	return nocsw;

out:
	return -1;
}
