/**
 * @file searching.h
 * @brief Busqueda sobre arreglos de deportistas.
 */

#ifndef SEARCHING_H
#define SEARCHING_H

#include "deportista.h"

/**
 * @brief Busqueda secuencial un deportista por ID.
 *
 * @param deportistas Arreglo de deportistas.
 * @param length Cantidad de elementos del arreglo.
 * @param targetId ID a buscar.
 * @return int indice del elemento encontrado o -1 si no existe.
 */
int sequential_search_by_id(Deportista *deportistas, int length, int targetId);

#endif
