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

struct pair_int_int {
	int first;
	int second;
};

struct triple_int {
	int first;
	int second;
	int third;
};