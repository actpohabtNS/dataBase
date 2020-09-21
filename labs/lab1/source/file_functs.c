#include "../header/file_functs.h"
#include "../header/data_structs.h"

#include <stdio.h>
#include <string.h>


// --------------------------------------- ADD MASTER ---------------------------------------

void add_master(struct Metro metro) {
    add_master_file(metro);
    add_master_idx(metro);
}

void add_master_file(struct Metro metro) {
    FILE* fp = fopen("data/M.fl", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ M.fl ] file.\n");
        return;
    }

    fwrite(&metro, sizeof(metro), 1, fp);

    fclose(fp);
}

void add_master_idx(struct Metro metro) {
    FILE* fp = fopen("data/M.ind", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ M.ind ] file.\n");
        return;
    }

    fwrite(&metro.id, sizeof(metro.id), 1, fp);

    fseek(fp, 0, SEEK_END);
    int data_num = ftell(fp) / (sizeof(metro.id) + sizeof(int));

    fwrite(&data_num, sizeof(data_num), 1, fp);

    fclose(fp);
}


// --------------------------------------- PRINT ---------------------------------------

void print_master() {
    FILE* fp = fopen("data/M.fl", "rb");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create file.\n");
        return;
    }

    struct Metro m;
    printf("id | name | foundation year | passenger flow:\n\n");

    while (fread(&m, sizeof(m), 1, fp) != NULL) 
        printf("%d  %s  %d  %d\n", m.id, m.name, m.yFounded, m.passFlow);


    fclose(fp);
}

void print_slave() {
    FILE* fp = fopen("data/M.ind", "rb");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create file.\n");
        return;
    }

    int id, data_num;
    printf("id | data_num:\n\n");

    while (fread(&id, sizeof(id), 1, fp) != NULL && fread(&data_num, sizeof(data_num), 1, fp) != NULL)

        printf("%d  %d\n", id, data_num);

    fclose(fp);
}