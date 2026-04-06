#include "csv.h"

void createDeportistasCSV(LinkedList linkedList);

static char* duplicateString(const char* src){
    size_t len = strlen(src);
    char* copy = malloc((len + 1) * sizeof(char));
    if(copy == NULL){
        return NULL;
    }
    memcpy(copy, src, len + 1);
    return copy;
}

void loadDeportistasCSV(LinkedList linkedList){
    if(linkedList == NULL){
        return;
    }

    FILE* f = fopen(CSV_NAME,"r");
    if(f == NULL){
        return;
    }

    char line[512];

    if(fgets(line, sizeof(line), f) == NULL){
        fclose(f);
        return;
    }

    while(fgets(line, sizeof(line), f) != NULL){
        char* token = strtok(line, ",\n\r");
        if(token == NULL){
            continue;
        }
        int id = atoi(token);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            continue;
        }
        char* nombre = duplicateString(token);
        if(nombre == NULL){
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            continue;
        }
        char* equipo = duplicateString(token);
        if(equipo == NULL){
            free(nombre);
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        float puntaje = strtof(token, NULL);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        int competencias = atoi(token);

        Deportista deportista = createDeportista(id, nombre, equipo, puntaje, competencias);
        if(deportista == NULL){
            free(nombre);
            free(equipo);
            continue;
        }

        addDeportistaToList(linkedList, deportista);
    }

    fclose(f);
}