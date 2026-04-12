/**
 * @file insertion_sort.c
 * @brief Implementacion de insertion sort para deportistas.
 */

#include "sorting.h"

/**
 * @brief Funcion que compara dos deportistas según un criterio de ordenamiento.
 *
 * @param left Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @return int Resultado de la comparacion: -1 si left < right, 1 si left > right, 0 si son iguales.
 */
static int compare_deportistas(Deportista left, Deportista right, SortCriteria criteria)
{
    switch(criteria){
        case SORT_BY_ID:
            if(left->ID < right->ID) return -1;
            if(left->ID > right->ID) return 1;
            return 0;

        case SORT_BY_PUNTAJE:
            if(left->Puntaje < right->Puntaje) return -1;
            if(left->Puntaje > right->Puntaje) return 1;
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
 * @brief Funcion que utiliza insertion sort para ordenar un arreglo de deportistas segun un criterio y orden de ordenamiento.
 *
 * @param deportistas Arreglo de deportistas a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Orden de ordenamiento (ascendente o descendente).
 */
void insertion_sort_deportistas(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order)
{
    if(deportistas == NULL || length < 2){
        return;
    }

    for(int i = 1; i < length; i++){
        Deportista key = deportistas[i];
        int j = i - 1;

        while(j >= 0){
            int cmp = compare_deportistas(deportistas[j], key, criteria);

            int should_shift;
            if(order == ASCENDING){
                should_shift = (cmp > 0);
            }
            else {
                should_shift = (cmp < 0);
            }

            if(!should_shift){
                break;
            }

            deportistas[j + 1] = deportistas[j];
            j--;
        }

        deportistas[j + 1] = key;
    }
}
