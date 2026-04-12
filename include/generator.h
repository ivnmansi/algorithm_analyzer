/**
    * @file generator.h
    * @brief
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>


char* generate_random_name();
char* generate_random_team();
float generate_random_score();
int generate_random_competitions();

/**
 * @brief Aplica el algoritmo Fisher-Yates sobre un arreglo de enteros.
 *
 * @param values Arreglo a mezclar.
 * @param length Cantidad de elementos del arreglo.
 */
void fisher_yates_shuffle(int *values, int length);

#endif
