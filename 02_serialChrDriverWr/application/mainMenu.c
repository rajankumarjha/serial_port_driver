#include "headers.h"
#include "decleration.h"

int mainMenu()
{
	int choice;
	printf("Enter Your Choice!\n");
	printf("1. Open Device File!\n");
	printf("2. Close Device File!\n");
	printf("3. Write in Device !\n");
	printf("4. Read Device !\n");
	printf("5. Seek cursor Position !\n");
	printf("6. IOCTL Options !\n");
	printf("0. Exit From Menu!\n");
	scanf("%d",&choice);

	return choice;
}

int chooseOpenReadMode()
{
	int choice;
        printf("Enter Your Choice to Open file mode!\n");
        printf("1. WRITE MODE \"O_WRONLY\"!\n");
        printf("2. READ MODE \"O_RDONLY\"!\n");
        scanf("%d",&choice);

	return choice;
}

int chooseIoctOptions()
{
	int choice;
        printf("Enter Your Choice for Ioctl!\n");
        printf("1.!\n");
        printf("2.!\n");
        printf("3.!\n");
        printf("4.!\n");
        printf("5.!\n");
        printf("6.!\n");
        scanf("%d",&choice);

	return choice;
}
