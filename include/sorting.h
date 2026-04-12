/**
 * @file sorting.h
 * @brief Ordenamiento para deportistas.
 */

#ifndef SORTING_H
#define SORTING_H
#include "deportista.h"
#include <string.h>

typedef enum {
    SORT_BY_ID,
    SORT_BY_PUNTAJE,
    SORT_BY_COMPETENCIAS,
    SORT_BY_NOMBRE,
} SortCriteria;

void cocktail_shaker_sort_desc(Deportista* array, int n, SortCriteria criteria);

void swap_deportistas(Deportista* a, Deportista* b);

void insertion_sort_deportistas(Deportista *deportistas, int length, int field, int descending);

#endif
