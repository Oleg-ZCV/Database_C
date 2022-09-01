#define ENTITY

typedef struct MODULES {
    int id;
    char name[30];
    int level;
    int cell;
    int flag_delete;
} Modules;

typedef struct LEVELS {
    int level;
    int cell;
    int flag_sec;
} Levels;

typedef struct STATUS_EVENTS {
    int id_event;
    int id_module;
    int new_status;
    char date[10+1];
    char time[8+1];
} Status_Events;

//////////////////////////////////////////////////////
ENTITY *select_m(FILE *db, int id);
int delete_m(FILE *db, int id);
int insert_m(FILE *db, ENTITY *entity);
int update_m(FILE *db, int id, ENTITY *entity);
//////////////////////////////////////////////////////
