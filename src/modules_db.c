#include "master_levels.h"
#include "master_modules.h"
#include "master_status_events.h"
#include <stdio.h>

void do_the_task();
void menu(int option);

int main(void) {
  char c;
  int option = 0;
  while (option != -1) {
    option = 0;
    printf("\nPlease choose one operation:\n");
    printf("\t1. SELECT\n\t2. INSERT\n\t3. UPDATE\n\t4. DELETE\n\t-1. EXIT\n");
    printf("> ");
    scanf("%d", &option);
    scanf("%c", &c);
    if (c != '\n') {
      printf("Incorrect input\n");
      option = 0;
      continue;
    } else if (option != 1 && option != 2 && option != 3 && option != 4 &&
               option != -1) {
      printf("Incorrect input\n");
      option = 0;
      continue;
    }
    if (option == -1) {
      break;
    }
    menu(option);
  }
  return 0;
}

void menu(int option) {
  int res = 1;
  printf("/nPlease choose a table:\n");
  printf("\t1. Modules\n\t2. Levels\n\t3. Status events\n");
  int db_type;
  char ch;
  scanf("%d", &db_type);
  scanf("%c", &ch);
  if (ch != '\n') {
    printf("Incorrect input\n");
    res = 0;
  } else if (db_type != 1 && db_type != 2 && db_type != 3) {
    printf("Incorrect input\n");
    res = 0;
  }
  if (res) {
    if (db_type == 1) {  // MODULES - DB
      if (option == 1) { //  SELECT - MODULES
        printf("Insert the number of records or 0 to output all of them: ");
        int select;
        char c;
        scanf("%d", &select);
        scanf("%c", &c);
        if (ch != '\n') {
          printf("Incorrect input\n");
        } else {
          select_mm(select);
        }
      } else if (option == 2) { //  INSERT - MODULES
        printf(
            "Insert a status event: [Module ID] [Module name] [memory level] ");
        printf("[Number of the cell] [Deletion flag]\n");
        int id;
        int level;
        int cell;
        int flag_delete;
        struct mm_data mm;
        scanf("%d %s %d %d %d", &id, mm.name, &level, &cell, &flag_delete);

        mm.id = id;
        mm.level_data = level;
        mm.cell_num = cell;
        mm.del_flag = flag_delete;
        insert_mm(&mm);
      } else if (option == 3) { //  UPDATE - MODULES
        printf(
            "Insert a status event: [Module ID] [Module name] [memory level] ");
        printf("[Number of the cell] [Deletion flag]\n");
        int id;
        int level;
        int cell;
        int flag_delete;
        struct mm_data mm;
        scanf("%d %29s %d %d %d", &id, mm.name, &level, &cell, &flag_delete);
        mm.id = id;
        mm.level_data = level;
        mm.cell_num = cell;
        mm.del_flag = flag_delete;
        update_mm(&mm);
      } else if (option == 4) { //  DELETE - MODULES
        printf("Insert id: [ID] \n");
        int id;
        scanf("%d", &id);
        delete_mm(id);
      }
    } else if (db_type == 2) { // LEVELS - DB
      if (option == 1) {       //  SELECT - LEVELS
        printf("Insert the number of records or 0 to output all of them: ");
        int select;
        char c;
        scanf("%d", &select);
        scanf("%c", &c);
        if (ch != '\n') {
          printf("Incorrect input\n");
        } else {
          select_levels(select);
        }
      } else if (option == 2) { //  INSERT - LEVELS
        printf("Insert a level: [Number of memory level] ");
        printf("[The number of cells on the level] [Protection flag]\n");
        int level;
        int cell;
        int flag_sec;
        scanf("%d %d %d", &level, &cell, &flag_sec);
        levels lvl;
        lvl.level = level;
        lvl.cells = cell;
        lvl.flag = flag_sec;
        insert_levels(&lvl);
      } else if (option == 3) { //  UPDATE - LEVELS
        printf("Insert a level: [Number of memory level] ");
        printf("[The number of cells on the level] [Protection flag]\n");
        int level;
        int cell;
        int flag_sec;
        scanf("%d %d %d", &level, &cell, &flag_sec);
        levels lvl;
        lvl.level = level;
        lvl.cells = cell;
        lvl.flag = flag_sec;
        printf("Insert id: [ID] \n");
        int idd;
        scanf("%d", &idd);
        update_levels(&lvl, idd);
      } else if (option == 4) { //  DELETE - LEVELS
        printf("Insert id: [ID] \n");
        int id;
        scanf("%d", &id);
        delete_levels(id);
      }
    } else if (db_type == 3) { // STATUS EVENTS - DB
      if (option == 1) {       //  SELECT - STATUS EVENTS
        printf("Insert the number of records or 0 to output all of them: ");
        int select;
        char c;
        scanf("%d", &select);
        scanf("%c", &c);
        if (ch != '\n') {
          printf("Incorrect input\n");
        } else {
          select_mse(select);
        }
      } else if (option == 2) { //  INSERT - STATUS EVENTS
        printf("Insert a status event: [Event ID] [Module ID] [New status] ");
        printf("[Change date dd.mm.yyyy] [Change time hh:mm:ss]\n");
        int id_event;
        int id_module;
        int new_status;
        struct statuses st;
        scanf("%d %d %d %29s %29s", &id_event, &id_module, &new_status, st.s1,
              st.s2);

        insert_mse(&st);
      } else if (option == 3) { //  UPDATE - STATUS EVENTS
        printf("Insert a status event: [Event ID] [Module ID] [New status] ");
        printf("[Change date dd.mm.yyyy] [Change time hh:mm:ss]\n");
        int id_event;
        int id_module;
        int new_status;
        struct statuses st;
        scanf("%d %d %d %29s %29s", &id_event, &id_module, &new_status, st.s1,
              st.s2);
        st.event_id = id_event;
        st.module_id = id_module;
        st.new_status = new_status;
        update_mse(&st);
      } else if (option == 4) { //  DELETE - STATUS EVENTS
        printf("Insert id: [ID] \n");
        int id;
        scanf("%d", &id);
        delete_mse(id);
      }
    }
  }
}

void do_the_task() {
    FILE *f;
    f = fopen("../materials/master_status_events.db", "r+b");
    struct statuses data;
    data.event_id = 1;
    while (!feof(f)) {
        fread(&data, sizeof(struct statuses), 1, f);
    }
    int id_last = data.event_id;
    fclose(f);
    int i = 0;
    while (i < id_last) {
        update_status_mse(i, 0);
    }
    update_status_mm();
    update_status_mse(0, 0);
    update_status_mse(0, 1);
    update_status_mse(0, 20);
    set_protection_flag();
}
