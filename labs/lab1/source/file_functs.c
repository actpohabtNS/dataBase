#include "../header/file_functs.h"
#include "../header/data_structs.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


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

    fseek(fp, 0, SEEK_END);
    int ind_row_size = sizeof(metro.id) + sizeof(int);
    int data_loc = ftell(fp) / ind_row_size;
    fseek(fp, 0, SEEK_SET);

    int prev_id = -1, next_id = -1;
    bool insertInside = false;

    switch (data_loc)
    {
    case 0:
        fseek(fp, 0, SEEK_END);
        break;

    case 1:
        fread(&prev_id, sizeof(prev_id), 1, fp);
        if (metro.id < prev_id) {
            fseek(fp, 0, SEEK_SET);
            insertInside = true;
        }
        else
            fseek(fp, 0, SEEK_END);
        break;

    default:
        fread(&prev_id, sizeof(prev_id), 1, fp);
        fseek(fp, sizeof(int), SEEK_CUR);
        fread(&next_id, sizeof(next_id), 1, fp);

        if (metro.id < prev_id) {
            fseek(fp, 0, SEEK_SET);
            insertInside = true;
            break;
        }

        do {
            if (prev_id < metro.id && metro.id < next_id) {
                fseek(fp, -1 * (int)sizeof(next_id), SEEK_CUR);
                insertInside = true;
                break;
            }

            prev_id = next_id;
            fseek(fp, sizeof(int), SEEK_CUR);
        } while (fread(&next_id, sizeof(next_id), 1, fp) != NULL);

        fseek(fp, 0, SEEK_END);
        break;
    }

    if (insertInside) {
        prev_id = metro.id;
        int prev_loc = data_loc, next_loc = -1;

        fread(&next_id, sizeof(next_id), 1, fp);

        printf("%d %d", next_id, next_loc);

        do {
            fread(&next_loc, sizeof(next_loc), 1, fp);
            fseek(fp, -1*(int)ind_row_size, SEEK_CUR);

            printf("%d %d",next_id, next_loc);

            fwrite(&prev_id, sizeof(prev_id), 1, fp);
            fwrite(&prev_loc, sizeof(prev_loc), 1, fp);

            prev_id = next_id;
            prev_loc = next_loc;

            break;
        } while (fread(&next_id, sizeof(next_id), 1, fp) != NULL);

        fwrite(&prev_id, sizeof(prev_id), 1, fp);
        fwrite(&prev_loc, sizeof(prev_loc), 1, fp);
    }
    else {
        fwrite(&metro.id, sizeof(metro.id), 1, fp);
        fwrite(&data_loc, sizeof(data_loc), 1, fp);
    }

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