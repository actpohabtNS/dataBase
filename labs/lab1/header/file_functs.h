#pragma once

#include "data_structs.h"

void add_master(struct Metro metro);
void add_master_file(struct Metro metro);
void add_master_idx(struct Metro metro);

void print_master();
void print_slave();

void clear_master();
void clear_slave();