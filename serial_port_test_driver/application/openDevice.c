#include "header.h"

int openDevice()
{
     int choice,fd=-1;
     printf("%s: Begin\n",__func__);
     
     printf("Enter the choice in which you want to open the device\n");
     printf("1->Write only\n");
     printf("2->Read  only\n");
    
     scanf("%d",&choice);
     
     switch(choice)
     {
        case 1: 
                printf("open in write only mode selected\n");
                fd=open("../myDev",O_WRONLY);
                if(fd<0)
                {
                 perror("open:");
                }
                flag=1;
                break;
        case 2: 
                printf("open in read only mode selected\n");
                fd=open("../myDev",O_RDONLY);
                if(fd<0)
                {
                 perror("open:");
                }
                flag=2;
                break;
        default:
                printf("Wrong choice\n");
                exit(EXIT_FAILURE);
     }

     printf("fd is : %d\n",fd);
     printf("%s: End\n",__func__);
     return fd;
}
