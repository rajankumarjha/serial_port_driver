#include "header.h"

int seekDevice(int fd)
{
     int offset,origin,newpos;

     printf("%s: Begin\n",__func__);
     
     printf("Enter the offset value\n");
     scanf("%d",&offset);
     printf("Enter the origin value 0->SEEK_SET,1->SEEK_CUR,2->SEEK_END\n");
     scanf("%d",&origin);
     
     newpos=lseek(fd,offset,origin);                //returns new offset value if pass else ret (loff_t)-1
     if(newpos==-1)
      perror("lseek");

     printf("%s: End\n",__func__);
     return newpos;
}
