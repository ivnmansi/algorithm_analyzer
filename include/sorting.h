/**
 * @file sorting.h
 * @brief Ordenamiento para deportistas.
 */

#ifndef SORTING_H
#define SORTING_H
#include "deportista.h"
#include <string.h>

typedef enum {
    SORT_BY_ID = 1,
    SORT_BY_PUNTAJE = 2,
    SORT_BY_COMPETENCIAS = 3,
    SORT_BY_NOMBRE = 4,
    SORT_BY_EQUIPO = 5
} SortCriteria;

typedef enum {
    DESCENDING = 1,
    ASCENDING = 0
} SortOrder;

typedef enum {
    INSERTION_SORT = 1,
    BUBBLE_SORT = 2,
    SELECTION_SORT = 3,
    COCKTAIL_SHAKER_SORT = 4
} SortAlgorithm;

typedef enum {
    SECUENTIAL_SEARCH = 1,
    BINARY_SEARCH = 2
} SearchAlgorithm;

typedef enum {
    SEARCH_BY_ID = 1
} SearchCriteria;


void cocktail_shaker_sort(Deportista* deportistas, int lenght, SortCriteria criteria, SortOrder order);

void insertion_sort_deportistas(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order);

#endif
