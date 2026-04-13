/**
 * @file generator.h
 * @brief Generadores de datos aleatorios para deportistas.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>

/**
 * @brief Genera un nombre aleatorio en ASCII.
 *
 * @return char* Cadena dinamica con el nombre generado.
 */
char *generate_random_name(void);

/**
 * @brief Genera un equipo aleatorio.
 *
 * @return char* Cadena dinamica con el equipo generado.
 */
char *generate_random_team(void);

/**
 * @brief Genera un puntaje aleatorio dentro del rango permitido.
 *
 * @return float Puntaje generado.
 */
float generate_random_score(void);

/**
 * @brief Genera una cantidad aleatoria de competencias.
 *
 * @return int Cantidad generada.
 */
int generate_random_competitions(void);

/**
 * @brief Aplica el algoritmo Fisher-Yates sobre un arreglo de enteros.
 *
 * @param values Arreglo a mezclar.
 * @param length Cantidad de elementos del arreglo.
 */
void fisher_yates_shuffle(int *values, int length);

#endif
