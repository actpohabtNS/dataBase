#include "../header/functs.h"
#include "../header/file_functs.h"

#include <stdio.h>
#include <string.h>



// --------------------------------------- ENTRY ---------------------------------------

void entry() {
	system("cls");

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

	printf("60 - Print (file) master\n");
	printf("61 - Print (file) slave\n\n");

	printf("70 - Print (index) master\n");
	printf("71 - Print inspector\n\n");

	printf("80 - Clear master\n");
	printf("81 - Clear slave\n\n");
	printf("Enter the number: ");

	scanf("%d", &funcNum);

	if (funcNum % 10 > 2 || funcNum > 82 || funcNum < 10) {
		printf("[ ERROR ] WRONG NUMBER. TRY AGAIN.\n\n");
		return chooseFunc();
	}
		

	return funcNum;
}

const char* getFuncStr(int funcNum) {
	char str[30];

	if (funcNum == 71) {
		strcpy(str, "Print inspector");
		return str;
	}

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
		strcpy(str, "Print (file)");
		break;
	case 7:
		strcpy(str, "Print (index)");
		break;
	case 8:
		strcpy(str, "Clear");
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
		print_metro(get_master(get_int_by_string("Enter metro's [ ID ] to [ get ]: ")));
		break;
	case 11:
		print_line(get_slave(get_int_by_string("Enter line's [ ID ] to [ get ]: ")));
		break;
	case 20:
		delete_master(get_int_by_string("Enter metro's [ ID ] to [ delete ]: "));
		break;
	case 21:
		break;
	case 30:
		update_master(get_int_by_string("Enter metro's [ ID ] to [ update ]: "));
		break;
	case 31:
		update_slave(get_int_by_string("Enter line's [ ID ] to [ update ]: "));
		break;
	case 40:
		add_master(getMetroInput());
		break;
	case 41:
		add_slave(get_int_by_string("\nEnter metro's [ ID ] to [ add slave ]: "), getLineInput());
		break;
	case 50:
		count_master();
		break;
	case 51:
		count_slave();
		break;
	case 60:
		print_master_file();
		break;
	case 61:
		print_slave_file();
		break;
	case 70:
		print_master_index();
		break;
	case 71:
		print_inspector();
		break;
	case 80:
		clear_master();
		break;
	case 81:
		clear_slave();
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

	printf("Enter Line [ NUMBER ] in city Metro: ");
	scanf("%d", &l.number);

	printf("Enter Line [ LENGTH ]: ");
	scanf("%d", &l.length);

	printf("Enter Line [ NUMBER OF STATIONS ]: ");
	scanf("%d", &l.stNum);

	return l;
}

int get_int_by_string(char* str) {
	int res;
	printf("%s ", str);
	scanf("%d", &res);
	return res;
}



// --------------------------------------- OUTPUT | METRO, LINE ---------------------------------------

void print_metro(struct Metro metro) {
	if (metro.id == -1)
		printf("\nNo metro with this id!\n");
	else
		printf("\n%d %s %d %d\n", metro.id, metro.name, metro.passFlow, metro.yFounded);
}

void print_line(struct Line line) {
	if (line.id == -1)
		printf("\nNo line with this id!\n");
	else
		printf("\n%d %d %d %d\n", line.id, line.number, line.length, line.stNum);
}