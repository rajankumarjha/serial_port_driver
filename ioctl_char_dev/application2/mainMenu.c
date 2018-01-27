#include "header.h"

int mainMenu()
{
     int choice,fd=-1,origin,offset;
     printf("%s: Begin\n",__func__);
     
     printf("Enter the choice of operation to be done through application:\n");
     printf("1-->device open\n");
     printf("2-->device close\n");
     printf("3-->device write\n");
     printf("4-->device read\n");
     printf("5-->device seek\n");
     printf("6-->IOCTL\n");
     printf("0-->exit application\n");
 
     scanf("%d",&choice);
     
     while(1)
     {
       switch(choice)
       {
         case 1: printf("device open selected\n"); 
                 if(fd<0)  
                   fd=openDevice();
                 else
                   printf("device already opened\n"); 
                 break;

         case 2: printf("device close selected\n");   
                 if(fd<0)  
                   printf("device not opened\n"); 
                 else
                  {
                   closeDevice(fd);  
                   fd=-1;
                  }                
                 break;

         case 3: printf("device write selected\n");   
                 //if(fd<0)  
                 if(flag!=1)  
                   printf("device not opened in write only mode\n"); 
                 else
                   writeDevice(fd);                  
                 break;

         case 4: printf("device read selected\n");   
                 //if(fd<0)  
                 if(flag!=2)  
                   printf("device not opened in read only mode\n"); 
                 else
                   readDevice(fd);                  
                 break;

         case 5: printf("device seeking selected\n");   
                 if(fd<0)  
                   printf("device not opened\n"); 
                 else 
                  {
                   seekDevice(fd);   
                  }               
                 break;

         case 6: printf("IOCTL selected\n");
                 ioctlDevice(fd); 
                 break;

         case 0: printf("Exit the application mode selected\n");
                 exit(EXIT_FAILURE);

         default:printf("invalid choice\n");   
                 break;
       }
     	printf("Re-Enter choice\n");
     	printf("1-->device open\n");
     	printf("2-->device close\n");
     	printf("3-->device write\n");
     	printf("4-->device read\n");
        printf("5-->device seek\n");
        printf("6-->IOCTL\n");
     	printf("0-->exit application\n");
       	scanf("%d",&choice);
     }
     printf("%s: End\n",__func__);
     return fd;
}
