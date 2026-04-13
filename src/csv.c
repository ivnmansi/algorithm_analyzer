/**
 * @file csv.c
 * @brief Implementacion de generacion y carga de datos CSV.
 */

#include "csv.h"
#include "base.h"
#include "generator.h"
#include "print_format.h"

/**
 * @brief Duplica una cadena en memoria dinamica.
 *
 * @param src Cadena de origen.
 * @return char* Copia dinamica de la cadena o NULL si falla la reserva.
 */
static char *duplicate_string(const char *src)
{
    size_t len = strlen(src);
    char *copy = malloc((len + 1) * sizeof(char));

    if(copy == NULL) {
        return NULL;
    }

    memcpy(copy, src, len + 1);
    return copy;
}

/**
 * @brief Genera un CSV con datos aleatorios de deportistas.
 *
 * @param dataAmount Cantidad de registros a crear.
 */
void create_deportistas_csv(int dataAmount)
{
    int i;
    int isOrdered;
    int *ids;
    FILE *file = fopen(CSV_ROUTE, "w");

    if(file == NULL) {
        print_error(ERROR_FILE_CREATE_FAILED, CSV_ROUTE);
        return;
    }

    ids = malloc(sizeof(int) * dataAmount);
    if(ids == NULL) {
        fclose(file);
        print_error(ERROR_MEMORY_ALLOCATION_FAILED, NULL);
        return;
    }

    for(i = 0; i < dataAmount; i++) {
        ids[i] = i;
    }

    fisher_yates_shuffle(ids, dataAmount);

    if(dataAmount > 1) {
        isOrdered = 1;

        for(i = 0; i < dataAmount; i++) {
            if(ids[i] != i) {
                isOrdered = 0;
                break;
            }
        }

        if(isOrdered == 1) {
            fisher_yates_shuffle(ids, dataAmount);
        }
    }

    fprintf(file, "ID,Nombre,Equipo,Puntaje,Competencias\n");

    for(i = 0; i < dataAmount; i++) {
        int id = ids[i];
        char *nombre = generate_random_name();
        char *equipo = generate_random_team();
        float puntaje = generate_random_score();
        int competencias = generate_random_competitions();

        if(nombre == NULL || equipo == NULL) {
            free(nombre);
            free(equipo);
            free(ids);
            fclose(file);
            print_error(ERROR_MEMORY_ALLOCATION_FAILED, NULL);
            return;
        }

        fprintf(file, "%d,%s,%s,%.2f,%d\n", id, nombre, equipo, puntaje, competencias);
        free(nombre);
        free(equipo);
    }

    free(ids);
    fclose(file);
    printf(BG_GREEN "Archivo CSV creado con exito.\n" RESET);
}

/**
 * @brief Carga en memoria el contenido del CSV de deportistas.
 *
 * @param count Direccion donde se guarda la cantidad cargada.
 * @return Deportista* Arreglo dinamico o NULL si falla la carga.
 */
Deportista *load_deportistas_array(int *count)
{
    int capacity;
    FILE *file = fopen(CSV_ROUTE, "r");
    Deportista *deportistas;
    char line[512];

    if(file == NULL) {
        return NULL;
    }

    if(count == NULL) {
        fclose(file);
        return NULL;
    }

    *count = 0;
    capacity = 16;

    deportistas = malloc(sizeof(Deportista) * capacity);
    if(deportistas == NULL) {
        fclose(file);
        return NULL;
    }

    if(fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        free(deportistas);
        return NULL;
    }

    while(fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",\n\r");

        if(token == NULL) {
            continue;
        }

        int id = atoi(token);

        token = strtok(NULL, ",\n\r");
        if(token == NULL) {
            continue;
        }

        char *nombre = duplicate_string(token);
        if(nombre == NULL) {
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL) {
            free(nombre);
            continue;
        }

        char *equipo = duplicate_string(token);
        if(equipo == NULL) {
            free(nombre);
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL) {
            free(nombre);
            free(equipo);
            continue;
        }

        float puntaje = strtof(token, NULL);

        token = strtok(NULL, ",\n\r");
        if(token == NULL) {
            free(nombre);
            free(equipo);
            continue;
        }

        int competencias = atoi(token);
        Deportista deportista = create_deportista(id, nombre, equipo, puntaje, competencias);

        if(deportista == NULL) {
            free(nombre);
            free(equipo);
            continue;
        }

        if(*count == capacity) {
            Deportista *newArray;

            capacity *= 2;
            newArray = realloc(deportistas, sizeof(Deportista) * capacity);
            if(newArray == NULL) {
                delete_deportista(deportista);
                free_deportistas_array(deportistas, *count);
                fclose(file);
                return NULL;
            }

            deportistas = newArray;
        }

        deportistas[*count] = deportista;
        (*count)++;
    }

    fclose(file);
    return deportistas;
}

/**
 * @brief Libera un arreglo dinamico de deportistas.
 *
 * @param deportistas Arreglo a liberar.
 * @param count Cantidad de elementos.
 */
void free_deportistas_array(Deportista *deportistas, int count)
{
    int i;

    if(deportistas == NULL) {
        return;
    }

    for(i = 0; i < count; i++) {
        delete_deportista(deportistas[i]);
    }

    free(deportistas);
}
