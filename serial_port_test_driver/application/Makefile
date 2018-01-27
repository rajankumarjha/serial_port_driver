#! /bin/bash

app: main.o mainMenu.o openDevice.o closeDevice.o writeDevice.o readDevice.o seekDevice.o ioctlDevice.o
	gcc -o app main.o mainMenu.o openDevice.o closeDevice.o writeDevice.o readDevice.o seekDevice.o ioctlDevice.o

main.o: main.c header.h
	gcc -c main.c

mainMenu.o: mainMenu.c header.h
	gcc -c mainMenu.c

openDevice.o: openDevice.c header.h
	gcc -c openDevice.c

closeDevice.o: closeDevice.c header.h
	gcc -c closeDevice.c

writeDevice.o: writeDevice.c header.h
	gcc -c writeDevice.c

readDevice.o: readDevice.c header.h
	gcc -c readDevice.c

seekDevice.o: seekDevice.c header.h
	gcc -c seekDevice.c

ioctlDevice.o: ioctlDevice.c header.h
	gcc -c ioctlDevice.c
clean:
	rm *.o
	rm app
