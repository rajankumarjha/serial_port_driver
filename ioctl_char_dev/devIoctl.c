#include"header.h"
#include"declaration.h"
#include"ioctl.h"

long devIoctl(struct file *filp,unsigned int request,unsigned long arg)
{
    Dev *ldev=NULL;    
    int para=0;
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
 
    ldev=filp->private_data;
    printk(KERN_INFO "request is %u\n",request); 
    switch(request)
    {
      case DEVRESET:
                       printk("Dev Reset demanded\n");
                       devTrim(ldev);
                       break;
      case GETREGSIZE:
                       printk("Get Reg size selected\n");
		       if(access_ok(VERIFY_READ,(void __user*)arg,sizeof(int)))       //returns 1 for success
                       put_user(ldev->register_size,(int __user*)arg);  //get_user and put_user used to print single values(int,char,long) for larger buffer copy_from_user and copy_to_user can be used                        
                       break;
      case GETREGNO:   
                       printk("Get Res no selected\n");
		       if(access_ok(VERIFY_READ,(void __user*)arg,sizeof(int)))  
                       put_user(ldev->register_no,(int __user*)arg);
                       break;
      case GETDEVSIZE:
                       printk("Get dev size selected\n");
		       if(access_ok(VERIFY_READ,(void __user*)arg,sizeof(int)))   
                       put_user(ldev->device_size,(int __user*)arg);
                       break;
      case GETDATASIZE:
                       printk("Get data size selected\n");
		       if(access_ok(VERIFY_READ,(void __user*)arg,sizeof(int)))    
                       put_user(ldev->data_size,(int __user*)arg);
                       break;
      case GETBAUDRATE:
                       printk("Get baud rate selected\n");
                       break;
      case SETREGSIZE: 
                       printk("Set reg size selected\n");
		       if(!capable(CAP_SYS_ADMIN))
		        {
			    printk(KERN_INFO "error:capable\n");
			    goto ERR;
			}
		       if(access_ok(VERIFY_WRITE,(void __user*)arg,sizeof(int)))    
		       		get_user(para,(int __user*)arg); 
		       printk("reg size. is %d\n",para); 
		       ldev->register_size=para;
		       register_size=para;
                       break;
      case SETREGNO:   
                       printk("Set reg no selected\n");
		       if(!capable(CAP_SYS_ADMIN))
		        {
			    printk(KERN_INFO "error:capable\n");
			    goto ERR;
			}
		       if(access_ok(VERIFY_WRITE,(void __user*)arg,sizeof(int)))     
		       		get_user(para,(int __user*)arg); 
		       printk("reg no. is %d\n",para); 
		       ldev->register_no=para;
		       register_no=para;
                       break;
      case SETBAUDRATE:
                       printk("Set baud rate selected\n");
                       break;
      default:
                       printk("invalid choice\n");
    }

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
   
    return 0;

   ERR:
           
    #ifdef DEBUG
    printk(KERN_INFO "%s :End with error\n",__func__);
    #endif
    return -1;
}

