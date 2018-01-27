#include "header.h"

int writeDevice(int fd)
{
     int count=0;
     //char buff[100]="Emblogic Research & Competency Development Labs NOIDA";
     //char buff[100]="Emblogic Embedded Technologies Pvt Ltd";
     unsigned char ch;
     printf("%s: Begin\n",__func__);
     ch = 0x55;
     //count=write(fd,buff,strlen(buff));
     count=write(fd,&ch,1);

     if(count==-1)
      perror("write");

     printf("bytes written are:%d\n",count);

     printf("%s: End\n",__func__);
     return count;
}
