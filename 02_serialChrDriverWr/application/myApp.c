#include "headers.h"
#include "decleration.h"
#define READ_MODE	1
#define WRITE_MODE	2


int main()
{
	int fd,ch,openChoice, fdOpened,byteWritten=0, byteRead=0,i,curPos=0;
	unsigned char * userBuff = (char*) malloc(sizeof(char)*100);
	unsigned char * readBuff = (char*) malloc(sizeof(char)*100);
	memset(readBuff, '\0', sizeof(char)*100);
	//userBuff = "****** my first charDev data! a my aaaaa charDev data! a my bbbbb charDev data! a my ccccc charDev data! #";
	//userBuff = "****** my first charDev data!********#";
	//userBuff = "my first charDev data!";
	//userBuff = 0xAA;
	unsigned char Data = 0xBA;
	printf("Begins:%s\n",__func__);
	while(1)
	{
		ch = mainMenu();	
		switch(ch)
		{
			case 0:
				printf("exiting...!\n");
				exit(EXIT_SUCCESS);
			case 1:
				//----------------------------------------/* open fd in write/read mode */
				openChoice = chooseOpenReadMode();
				switch(openChoice)
				{
					case 1:
                                		fd = open("../myDev",O_WRONLY);
						printf("device opened fd:%d in WriteMode...!\n",fd);
						fdOpened = WRITE_MODE;
						break;
					case 2:
                                                fd = open("../myDev",O_RDONLY);
						printf("device opened fd:%d in ReadMode...!\n",fd);
						fdOpened = READ_MODE;
                                                break;
					default:
						printf("wrong choice!!\n");

				}
				//-------------------------------------------------------------------------
				break;
			case 2:
				printf("closing device file myDev...!\n");
				close(fd);
					fdOpened = 0;
				break;
			case 3:
				if(fdOpened == WRITE_MODE)
				{
					//byteWritten = write(fd, userBuff, strlen(userBuff));
					//for(i=0;i<50;i++)
					//{
						byteWritten = write(fd, &Data, 1);
						//sleep(3);
						//Data = 0x55;
						//byteWritten = write(fd, &Data, 1);	
					//}
					printf("bytes written:%d\n",byteWritten);
					close(fd);
					fdOpened = 0;
					printf("write fd:%d closed!!\n",fd);
				}
				else
					printf("file closed! please open or opened in wrong mode!\n");
				break;
			case 4:
				if(fdOpened = READ_MODE)
				{
					byteRead = read(fd, readBuff, 100);
					printf("no of data read:%d\n",byteRead);
					printf("readData:%s\n",readBuff);
					close(fd);
					fdOpened = 0;
					printf("read fd:%d closed!!\n",fd);
				}
				else
					printf("file closed! please open or opened in wrong mode!\n");
				break;
			case 5:
				curPos = lseek(fd,12,SEEK_SET);
				if(curPos<0) 
				{
					perror("lseek:");
					return 1;
				}
				else{
					printf("curPos,after seek::%d\n",curPos);
				}
				memset(readBuff, '\0', 100);
				byteRead = read(fd, readBuff, 100);
                                printf("readData:%s\n",readBuff);
				break;
			case 6:
				openChoice = chooseIoctOptions();
				printf("Your Choice :%d\n",openChoice);
				break;
			deafult:
				printf("wrong option!\n");

		}
	}
	printf("End:%s\n",__func__);	
	return 0;
}
