/**
 * @file cocktail_shaker.c
 * @brief Desarrollo del algoritmo cocktail shaker sort
 */


#include "sorting.h"

/**
 * @brief Compara dos deportistas según un criterio de ordenamiento.
 *
 * @param left Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @return int Resultado de la comparacion: -1 si left < right, 1 si left > right, 0 si son iguales.
 */
static int compare_by_criteria(Deportista left, Deportista right, SortCriteria criteria)
{
    switch(criteria){
        case SORT_BY_PUNTAJE:
            if(left->Puntaje < right->Puntaje) return -1;
            if(left->Puntaje > right->Puntaje) return 1;
            return 0;

        case SORT_BY_ID:
            if(left->ID < right->ID) return -1;
            if(left->ID > right->ID) return 1;
            return 0;

        case SORT_BY_COMPETENCIAS:
            if(left->Competencias < right->Competencias) return -1;
            if(left->Competencias > right->Competencias) return 1;
            return 0;

        case SORT_BY_NOMBRE:
            return strcmp(left->Nombre, right->Nombre);

        case SORT_BY_EQUIPO:
            return strcmp(left->Equipo, right->Equipo);

        default:
            return 0;
    }
}

/**
 * @brief Funcion que determina si dos deportistas deben ser intercambiados según el criterio y orden de ordenamiento.
 *
 * @param lef Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Orden de ordenamiento (ascendente o descendente).
 * @return int 1 si se deben intercambiar, 0 en caso contrario.
 */
static int should_swap(Deportista left, Deportista right, SortCriteria criteria, SortOrder order)
{
    int cmp = compare_by_criteria(left, right, criteria);

    if(order == ASCENDING){
        return cmp > 0; // SI left > right, entonces se debe intercambiar
    }

    return cmp < 0; // DESCENDING, Si left < right, entonces se debe intercambiar
}

/**
 * @brief Ordena un arreglo de deportistas utilizando el algoritmo cocktail shaker sort según un criterio y orden de ordenamiento.
 *
 * @param deportistas Arreglo de deportistas a ordenar.
 * @param lenght Largo del arreglo de deportistas.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Sentido de ordenamiento (ascendente o descendente).
 */
void cocktail_shaker_sort(Deportista* deportistas, int lenght, SortCriteria criteria, SortOrder order)
{
    if(deportistas == NULL || lenght < 2){
        return;
    }

    int left = 0;
    int right = lenght - 1;
    int swapped = 1;

    while(swapped){
        swapped = 0;

        for(int i = left; i < right; i++){
            if(should_swap(deportistas[i], deportistas[i + 1], criteria, order)){
                swap_deportistas(&deportistas[i], &deportistas[i + 1]);
                swapped = 1;
            }
        }

        if(!swapped){
            break;
        }

        right--;
        swapped = 0;

        for(int i = right; i > left; i--){
            if(should_swap(deportistas[i - 1], deportistas[i], criteria, order)){
                swap_deportistas(&deportistas[i - 1], &deportistas[i]);
                swapped = 1;
            }
        }

        left++;
    }
}