#ifndef SRC_MASTER_STATUS_EVENTS_H_
#define SRC_MASTER_STATUS_EVENTS_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
struct statuses {
    int event_id;
    int module_id;
    int new_status;
    char s1[11];
    char s2[9];
};
 
void select_mse(int n);
 
void insert_mse(struct statuses *stat);
 
void update_mse(struct statuses *stat);
 
void update_status_mse(int id, int status);
 
void delete_mse(int id);
 
#endif  // SRC_MASTER_STATUS_EVENTS_H_
 
