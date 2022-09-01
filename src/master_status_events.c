#include "database.h"
#include "master_status_events.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
void select_mse(int n) {
    FILE *f = NULL;
    int i = 0;
    f = fopen("../materials/master_status_events.db", "rb");
    struct statuses data;
    if (n == 0) {
        while (!feof(f)) {
            if (fread(&data, sizeof(struct statuses), 1, f) > 0) {
                printf("%d %d %d %s %s\n", data.event_id, data.module_id, data.new_status, data.s1, data.s2);
            }
            i++;
        }
    } else {
        while (!feof(f) && i < n) {
            if (fread(&data, sizeof(struct statuses), 1, f) > 0) {
                printf("%d %d %d %29s %29s\n", data.event_id, data.module_id, data.new_status, data.s1, data.s2);
            }
            i++;
        }
    }
}
 
void insert_mse(struct statuses *stat) {
    FILE *f = NULL;
    f = fopen("../materials/master_status_events.db", "rb");
    struct statuses data;
    while (!feof(f)) {
        fread(&data, sizeof(struct statuses), 1, f);
    }
    data.event_id = 1;
    int id_last = data.event_id;
    fclose(f);
    f = fopen("../materials/master_status_events.db", "ab");
    struct statuses data2;
    data2.event_id = id_last + 1;
    data2.module_id = stat->module_id;
    data2.new_status = stat->module_id;
    time_t t = time(NULL);
    struct tm *p = localtime(&t);
    strftime(data2.s1, 11, "%d.%m.%Y", p);
    strftime(data2.s2, 9, "%H:%M:%S", p);
    fwrite(&data2, sizeof(struct statuses), 1, f);
    fclose(f);
}
 
void update_mse(struct statuses *stat) {
    FILE *f = NULL;
    FILE *f_temp = NULL;
    f = fopen("../materials/master_status_events.db", "r+b");
    f_temp = fopen("../materials/temp.db", "w+b");
    rewind(f);
    struct statuses data;
    while (!feof(f)) {
        if (fread(&data, sizeof(struct statuses), 1, f) > 0) {
            if (data.event_id != stat->event_id) {
                fwrite(&data, sizeof(struct statuses), 1, f_temp);
            } else {
                data.module_id = stat->module_id;
                data.new_status = stat->new_status;
                time_t t = time(NULL);
                struct tm *p = localtime(&t);
                strftime(data.s1, 11, "%d.%m.%Y", p);
                strftime(data.s2, 9, "%H:%M:%S", p);
                fwrite(&data, sizeof(struct statuses), 1, f_temp);
            }
        }
    }
    fclose(f);
    fclose(f_temp);
    remove("../materials/master_status_events.db");
    rename("../materials/temp.db", "../materials/master_status_events.db");
}
 
void update_status_mse(int id, int status) {
    FILE *f = NULL;
    FILE *f_temp = NULL;
    f = fopen("../materials/master_status_events.db", "r+b");
    f_temp = fopen("../materials/temp.db", "w+b");
    rewind(f);
    struct statuses data;
    while (!feof(f)) {
        if (fread(&data, sizeof(struct statuses), 1, f) > 0) {
            if (data.event_id != id) {
                fwrite(&data, sizeof(struct statuses), 1, f_temp);
            } else {
                data.new_status = status;
                time_t t = time(NULL);
                struct tm *p = localtime(&t);
                strftime(data.s1, 11, "%d.%m.%Y", p);
                strftime(data.s2, 9, "%H:%M:%S", p);
                fwrite(&data, sizeof(struct statuses), 1, f_temp);
            }
        }
    }
    fclose(f);
    fclose(f_temp);
    remove("../materials/master_status_events.db");
    rename("../materials/temp.db", "../materials/master_status_events.db");
}
 
void delete_mse(int id) {
    FILE *f = NULL;
    FILE *f_temp = NULL;
    f = fopen("../materials/master_status_events.db", "r+b");
    f_temp = fopen("../materials/temp.db", "w+b");
    rewind(f);
    struct statuses data;
    while (!feof(f)) {
        if (fread(&data, sizeof(struct statuses), 1, f) > 0) {
            if (data.event_id != id) {
                fwrite(&data, sizeof(struct statuses), 1, f_temp);
            }
        }
    }
    fclose(f);
    fclose(f_temp);
    remove("../materials/master_status_events.db");
    rename("../materials/temp.db", "../materials/master_status_events.db");
}
 
 
