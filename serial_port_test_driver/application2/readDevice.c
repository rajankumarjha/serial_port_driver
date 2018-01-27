#include "header.h"

int readDevice(int fd)
{
     int count=0;
     char buff[100];

     printf("%s: Begin\n",__func__);
     
     count=read(fd,buff,100);
     
     if(count==-1)
      perror("read");

     buff[count]='\0';
     printf("bytes read are:%d\n",count);
     printf("buff is:%s\n",buff);

     printf("%s: End\n",__func__);
     return count;
}
