/**
 * @file run_experiment.c
 * @brief Operaciones de ordenamiento, búsqueda y ranking.
 */

#include "base.h"
#include "csv.h"
#include "sorting.h"

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
static SortAlgorithm ask_sort_algorithm()
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

    SortAlgorithm alg = atoi(option);
    if(alg != INSERTION_SORT && alg != BUBBLE_SORT && alg != SELECTION_SORT && alg != COCKTAIL_SHAKER_SORT){
        return 0;
    }

    return alg;
}

/**
 * @brief Pregunta qué búsqueda usar.
 *
 * @return int Opción seleccionada.
 */
static SearchAlgorithm ask_search_algorithm()
{
    char option[16];

    printf("Seleccione algoritmo de busqueda:\n");
    printf("1. Busqueda secuencial\n");
    printf("2. Busqueda binaria\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    SearchAlgorithm alg = atoi(option);
    if(alg != SECUENTIAL_SEARCH && alg != BINARY_SEARCH){
        return 0;
    }

    return alg;
}



/**
 * @brief Ejecuta una operación de ordenamiento o ranking.
 *
 * @param criteria Campo por el cual se ordena.
 * @param rankingAmount Cantidad de elementos a mostrar.
 * @param descending 1 si el orden es descendente, 0 en caso contrario.
 */
static void run_sort_operation(SortCriteria criteria, int rankingAmount, SortOrder order)
{
    Deportista *deportistas;
    int algorithmOption;
    int count, i;

    algorithmOption = ask_sort_algorithm();

    switch(algorithmOption){
        case INSERTION_SORT: // Insertion sort
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            insertion_sort_deportistas(deportistas, count, criteria, order);
            if(rankingAmount > count){
                rankingAmount = count;
            }

            for(i = 0; i < rankingAmount; i++){
                if(order != 0){
                    printf("%d. ", i + 1);
                }
                print_deportista(deportistas[i]);
            }

            freeDeportistasArray(deportistas, count);
            break;
        case BUBBLE_SORT:
            // Aqui va bubble sort optimizado
            printf("Aun no esta implementado\n");
            break;
        case SELECTION_SORT:
            // Aqui va selection sort optimizado
            printf("Aun no esta implementado\n");
            break;
        case COCKTAIL_SHAKER_SORT:
            // Aqui va cocktail shaker sort
            printf("Aun no esta implementado\n");
            break;
        default:
            printf("Error\n");
            break;
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
    SearchAlgorithm algorithmOption;
    int count, index;

    algorithmOption = ask_search_algorithm();

    switch(algorithmOption){
        case SECUENTIAL_SEARCH:
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
        case BINARY_SEARCH:
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
    printf("  -g [cantidad]      Genera datos aleatorios\n");
    printf("  -t                 Ordena deportistas\n");
    printf("  -id [valor]        Busca un deportista por ID\n");
    printf("  -r [cantidad]      Muestra el top N por puntaje\n");
}

/**
 * @brief Pregunta por el campo de ordenamiento.
 *
 * @return SortCriteria Opción seleccionada.
 */
static SortCriteria ask_sort_criteria()
{
    char option[16];

    printf("Seleccione campo de ordenamiento:\n");
    printf("1. ID\n");
    printf("2. Puntaje\n");
    printf("3. Competencias\n");
    printf("4. Nombre\n");
    printf("5. Equipo\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    SortCriteria criteria = atoi(option);
    if(criteria != SORT_BY_ID && criteria != SORT_BY_PUNTAJE && criteria != SORT_BY_COMPETENCIAS && criteria != SORT_BY_NOMBRE && criteria != SORT_BY_EQUIPO){
        return 0;
    }

    return criteria;
}


/**
 * @brief Funcion que pregunta por el sentido del ordenamiento
 * @return SortOrder Opcion seleccionada
 */
SortOrder ask_sort_order()
{
    char option[16];

    printf("Seleccione orden:\n");
    printf("1. Descendente\n");
    printf("2. Ascendente\n");
    printf("Opcion: ");

    if(fgets(option, sizeof(option), stdin) == NULL){
        return 0;
    }

    SortOrder order = atoi(option);
    if(order != DESCENDING && order != ASCENDING){
        return 0;
    }

    return order;
}

void runExperiment()
{
    SortCriteria criteria = ask_sort_criteria();

    SortOrder order = ask_sort_order();

    switch(criteria){
        case SORT_BY_ID:
            run_sort_operation(criteria, MAX_DATA, order);
            break;
        case SORT_BY_PUNTAJE:
            run_sort_operation(criteria, MAX_DATA, order);
            break;
        case SORT_BY_COMPETENCIAS:
            run_sort_operation(criteria, MAX_DATA, order);
            break;
        case SORT_BY_NOMBRE:
            run_sort_operation(criteria, MAX_DATA, order);
            break;
        case SORT_BY_EQUIPO:
            run_sort_operation(criteria, MAX_DATA, order);
            break;
        default:
            printf("Campo de ordenamiento invalido\n");
            return;
    }
}

/**
    - Cosas por hacer:
        - Implementar Cocktail shaker sort en la ejecucion
        - Implementar los algoritmos de ordenamiento restantes
        - Implementar la búsqueda binaria
        - Agregar validaciones de entrada
 */