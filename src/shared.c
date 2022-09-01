#include <stdio.h>
#include "database.h"



ENTITY *select_m(FILE *db, int id) {
    Modules* module;
    if (db == NULL) {
        printf("n/a");
    } else {
        while (*module.id != id + 1) {
            fread(module, sizeof(Modules), 1, db);
            printf("%d %s %d %d %d",
                           *module.id, *module.name, *module.level, *module.cell, *module.flag_delete);
            printf("\n");
        }
    }
    return module;
}

int delete_m(FILE *db, int id) {
    
}

int insert_m(FILE *db, ENTITY *entity) {
    int res = 1;
    if (db == NULL || entity == NULL){
        printf("n/a");
        res = 0;
    } else {
        fwrite(entity, sizeof(ENTITY), 1, db);
    }
    return 0;
}

int update_m(FILE *db, int id, ENTITY *entity) {
    do {
        fread(module, sizeof(Modules), 1, db);
        printf("%d %s %d %d %d",
               entity->id, entity->name, entity->level,
               entity->cell, entity->flag_delete);
        printf("\n");
    } while (*module.id != id);
    fwrite(entity, sizeof(ENTITY) * id, 1, db);
    printf("%d %s %d %d %d",
           *module.id, *module.name, *module.level,
           *module.cell, *module.flag_delete)
    return 0;
}
