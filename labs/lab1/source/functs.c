#include <stdio.h>
#include <string.h>
#include "../header/functs.h"

void entry() {
	system("cls");
	
	int fileNum = chooseFile();

	char fileStr[15] = "";
	strcpy(fileStr, getFileStr(fileNum));

	system("cls");

	printf("Chosen file: ");
	puts(fileStr); 
	printf("\n");


}

const char* getFileStr(int fileNum) {
	char str[15];

	switch (fileNum) {
	case 1:
		strcpy(str, "Metros");
		break;
	case 2:
		strcpy(str, "Lines");
		break;
	case 3:
		strcpy(str, "Stations");
		break;
	case 4:
		strcpy(str, "Depos");
		break;
	case 5:
		strcpy(str, "Trains");
		break;
	case 6:
		strcpy(str, "Rail sector");
		break;
	default:
		strcpy(str, "NO SUCH FILE");
		break;
	}

	return str;
}

int chooseFile() {
	int fileNum;

	printf("Choose [ FILE ] to work with.\n");
	printf("1 - Metros\n");
	printf("2 - Lines\n");
	printf("3 - Stations\n");
	printf("4 - Depos\n");
	printf("5 - Trains\n");
	printf("6 - Rail sector\n\n");
	printf("Enter the number 1 - 6: ");

	scanf("%d", &fileNum);

	fileNum %= 10;

	return fileNum;
}

int chooseFunc() {
	int funcNum;

	printf("Choose [ OPTION ] to do.\n");
	printf("1 - Get\n");
	printf("2 - Delete\n");
	printf("3 - Update\n");
	printf("4 - Add\n");
	printf("5 - Count\n");
	printf("6 - Back <-\n\n");
	printf("Enter the number 1 - 6: ");

	scanf("%d", &funcNum);

	funcNum %= 10;

	return funcNum;
}