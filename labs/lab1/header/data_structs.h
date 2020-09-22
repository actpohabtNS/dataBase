#pragma once

#define NAME_LENGTH 31

struct Metro {
	int id;
	char name[NAME_LENGTH];
	int yFounded;
	int passFlow;
};

struct Line {
	int id;
	int length;
	int stNum;
};