#include "csv.h"
#include "base.h"
#include "generator.h"
#include "print_format.h"

void createDeportistasCSV(int cantidadDatos){
    int i;
    int isOrdered;
    int *ids;
    FILE* f = fopen(CSV_ROUTE,"w");

    if(f == NULL){
        printf("No se pudo crear el archivo.\n");
        return;
    }

    ids = malloc(sizeof(int) * cantidadDatos);
    if(ids == NULL){
        fclose(f);
        return;
    }

    for(i = 0; i < cantidadDatos; i++){
        ids[i] = i;
    }

    fisher_yates_shuffle(ids, cantidadDatos);
    if(cantidadDatos > 1){
        isOrdered = 1;
        for(i = 0; i < cantidadDatos; i++){
            if(ids[i] != i){
                isOrdered = 0;
                break;
            }
        }

        if(isOrdered == 1){
            fisher_yates_shuffle(ids, cantidadDatos);
        }
    }

    fprintf(f, "ID,Nombre,Equipo,Puntaje,Competencias\n");
    for(i = 0; i < cantidadDatos; i++){
        int id = ids[i];
        char* nombre = generate_random_name();
        char* equipo = generate_random_team();
        float puntaje = generate_random_score();
        int competencias = generate_random_competitions();
        fprintf(f, "%d,%s,%s,%.2f,%d\n", id, nombre, equipo, puntaje, competencias);
        free(nombre);
        free(equipo);
    }

    free(ids);
    printf(BG_GREEN"Archivo CSV creado con éxito.\n"RESET);
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

Deportista* loadDeportistasArray(int *count){
    int capacity;
    FILE* f = fopen(CSV_ROUTE,"r");
    if(f == NULL){
        return NULL;
    }

    if(count == NULL){
        fclose(f);
        return NULL;
    }

    *count = 0;
    capacity = 16;

    Deportista* deportistas = malloc(sizeof(Deportista) * capacity);
    if(deportistas == NULL){
        fclose(f);
        return NULL;
    }

    char line[512];

    if(fgets(line, sizeof(line), f) == NULL){
        fclose(f);
        free(deportistas);
        return NULL;
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

        if(*count == capacity){
            capacity *= 2;
            Deportista* newArray = realloc(deportistas, sizeof(Deportista) * capacity);
            if(newArray == NULL){
                deleteDeportista(deportista);
                freeDeportistasArray(deportistas, *count);
                fclose(f);
                return NULL;
            }
            deportistas = newArray;
        }

        deportistas[*count] = deportista;
        (*count)++;
    }

    fclose(f);
    return deportistas;
}

void freeDeportistasArray(Deportista *deportistas, int count){
    int i;

    if(deportistas == NULL){
        return;
    }

    for(i = 0; i < count; i++){
        deleteDeportista(deportistas[i]);
    }

    free(deportistas);
}


