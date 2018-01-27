#include"header.h"
#include"declaration.h"

void timerFunc(unsigned long data)
{
    
    #ifdef DEBUG
    printk(KERN_INFO "%s :Begin\n",__func__);
    #endif
 

    #ifdef DEBUG
    printk(KERN_INFO "%s :End\n",__func__);
    #endif
   
    //return 0;
}

