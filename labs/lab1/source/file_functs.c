#include "../header/file_functs.h"
#include "../header/functs.h"
#include "../header/data_structs.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


// --------------------------------------- GET DATA NUM ---------------------------------------

int get_master_data_count() {
    FILE* fp = fopen("data/M.ind", "rb");

    if (fp == NULL) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    int ind_row_size = 2 * sizeof(int);
    int rows = ftell(fp) / ind_row_size;
    fclose(fp);

    return rows;
}

int get_slave_data_count() {
    FILE* fp = fopen("data/S.ind", "rb");

    if (fp == NULL) {
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    int ind_row_size = 2 * sizeof(int);
    int rows = ftell(fp) / ind_row_size;
    fclose(fp);

    return rows;
}


// --------------------------------------- GET ---------------------------------------

struct Metro get_master(int id) {
    int data_num = get_master_data_num(id);

    if (data_num == -1)
        return (struct Metro) {-1,"",0,0};

    FILE* fp = fopen("data/M.fl", "rb");

    if (fp == NULL) {
        printf("[ ERROR ] Couldn't open M.fl in [ get master ]!");
        return (struct Metro) { -1, "", 0, 0 };
    }

    struct Metro res;

    fseek(fp, data_num * sizeof(struct Metro), SEEK_SET);
    fread(&res, sizeof(res), 1, fp);

    return res;
}

int get_master_data_num(int id) {
    FILE* fp = fopen("data/M.ind", "rb");

    if (fp == NULL)
        return -1;

    int res, curr_ind;
    bool found = false;

    while (fread(&curr_ind, sizeof(curr_ind), 1, fp) != NULL) {
        if (curr_ind == id) {
            fread(&res, sizeof(res), 1, fp);
            found = true;
            break;
        }

        fseek(fp, sizeof(int), SEEK_CUR);

    }

    if (!found)
        res = -1;

    fclose(fp);
    return res;
}


// --------------------------------------- DELETE ---------------------------------------

void delete_master(int id) {
    int data_num = get_master_data_num(id);

    if (data_num == -1) {
        printf("\nNo element with [ ID ] = %d", id);
        return;
    }


    FILE* fp = fopen("data/M.fl", "rb");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to open [ M.fl ] file in [ delete master ]\n");
        return;
    }

    int rows = get_master_data_count();

    struct Metro* metros = NULL;
    metros = (struct Metro*)malloc((rows - 1) * sizeof(struct Metro));

    for (int i = 0; i < rows - 1; i++) {
        if (i == data_num)
            fseek(fp, sizeof(struct Metro), SEEK_CUR);

        fread(&metros[i], sizeof(metros[0]), 1, fp);
    }

    fclose(fp);

    fp = fopen("data/M.fl", "wb");

    for (int i = 0; i < rows - 1; i++) 
        fwrite(&metros[i], sizeof(metros[0]), 1, fp);

    free(metros);
    fclose(fp);


    struct pair_int_int* locs = NULL;
    locs = (struct pair_int_int*)malloc((rows - 1) * sizeof(struct pair_int_int));

    fp = fopen("data/M.ind", "rb");

    struct pair_int_int curr_loc;

    for (int i = 0; i < rows - 1; i++) {
        fread(&curr_loc, sizeof(curr_loc), 1, fp);

        if (curr_loc.first == id) {
            i--;
            continue;
        }

        if (curr_loc.second > data_num)
            curr_loc.second--;

        locs[i] = curr_loc;
    }

    fclose(fp);

    fp = fopen("data/M.ind", "wb");

    for (int i = 0; i < rows - 1; i++)
        fwrite(&locs[i], sizeof(locs[0]), 1, fp);

    free(locs);
    fclose(fp);

    printf("\nMetro with id = %d was [ deleted ]!", id);
}


// --------------------------------------- UPDATE ---------------------------------------

