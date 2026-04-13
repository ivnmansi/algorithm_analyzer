/**
 * @file selection_sort.c
 * @brief Implementacion de selection sort para deportistas.
 */

#include "sorting.h"

/**
 * @brief Ordena un arreglo de deportistas usando selection sort.
 *
 * @param deportistas Arreglo de deportistas a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Orden de ordenamiento (ascendente o descendente).
 */
void selection_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order)
{
    if(deportistas == NULL || length < 2) {
        return;
    }

    for(int i = 0; i < length - 1; i++) {
        int selectedIndex = i;

        for(int j = i + 1; j < length; j++) {
            int cmp = compare_by_criteria(deportistas[selectedIndex], deportistas[j], criteria);
            int shouldSelect;

            if(order == ASCENDING) {
                shouldSelect = (cmp > 0);
            } else {
                shouldSelect = (cmp < 0);
            }

            if(shouldSelect) {
                selectedIndex = j;
            }
        }

        if(selectedIndex != i) {
            swap_deportistas(&deportistas[i], &deportistas[selectedIndex]);
        }
    }
}
