#include "../header/functs.h"
#include "../header/file_functs.h"

#include <stdio.h>
#include <string.h>



// --------------------------------------- ENTRY ---------------------------------------

void entry() {
	system("cls");

	//struct Metro m1 = { 10, "Hello", 1, 100 };
	//struct Metro m2 = { 15, "world", 1, 100 };

	//add_master(m1);
	//add_master(m2);
	//print_master();

	int funcNum = chooseFunc();

	char funcStr[15] = "";
	strcpy(funcStr, getFuncStr(funcNum));

	system("cls");

	printf("--------------------\n");
	puts(funcStr); 
	printf("--------------------\n\n");

	startFunc(funcNum);
}


// --------------------------------------- USER INPUT | FUNC ---------------------------------------

int chooseFunc() {
	int funcNum;

	printf("Choose [ FUNCTION ] to perform:\n\n");
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

void startFunc(int funcNum) {
	switch (funcNum)
	{
	case 10:
		break;
	case 11:
		break;
	case 20:
		break;
	case 21:
		break;
	case 30:
		break;
	case 31:
		break;
	case 40:
		add_master(getMetroInput());
		break;
	case 41:
		break;
	case 50:
		break;
	case 51:
		break;
	case 60:
		print_master();
		break;
	case 61:
		break;
	default:
		printf("[ ERROR ] NO SUCH FUNC");
		break;
	}

	waitAndGoBack();
}

void waitAndGoBack() {
	printf("\n\n<- GO BACK\n");
	printf("press ENTER to go back\n");
	while (getchar() != '\n'); // option TWO to clean stdin
	getchar();

	entry();
}


// --------------------------------------- USER INPUT | METRO, LINE ---------------------------------------

struct Metro getMetroInput() {
	struct Metro m;

	printf("-----------------------\n");
	printf("ENTER METRO STRUCT\n");
	printf("-----------------------\n\n");

	printf("Enter Metro [ ID ]: ");
	scanf("%d", &m.id);

	printf("Enter Metro [ NAME ]: ");
	getchar();
	fgets(&m.name, sizeof(m.name), stdin);
	m.name[strcspn(m.name, "\n")] = 0;

	printf("Enter Metro [ FOUNDATION YEAR ]: ");
	scanf("%d", &m.yFounded);

	printf("Enter Metro [ PASSENGER FLOW ]: ");
	scanf("%d", &m.passFlow);

	return m;
}

struct Line getLineInput() {
	struct Line l;

	printf("-----------------------\n");
	printf("ENTER LINE STRUCT\n");
	printf("-----------------------\n\n");

	printf("Enter Line [ ID ]: ");
	scanf("%d", &l.id);

	printf("Enter Line [ LENGTH ]: ");
	scanf("%d", &l.length);

	printf("Enter Line [ NUMBER OF STATIONS ]: ");
	scanf("%d", &l.stNum);

	return l;
}