void update_master(int id) {
    int data_num = get_master_data_num(id);

    if (data_num == -1) {
        printf("\nNo element with [ ID ] = %d", id);
        return;
    }

    printf("\nCurrent metro is:");
    print_metro(get_master(id));

    struct Metro updatedMetro;

    updatedMetro.id = id;

    printf("\nUpdated metro will be:\nMetro [ ID ]: %d\n", id);
    printf("Enter Metro [ NAME ]: ");
    getchar();
    fgets(&updatedMetro.name, sizeof(updatedMetro.name), stdin);
    updatedMetro.name[strcspn(updatedMetro.name, "\n")] = 0;

    printf("Enter Metro [ FOUNDATION YEAR ]: ");
    scanf("%d", &updatedMetro.yFounded);

    printf("Enter Metro [ PASSENGER FLOW ]: ");
    scanf("%d", &updatedMetro.passFlow);



    FILE* fp = fopen("data/M.fl", "rb");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to open [ M.fl ] file in [ update master ]\n");
        return;
    }

    int rows = get_master_data_count();

    struct Metro* metros = NULL;
    metros = (struct Metro*)malloc(rows * sizeof(struct Metro));

    for (int i = 0; i < rows; i++) 
        fread(&metros[i], sizeof(metros[0]), 1, fp);

    fclose(fp);

    metros[data_num] = updatedMetro;

    fp = fopen("data/M.fl", "wb");

    for (int i = 0; i < rows; i++)
        fwrite(&metros[i], sizeof(metros[0]), 1, fp);

    free(metros);
    fclose(fp);

    printf("\nMetro with id = %d was [ updated ]!", id);
}


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

    int rows = get_master_data_count();

    struct pair_int_int pair = { metro.id, rows };

    struct pair_int_int* locs = NULL;
    locs = (struct pair_int_int*)malloc((rows + 1 ) * sizeof(struct pair_int_int));

    struct pair_int_int prev_pair, next_pair;
    int data_num = 0;
    bool pairWritten = false;

    switch (rows)
    {
    case 0:
        locs[0] = pair;
        break;

    case 1:
        fread(&prev_pair, sizeof(prev_pair), 1, fp);

        if (pair.first < prev_pair.first) {
            locs[0] = pair;
            locs[1] = prev_pair;
        }
        else {
            locs[0] = prev_pair;
            locs[1] = pair;
        }
        break;

    default:
        fread(&prev_pair, sizeof(prev_pair), 1, fp);
        fread(&next_pair, sizeof(next_pair), 1, fp);

        if (pair.first < prev_pair.first) {
            locs[0] = pair;
            pairWritten = true;

            data_num = 1;
        }

        do {
            locs[data_num] = prev_pair;

            if (prev_pair.first < pair.first && pair.first < next_pair.first) {
                data_num++;
                locs[data_num] = pair;
                pairWritten = true;
            }

            data_num++;
            prev_pair = next_pair;

        } while (fread(&next_pair, sizeof(next_pair), 1, fp) != NULL);

        locs[data_num] = prev_pair;

        if (!pairWritten)
            locs[data_num + 1] = pair;

        break;
    }

    fclose(fp);

    fp = fopen("data/M.ind", "wb+");

    for (int i = 0; i < rows + 1; i++)
        fwrite(&locs[i], sizeof(locs[0]), 1, fp);

    free(locs);
    locs = NULL;

    fclose(fp);
}


// --------------------------------------- ADD SLAVE ---------------------------------------

void add_slave(int m_id, struct Line line) {

    if (get_master_data_num(m_id) == -1) {
        printf("No metro with [ ID ] = %d to add a slave to!", m_id);
        return;
    }

    add_to_inspector(m_id, line.id, get_slave_data_count());
    add_slave_idx(line);
    add_slave_file(line);
}

void add_to_inspector(int m_id, int s_id, int s_loc) {
    FILE* fp = fopen("data/MS.insp", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ MS.insp ] file.\n");
        return;
    }

    struct triple_int triple = {m_id, s_id, s_loc};

    fwrite(&triple, sizeof(triple), 1, fp);

    fclose(fp);
}

void add_slave_file(struct Line line) {
    FILE* fp = fopen("data/S.fl", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ S.fl ] file.\n");
        return;
    }

    fwrite(&line, sizeof(line), 1, fp);

    fclose(fp);
}

