/**
 * @file searching.h
 * @brief Busqueda sobre arreglos de deportistas.
 */

#ifndef SEARCHING_H
#define SEARCHING_H

#include "deportista.h"


int sequential_search_by_id(Deportista *deportistas, int length, int targetId);

int binary_search_by_id(Deportista *deportistas, int length, int targetId);

#endif
