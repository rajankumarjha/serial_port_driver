#include "header.h"

int ioctlDevice(int fd)
{

     printf("%s: Begin\n",__func__);
     int ret,choice;
     //struct parameters para;
     int arg;

     while(1)
     {
         printf("Enter the choice\n");
         printf("0->Device reset\n");       
         printf("1->Get Register size\n");       
         printf("2->Get Register no\n");       
         printf("3->Get Device size\n");       
         printf("4->Get Data size\n");       
         printf("5->Get Baud rate\n");       
         printf("6->Set Register size\n");       
         printf("7->Set Register no\n");       
         printf("8->Set Baud rate\n");    
         printf("9->EXIT\n");    
    
         scanf("%d",&choice);
          
         switch(choice)
          {
             case 0:     printf("device reset selected\n");
  	   		 ret=ioctl(fd,DEVRESET,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
                          break;

             case 1:     printf("get register size selected\n");
  	   		 ret=ioctl(fd,GETREGSIZE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
    			 printf("Reg Size is %d\n",arg);
                          break;

             case 2:     printf("get register no selected\n");
  	   		 ret=ioctl(fd,GETREGNO,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
    			 printf("Reg no is %d\n",arg);
                          break;

             case 3:     printf("get device size selected\n");
  	   		 ret=ioctl(fd,GETDEVSIZE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
    			 printf("device size is %d\n",arg);
                          break;

             case 4:     printf("get data size selected\n");
  	   		 ret=ioctl(fd,GETDATASIZE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
    			 printf("data size is %d\n",arg);
                          break;

             case 5:     printf("get baud rate selected\n");
  	   		 ret=ioctl(fd,GETBAUDRATE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
    			 printf("baud rate is %d\n",arg);
                          break;   

             case 6:     printf("set register size selected\n");
                         printf("enter the register size\n");
                         scanf("%d",&arg);
  	   		 ret=ioctl(fd,SETREGSIZE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
                          break;

             case 7:     printf("set register no selected\n");
                         printf("enter the register no\n");
                         scanf("%d",&arg);
  	   		 ret=ioctl(fd,SETREGNO,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
                          break;

             case 8:     printf("set baud rate selected\n");
                         printf("enter the baud rate\n");
                         scanf("%d",&arg);
  	   		 ret=ioctl(fd,SETBAUDRATE,&arg);
  	  		 if(ret<0)
  	   		   perror("ioctl");
                          break;
             case 9: 
                         goto OUT;
          }
     
     }
     printf("%s: End\n",__func__);
     return 0;
     
     OUT: 
          return 0;
          printf("%s: End\n",__func__);
     
}
