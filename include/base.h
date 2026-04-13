/**
 * @file base.h
 * @brief Constantes globales y prototipos del flujo principal del programa.
 */

#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "csv.h"
#include "errors.h"
#include "searching.h"
#include "sorting.h"
#include "print_format.h"

#define NAME_LENGTH_MIN 3
#define NAME_LENGTH_MAX 8
#define MAX_DATA 2147483647
#define MIN_DATA 10
#define MAX_SCORE 100.0
#define MIN_SCORE 0.0
#define MAX_COMPETITIONS 45
#define MIN_COMPETITIONS 1
#define INTERVAL_SIZE 50
#define EXPERIMENT_REPEATS 5
#define CSV_ROUTE "./db/deportistas.csv"
#define SEARCH_BENCHMARK_ROUTE "./db/search_benchmark.csv"
#define SORT_BENCHMARK_ROUTE "./db/sort_benchmark.csv"


/**
 * @brief Ejecuta el flujo interactivo de ordenamiento.
 */
void run_experiment(void);

/**
 * @brief Ejecuta el benchmark de algoritmos de busqueda.
 */
void run_search_benchmark();

/**
 * @brief Ejecuta el benchmark de algoritmos de ordenamiento.
 */
void run_sort_benchmark();

/**
 * @brief Busca un deportista por su ID.
 *
 * @param targetId ID a buscar.
 */
void search_by_id(int targetId);

/**
 * @brief Muestra el ranking con los mejores deportistas por puntaje.
 *
 * @param rankingAmount Cantidad de deportistas a mostrar.
 */
void show_ranking(int rankingAmount);

/**
 * @brief Imprime la ayuda de uso del programa.
 *
 * @param programName Nombre del ejecutable.
 */
void print_help(const char *programName);

#endif
