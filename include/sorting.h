/**
 * @file sorting.h
 * @brief Ordenamiento para deportistas.
 */

#ifndef SORTING_H
#define SORTING_H

#include "deportista.h"

/**
 * @brief Ordena un arreglo de deportistas con insertion sort.
 *
 * @param deportistas Arreglo a ordenar.
 * @param length Cantidad de elementos.
 * @param field Campo por el cual se ordena.
 * @param descending 1 para descendente, 0 para ascendente.
 */
void insertion_sort_deportistas(Deportista *deportistas, int length, int field, int descending);

#endif
