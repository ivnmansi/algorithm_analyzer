/**
 * @file run_experiment.c
 * @brief Operaciones de ordenamiento, búsqueda y ranking.
 */

#include "base.h"

/**
 * @brief Imprime un deportista.
 *
 * @param deportista Deportista a imprimir.
 */
static void print_deportista(Deportista deportista)
{
    if(deportista == NULL){
        return;
    }

    printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
        deportista->ID,
        deportista->Nombre,
        deportista->Equipo,
        deportista->Puntaje,
        deportista->Competencias);
}

/**
 * @brief Carga el CSV actual en un arreglo.
 *
 * @param deportistas Dirección donde se entrega el arreglo creado.
 * @param count Dirección donde se entrega la cantidad de elementos.
 * @return int 1 si la carga fue exitosa, 0 en caso contrario.
 */
static int load_data(Deportista **deportistas, int *count)
{
    if(deportistas == NULL){
        return 0;
    }

    if(count == NULL){
        return 0;
    }

    *deportistas = loadDeportistasArray(count);
    if(*deportistas == NULL){
        printf("No hay deportistas cargados en el CSV\n");
        return 0;
    }

    if(*count == 0){
        freeDeportistasArray(*deportistas, *count);
        printf("No hay deportistas cargados en el CSV\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Pregunta qué ordenamiento usar.
 *
 * @return int Opción seleccionada.
 */
static int ask_sort_algorithm()
{
    char option[16];

    printf("Seleccione algoritmo de ordenamiento:\n");
    printf("1. Insertion sort\n");
    printf("2. Bubble sort\n");
    printf("3. Selection sort\n");
    printf("4. Cocktail shaker sort\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    return atoi(option);
}

/**
 * @brief Pregunta qué búsqueda usar.
 *
 * @return int Opción seleccionada.
 */
static int ask_search_algorithm()
{
    char option[16];

    printf("Seleccione algoritmo de busqueda:\n");
    printf("1. Busqueda secuencial\n");
    printf("2. Busqueda binaria\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    return atoi(option);
}

/**
 * @brief Pregunta por el campo de ordenamiento.
 *
 * @return int Opción seleccionada.
 */
static int ask_sort_field()
{
    char option[16];

    printf("Seleccione campo de ordenamiento:\n");
    printf("1. ID\n");
    printf("2. Nombre\n");
    printf("3. Equipo\n");
    printf("4. Puntaje\n");
    printf("5. Competencias\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    return atoi(option);
}

/**
 * @brief Ejecuta una operación de ordenamiento o ranking.
 *
 * @param field Campo por el cual se ordena.
 * @param rankingAmount Cantidad de elementos a mostrar.
 * @param descending 1 si el orden es descendente, 0 en caso contrario.
 */
static void run_sort_operation(int field, int rankingAmount, int descending)
{
    Deportista *deportistas;
    int algorithmOption;
    int count, i;

    algorithmOption = ask_sort_algorithm();

    switch(algorithmOption){
        case 1:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            insertion_sort_deportistas(deportistas, count, field, descending);
            if(rankingAmount > count){
                rankingAmount = count;
            }

            for(i = 0; i < rankingAmount; i++){
                if(descending != 0){
                    printf("%d. ", i + 1);
                }
                print_deportista(deportistas[i]);
            }

            freeDeportistasArray(deportistas, count);
            break;
        case 2:
            // Aqui va bubble sort optimizado
            printf("Aun no esta implementado\n");
            break;
        case 3:
            // Aqui va selection sort optimizado
            printf("Aun no esta implementado\n");
            break;
        case 4:
            // Aqui va cocktail shaker sort
            printf("Aun no esta implementado\n");
            break;
        default:
            printf("Error\n");
            break;
    }
}

void runExperiment()
{
    int fieldOption;

    fieldOption = ask_sort_field();

    switch(fieldOption){
        case 1:
            run_sort_operation(fieldOption, MAX_DATA, 0);
            break;
        case 2:
            run_sort_operation(fieldOption, MAX_DATA, 0);
            break;
        case 3:
            run_sort_operation(fieldOption, MAX_DATA, 0);
            break;
        case 4:
            run_sort_operation(fieldOption, MAX_DATA, 0);
            break;
        case 5:
            run_sort_operation(fieldOption, MAX_DATA, 0);
            break;
        default:
            printf("Campo de ordenamiento invalido\n");
            return;
    }
}

/**
 * @brief Busca un deportista por ID e imprime el resultado.
 *
 * @param targetId ID buscado.
 */
void search_by_id(int targetId)
{
    Deportista *deportistas;
    int algorithmOption;
    int count, index;

    algorithmOption = ask_search_algorithm();

    switch(algorithmOption){
        case 1:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            index = sequential_search_by_id(deportistas, count, targetId);
            if(index < 0){
                freeDeportistasArray(deportistas, count);
                printf("No se encontro un deportista con ID %d\n", targetId);
                return;
            }

            print_deportista(deportistas[index]);
            freeDeportistasArray(deportistas, count);
            break;
        case 2:
            // Aqui va Busqueda Binaria
            printf("Aun no esta implementado\n");
            break;
        default:
            printf("Aun no esta implementado\n");
            break;
    }
}

/**
 * @brief Muestra el ranking de los mejores N deportistas según puntaje.
 *
 * @param rankingAmount Cantidad de deportistas a mostrar.
 */
void show_ranking(int rankingAmount)
{
    run_sort_operation(4, rankingAmount, 1);
}

/**
 * @brief Imprime la ayuda de uso del programa.
 *
 * @param programName Nombre del ejecutable.
 */
void print_help(const char *programName)
{
    printf("Uso: %s [opciones]\n", programName);
    printf("  -h                 Muestra esta ayuda\n");
    printf("  -g <cantidad>      Genera datos aleatorios\n");
    printf("  -t                 Ordena deportistas\n");
    printf("  -id <valor>        Busca un deportista por ID\n");
    printf("  -r <cantidad>      Muestra el top N por puntaje\n");
}
