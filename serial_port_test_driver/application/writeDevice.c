#include "header.h"

int writeDevice(int fd)
{
     int count=0;
     unsigned char buff[100]="Emblogic Research & Competency Development Labs NOIDA";
     //unsigned char ch;
     printf("%s: Begin\n",__func__);

     //count=write(fd,buff,strlen(buff));
     count=write(fd,buff,strlen(buff));

     if(count==-1)
      perror("write");

     printf("bytes written are:%d\n",count);

     printf("%s: End\n",__func__);
     return count;
}
