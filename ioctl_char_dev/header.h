#include<linux/init.h>         
#include<linux/module.h>                 
#include<linux/kernel.h>                
#include<linux/fs.h>                     
#include<linux/slab.h>                  //kmalloc
#include<linux/cdev.h>                  
#include<linux/moduleparam.h>          //accept module parameters during insmod                 
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<asm-generic/ioctl.h>         //include/uapi/asm-generic/ioctl.h
#include<linux/sched.h>
#include<linux/capability.h>
#include<linux/jiffies.h>
#include<linux/time.h>
#include<asm/msr.h>                  //machine specific registers
#include<asm/io.h>                  //machine specific registers
#include<linux/timer.h>              
#include<linux/ioport.h>       // for request_resgion() and check_region() and relesae_region()       
#include<linux/bitops.h>
#include<linux/delay.h>

#define DEVNAME "NG_KG_CHAR_DRIVER"


#ifndef DEBUG 
#define DEBUG
#endif


#ifndef MAJORNO
#define MAJORNO 0
#endif

#ifndef MINORNO
#define MINORNO 0
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef REGSIZE 
#define REGSIZE 1
#endif

#ifndef REGNO 
#define REGNO 3
#endif

#ifndef DEVSIZE 
#define DEVSIZE 24
#endif

#ifndef DATASIZE 
#define DATASIZE 0
#endif

#ifndef PORTADDR 
#define PORTADDR 0x378
#endif

extern int majorno,minorno,nod,register_no,register_size,data_size,device_size;
extern dev_t devno,devid;
extern unsigned long tvar1,tvar2;

typedef struct Qset
{
   struct Qset *next;
   void **data;

}Qset;

/*struct timer_list
{
	struct hlist_node       entry;
        unsigned long           expires;
        void                    (*function)(unsigned long);
	unsigned long           data;
	u32                     flags;
	int                     slack;
    #ifdef CONFIG_TIMER_STATS
        int                     start_pid;
	void                    *start_site;
	char                    start_comm[16];
	#endif
	#ifdef CONFIG_LOCKDEP
	struct lockdep_map      lockdep_map;
	#endif

   
};*/

typedef struct Dev
{
    struct cdev c_dev;
    int register_no;               //size of qset array          
    int register_size;            //quantum size
    int data_size;
    int device_size;
    struct Qset *sqset;
    struct semaphore sem;
    struct timer_list tmr;

}Dev;

extern Dev *D_dev; 
