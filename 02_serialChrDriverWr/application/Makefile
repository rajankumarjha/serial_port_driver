myApp:myApp.o writeAppCall.o mainMenu.o
	gcc -o myApp myApp.o mainMenu.o

writeAppCall.o:writeAppCall.c headers.h decleration.h
	gcc -c writeAppCall.c
mainMenu.o:mainMenu.c headers.h decleration.h
	gcc -c mainMenu.c
myApp.o:myApp.c headers.h decleration.h
	gcc -c myApp.c 
clean:
	rm *.o
	rm myApp
