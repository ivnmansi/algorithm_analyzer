/**
 * @file cocktail_shaker.c
 * @brief Desarrollo del algoritmo cocktail shaker sort
 */


#include "sorting.h"
#include "deportista.h"

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

void cocktail_shaker_sort(Deportista* array, int n, SortCriteria criteria, SortOrder order)
{
    if(array == NULL || n < 2){
        return;
    }

    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while(swapped){
        swapped = 0;

        for(int i = left; i < right; i++){
            if(should_swap(array[i], array[i + 1], criteria, order)){
                swap_deportistas(&array[i], &array[i + 1]);
                swapped = 1;
            }
        }

        if(!swapped){
            break;
        }

        right--;
        swapped = 0;

        for(int i = right; i > left; i--){
            if(should_swap(array[i - 1], array[i], criteria, order)){
                swap_deportistas(&array[i - 1], &array[i]);
                swapped = 1;
            }
        }

        left++;
    }
}