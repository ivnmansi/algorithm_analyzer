#include "csv.h"
#include "base.h"
#include "generator.h"

void createDeportistasCSV(int cantidadDatos){
    FILE* f = fopen(CSV_ROUTE,"w");
    if(f == NULL){
        printf("No se pudo crear el archivo.\n");
        return;
    }
    fprintf(f, "ID,Nombre,Equipo,Puntaje,Competencias\n");
    for(int i = 0; i < cantidadDatos; i++){
        int id = i;
        char* nombre = generate_random_name();
        char* equipo = generate_random_team();
        float puntaje = generate_random_score();
        int competencias = generate_random_competitions();
        fprintf(f, "%d,%s,%s,%.2f,%d\n", id, nombre, equipo, puntaje, competencias);
        free(nombre);
        free(equipo);
    }

    printf("Archivo CSV creado con éxito.\n");
    fclose(f);
}

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

    FILE* f = fopen(CSV_ROUTE,"r");
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