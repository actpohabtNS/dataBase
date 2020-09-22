#pragma once

void entry();

int chooseFunc();
const char* getFuncStr(int funcNum);
void startFunc(int funcNum);
void waitAndGoBack();

struct Metro getMetroInput();
struct Line getLineInput();

int get_int_by_string(char* str);

void printMetro(struct Metro metro);