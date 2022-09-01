#ifndef SRC_MASTER_LEVELS_H_
#define SRC_MASTER_LEVELS_H_
#include <stdio.h>

typedef struct levels {
  int level;
  int cells;
  int flag;
} levels;

levels read_record_from_file(FILE *pfile, int index);
void write_record_in_file(FILE *pfile, const levels *record_to_write,
                          int index);
void swap_records_in_file(FILE *pfile, int record_index1, int record_index2);
int get_file_size_in_bytes(FILE *pfile);

int get_records_count_in_file(FILE *pfile);
void print_record(levels s, int last);
void print_levels(int a);
void select_levels(int id);

void insert_levels(levels *record);
int id_exists(int id);
void update_levels(levels *record, int id);
void set_protection_flag();
void delete_levels(int id);

#endif  // SRC_MASTER_LEVELS_H_