void add_slave_idx(struct Line line) {
    FILE* fp = fopen("data/S.ind", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ S.ind ] file.\n");
        return;
    }

    int rows = get_slave_data_count();

    struct pair_int_int pair = { line.id, rows };

    struct pair_int_int* locs = NULL;
    locs = (struct pair_int_int*)malloc((rows + 1) * sizeof(struct pair_int_int));

    struct pair_int_int prev_pair, next_pair;
    int data_num = 0;
    bool pairWritten = false;

    switch (rows)
    {
    case 0:
        locs[0] = pair;
        break;

    case 1:
        fread(&prev_pair, sizeof(prev_pair), 1, fp);

        if (pair.first < prev_pair.first) {
            locs[0] = pair;
            locs[1] = prev_pair;
        }
        else {
            locs[0] = prev_pair;
            locs[1] = pair;
        }
        break;

    default:
        fread(&prev_pair, sizeof(prev_pair), 1, fp);
        fread(&next_pair, sizeof(next_pair), 1, fp);

        if (pair.first < prev_pair.first) {
            locs[0] = pair;
            pairWritten = true;

            data_num = 1;
        }

        do {
            locs[data_num] = prev_pair;

            if (prev_pair.first < pair.first && pair.first < next_pair.first) {
                data_num++;
                locs[data_num] = pair;
                pairWritten = true;
            }

            data_num++;
            prev_pair = next_pair;

        } while (fread(&next_pair, sizeof(next_pair), 1, fp) != NULL);

        locs[data_num] = prev_pair;

        if (!pairWritten)
            locs[data_num + 1] = pair;

        break;
    }

    fclose(fp);

    fp = fopen("data/S.ind", "wb+");

    for (int i = 0; i < rows + 1; i++)
        fwrite(&locs[i], sizeof(locs[0]), 1, fp);

    free(locs);
    locs = NULL;

    fclose(fp);
}


// --------------------------------------- COUNT ---------------------------------------

void count_master() {
    FILE* fp = fopen("data/M.ind", "ab+");

    if (fp == NULL) {
        printf("[ ERROR ] Unable to create [ M.ind ] file.\n");
        return;
    }

    int rows = get_master_data_count();

    fclose(fp);

    printf("Master file has %d [ records ]!", rows);
}


// --------------------------------------- PRINT ---------------------------------------

void print_master_file() {
    FILE* fp = fopen("data/M.fl", "rb");

    if (fp == NULL) {
        return;
    }

    struct Metro m;
    printf("id | name | foundation year | passenger flow:\n\n");

    while (fread(&m, sizeof(m), 1, fp) != NULL) 
        printf("%d  %s  %d  %d\n", m.id, m.name, m.yFounded, m.passFlow);


    fclose(fp);
}

void print_master_index() {
    FILE* fp = fopen("data/M.ind", "rb");

    if (fp == NULL) {
        return;
    }

    int id, data_num;
    printf("id | data_num:\n\n");

    while (fread(&id, sizeof(id), 1, fp) != NULL && fread(&data_num, sizeof(data_num), 1, fp) != NULL)

        printf("%d  %d\n", id, data_num);

    fclose(fp);
}

void print_slave_file() {
    FILE* fp = fopen("data/S.fl", "rb");

    if (fp == NULL) {
        return;
    }

    struct Line l;
    printf("id | length | number of stations:\n\n");

    while (fread(&l, sizeof(l), 1, fp) != NULL)
        printf("%d  %d  %d\n", l.id, l.length, l.stNum);


    fclose(fp);
}

void print_slave_index() {
    FILE* fp = fopen("data/S.ind", "rb");

    if (fp == NULL) {
        return;
    }

    struct pair_int_int pair;
    printf("id | data_num:\n\n");

    while (fread(&pair, sizeof(pair), 1, fp) != NULL)

        printf("%d  %d\n", pair.first, pair.second);

    fclose(fp);
}

void print_inspector() {
    FILE* fp = fopen("data/MS.insp", "rb");

    if (fp == NULL) {
        return;
    }

    struct triple_int triple;
    printf("m id | s id | s data num:\n\n");

    while (fread(&triple, sizeof(triple), 1, fp) != NULL)

        printf("%d  %d  %d\n", triple.first, triple.second, triple.third);

    fclose(fp);
}


// --------------------------------------- CLEAR ---------------------------------------

void clear_master() {
    FILE* flp = fopen("data/M.fl", "wb+");
    fclose(flp);

    FILE* indp = fopen("data/M.ind", "wb+");
    fclose(indp);

    printf("\nMaster file was CLEARED!\n");

    clear_slave();
    clear_inspector();
}

void clear_slave() {
    FILE* flp = fopen("data/S.fl", "wb+");
    fclose(flp);

    FILE* indp = fopen("data/S.ind", "wb+");
    fclose(indp);

    printf("\nSlave file was CLEARED!\n");

    clear_inspector();
}

void clear_inspector() {
    FILE* flp = fopen("data/MS.insp", "wb+");
    fclose(flp);

    printf("\nInspector file was CLEARED!\n");
}