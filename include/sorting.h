/**
 * @file sorting.h
 * @brief Ordenamiento para deportistas.
 */

#ifndef SORTING_H
#define SORTING_H

#include "deportista.h"
#include <string.h>

/**
 * @brief Criterios disponibles para ordenar deportistas.
 */
typedef enum {
    SORT_BY_ID = 1,
    SORT_BY_PUNTAJE = 2,
    SORT_BY_COMPETENCIAS = 3,
    SORT_BY_NOMBRE = 4,
    SORT_BY_EQUIPO = 5
} SortCriteria;

/**
 * @brief Sentidos de ordenamiento disponibles.
 */
typedef enum {
    DESCENDING = 1,
    ASCENDING = 0
} SortOrder;

/**
 * @brief Algoritmos de ordenamiento disponibles.
 */
typedef enum {
    INSERTION_SORT = 1,
    BUBBLE_SORT = 2,
    SELECTION_SORT = 3,
    COCKTAIL_SHAKER_SORT = 4
} SortAlgorithm;

/**
 * @brief Algoritmos de busqueda disponibles.
 */
typedef enum {
    SEQUENTIAL_SEARCH = 1,
    BINARY_SEARCH = 2
} SearchAlgorithm;

/**
 * @brief Criterios disponibles para la busqueda.
 */
typedef enum {
    SEARCH_BY_ID = 1
} SearchCriteria;

/**
 * @brief Compara dos deportistas segun un criterio.
 *
 * @param left Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio de comparacion.
 * @return int Valor negativo si left < right, positivo si left > right y 0 si son iguales.
 */
int compare_by_criteria(Deportista left, Deportista right, SortCriteria criteria);

/**
 * @brief Ordena un arreglo con cocktail shaker sort.
 *
 * @param deportistas Arreglo a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio de comparacion.
 * @param order Sentido del ordenamiento.
 */
void cocktail_shaker_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order);

/**
 * @brief Ordena un arreglo con insertion sort.
 *
 * @param deportistas Arreglo a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio de comparacion.
 * @param order Sentido del ordenamiento.
 */
void insertion_sort_deportistas(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order);

/**
 * @brief Ordena un arreglo con bubble sort optimizado.
 *
 * @param deportistas Arreglo a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio de comparacion.
 * @param order Sentido del ordenamiento.
 */
void optimized_bubble_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order);

/**
 * @brief Ordena un arreglo con selection sort.
 *
 * @param deportistas Arreglo a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio de comparacion.
 * @param order Sentido del ordenamiento.
 */
void selection_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order);

#endif
