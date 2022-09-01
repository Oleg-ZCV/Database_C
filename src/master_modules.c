#include "master_modules.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for delete

// end
void select_mm(int selected_int) {
  FILE *f = NULL;
  f = fopen("../materials/master_modules.db", "rb");
  struct mm_data data;
  if (selected_int == 0) {
    selected_int = -1;
  }
  while (!feof(f) && selected_int != 0) {
    if (fread(&data, sizeof(struct mm_data), 1, f) > 0) {
      printf("%d %s %d %d %d\n", data.id, data.name, data.level_data,
             data.cell_num, data.del_flag);
      selected_int--;
    }
  }
  fclose(f);
}
void insert_mm(struct mm_data *input_data) {
  FILE *f = NULL;
  struct mm_data data;
  f = fopen("../materials/master_modules.db", "r");
  while (!feof(f)) {
    fread(&data, sizeof(struct mm_data), 1, f);
  }
  fclose(f);
  f = fopen("../materials/master_modules.db", "ab");
  strcpy(data.name, input_data->name);
  data.level_data = input_data->level_data;
  data.cell_num = input_data->cell_num;
  data.id++;
  fwrite(&data, sizeof(struct mm_data), 1, f);
  fclose(f);
}
void delete_mm(int input_id) {
  FILE *f = NULL;
  f = fopen("../materials/master_modules.db", "r+b");
  FILE *f_tmp = NULL;
  f_tmp = fopen("../materials/temp.db", "wb");
  struct mm_data data;
  while (!feof(f)) {
    if (fread(&data, sizeof(struct mm_data), 1, f) > 0) {
      if (input_id != data.id) {
        fwrite(&data, sizeof(struct mm_data), 1, f_tmp);
      }
    }
  }
  fclose(f);
  fclose(f_tmp);
  remove("../materials/master_modules.db");
  rename("../materials/temp.db", "../materials/master_modules.db");
}
void update_mm(struct mm_data *input_data) {
  FILE *f = NULL;
  struct mm_data data;
  f = fopen("../materials/master_modules.db", "r+b");
  FILE *f_tmp = NULL;
  f_tmp = fopen("../materials/temp.db", "wb");
  while (!feof(f)) {
    if (fread(&data, sizeof(struct mm_data), 1, f) > 0) {
      if (input_data->id != data.id) {
        fwrite(&data, sizeof(struct mm_data), 1, f_tmp);
      } else {
        data.cell_num = input_data->cell_num;
        strcpy(data.name, input_data->name);
        data.level_data = input_data->level_data;
        fwrite(&data, sizeof(struct mm_data), 1, f_tmp);
      }
    }
  }
  fclose(f);
  fclose(f_tmp);
  remove("../materials/master_modules.db");
  rename("../materials/temp.db", "../materials/master_modules.db");
}
void update_status_mm() {
  FILE *f = NULL;
  f = fopen("../materials/master_modules.db", "r+b");
  FILE *f_tmp = NULL;
  f_tmp = fopen("../materials/temp.db", "wb");
  struct mm_data data;
  while (!feof(f)) {
    if (fread(&data, sizeof(struct mm_data), 1, f) > 0) {
      if (data.id != 1) {
        data.level_data = 0;
        data.cell_num = 0;
        data.del_flag = 1;
        fwrite(&data, sizeof(struct mm_data), 1, f_tmp);
      } else {
        data.level_data = 1;
        data.cell_num = 1;
        data.del_flag = 0;
      }
    }
  }
  fclose(f);
  fclose(f_tmp);
  remove("../materials/master_modules.db");
  rename("../materials/temp.db", "../materials/master_modules.db");
}

