#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"ioctl.h"

int mainMenu();
int openDevice();
int closeDevice(int);
int writeDevice(int);
int readDevice(int);
int seekDevice(int);
int ioctlDevice(int);

extern int flag;
