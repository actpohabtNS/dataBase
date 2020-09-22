#pragma once

#include "data_structs.h"

int get_master_data_count();
int get_slave_data_count();

struct Metro get_master(int id);
int get_master_data_num(int id);
struct Line get_slave(int master_id, int slave_id);

void delete_master(int id);
void delete_slave(int id);

void update_master(int id);
void update_slave(int id);

void add_master(struct Metro metro);
void add_master_file(struct Metro metro);
void add_master_idx(struct Metro metro);

void add_to_inspector(int m_id, int s_id, int s_loc);

void add_slave(int m_id, struct Line line);
void add_slave_file(struct Line line);
void add_slave_idx(struct Line line);

void count_master();
void count_slave();

void print_master_file();
void print_master_index();

void print_slave_file();
void print_slave_index();

void print_inspector();

void clear_master();
void clear_slave();
void clear_inspector();