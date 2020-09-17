#include <stdio.h>
#include <string.h>
#include "../header/functs.h"

void entry() {
	system("cls");
	
	int funcNum = chooseFunc();

	char funcStr[15] = "";
	strcpy(funcStr, getFuncStr(funcNum));

	system("cls");

	printf("--------------------\n");
	puts(funcStr); 
	printf("--------------------\n\n");

}

int chooseFunc() {
	int funcNum;

	printf("Choose [ FUNTION ] to perform:\n\n");
	printf("10 - Get master\n");
	printf("11 - Get slave\n\n");
	printf("20 - Delete master\n");
	printf("21 - Delete slave\n\n");
	printf("30 - Update master\n");
	printf("31 - Update slave\n\n");
	printf("40 - Add master\n");
	printf("41 - Add slave\n\n");
	printf("50 - Count master\n");
	printf("51 - Count slave\n\n");
	printf("60 - Print master\n");
	printf("61 - Print slave\n\n");
	printf("Enter the number: ");

	scanf("%d", &funcNum);

	if (funcNum % 10 > 2 || funcNum > 62 || funcNum < 10) {
		printf("[ ERROR ] WRONG NUMBER. TRY AGAIN.\n\n");
		return chooseFunc();
	}
		

	return funcNum;
}

const char* getFuncStr(int funcNum) {
	char str[15];

	switch (funcNum / 10) {
	case 1:
		strcpy(str, "Get");
		break;
	case 2:
		strcpy(str, "Delete");
		break;
	case 3:
		strcpy(str, "Update");
		break;
	case 4:
		strcpy(str, "Add");
		break;
	case 5:
		strcpy(str, "Count");
		break;
	case 6:
		strcpy(str, "Print");
		break;
	default:
		strcpy(str, "NO SUCH FUNC");
		return str;
	}

	switch (funcNum % 10) {
	case 0:
		strcat(str, " master");
		break;
	case 1:
		strcat(str, " slave");
		break;
	default:
		strcat(str, " NO SUCH RELATIONSHIP");
		break;
	}

	return str;
}