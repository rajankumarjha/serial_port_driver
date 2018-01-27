#include "header.h"

int closeDevice(int fd)
{

     printf("%s: Begin\n",__func__);
     
     close(fd);

     printf("%s: End\n",__func__);

     return 0;
}
