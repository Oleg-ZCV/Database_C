#ifndef SRC_MASTER_MODULES_H_
#define SRC_MASTER_MODULES_H_

struct mm_data {
  int id;
  char name[30];
  int level_data;
  int cell_num;
  int del_flag;
};
void select_mm(int selected_int);
void insert_mm(struct mm_data *input_data);
void delete_mm(int input_id);
void update_mm(struct mm_data *input_data);
void update_status_mm();
#endif  // SRC_MASTER_MODULES_H_


