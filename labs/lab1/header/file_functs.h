#pragma once

#include "data_structs.h"

void add_master(struct Metro metro);
void add_master_file(struct Metro metro);
void add_master_idx(struct Metro metro);

struct Metro get_master(int id);
int get_master_data_num(int id);
struct Line get_slave(int master_id, int slave_id);

void delete_master(int id);
void delete_slave(int id);

void print_master();
void print_slave();

void clear_master();
void clear_slave();