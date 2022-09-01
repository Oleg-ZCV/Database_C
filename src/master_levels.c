#include "master_levels.h"

levels read_record_from_file(FILE *pfile, int index) {
  int offset = index * sizeof(levels);
  fseek(pfile, offset, SEEK_SET);
  levels record;
  fread(&record, sizeof(levels), 1, pfile);
  rewind(pfile);
  return record;
}

void write_record_in_file(FILE *pfile, const levels *record_to_write,
                          int index) {
  int offset = index * sizeof(levels);
  fseek(pfile, offset, SEEK_SET);
  fwrite(record_to_write, sizeof(levels), 1, pfile);
  fflush(pfile);
  rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2) {
  levels record1 = read_record_from_file(pfile, record_index1);
  levels record2 = read_record_from_file(pfile, record_index2);
  write_record_in_file(pfile, &record1, record_index2);
  write_record_in_file(pfile, &record2, record_index1);
}

int get_file_size_in_bytes(FILE *pfile) {
  int size = 0;
  fseek(pfile, 0, SEEK_END);
  size = ftell(pfile);
  rewind(pfile);
  return size;
}

int get_records_count_in_file(FILE *pfile) {
  return get_file_size_in_bytes(pfile) / sizeof(levels);
}

void print_record(levels s, int last) {
  printf(last ? "%d %d %d" : "%d %d %d\n", s.level, s.cells, s.flag);
}

void print_levels(int a) {
  FILE *fp = fopen("../materials/master_levels.db", "rb");
  int count = get_records_count_in_file(fp);
  int n = a > count || a <= 0 ? count : a;
  for (int i = 0; i < n; i++) {
    levels s = read_record_from_file(fp, i);
    i == n - 1 ? print_record(s, 1) : print_record(s, 0);
  }
}

void select_levels(int id) { print_levels(id); }

void insert_levels(levels *record) {
  FILE *fp = fopen("../materials/master_levels.db", "ab");
  fwrite(record, sizeof(levels), 1, fp);
  fclose(fp);
}

int id_exists(int id) {
  FILE *fp = fopen("../materials/master_levels.db", "rb");
  int n = get_records_count_in_file(fp), res = -1;
  for (int i = 0; i < n && res < 0; ++i) {
    levels l = read_record_from_file(fp, i);
    if (l.level == id) {
      res = i;
    }
  }
  fclose(fp);
  return res;
}

void update_levels(levels *record, int id) {
  FILE *fp = fopen("../materials/master_levels.db", "r+b");
  if (id > 0 && id_exists(id) >= 0) {
    write_record_in_file(fp, record, id_exists(id));
  }
  fclose(fp);
}

void set_protection_flag() {
  FILE *fp = fopen("../materials/master_levels.db", "rb");
  levels record = read_record_from_file(fp, id_exists(1));
  fclose(fp);
  record.flag = 1;
  update_levels(&record, 1);
}

void delete_levels(int id) {
  FILE *fp, *fp_tmp;
  fp = fopen("../materials/master_levels.db", "rb");
  fp_tmp = fopen("tmp.bin", "wb");
  levels read;
  while (fread(&read, sizeof(levels), 1, fp)) {
    if (read.level != id) {
      fwrite(&read, sizeof(levels), 1, fp_tmp);
    }
  }
  fclose(fp);
  fclose(fp_tmp);
  remove("../materials/master_levels.db");
  rename("tmp.bin", "../materials/master_levels.db");
}

