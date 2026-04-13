/**
 * @file base.h
 * @brief
 *
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
#include "searching.h"
#include "sorting.h"
#include "print_format.h"

#define NAMES_LENGHT_MIN 3
#define NAMES_LENGHT_MAX 8
#define MAX_DATA 2147483647
#define MIN_DATA 10
#define MAX_SCORE 100.0
#define MIN_SCORE 0.0
#define MAX_COMPETITIONS 45
#define MIN_COMPETITIONS 1
#define INTERVAL_SIZE 20
#define EXPERIMENT_REPEATS 5
#define CSV_ROUTE "./db/deportistas.csv"
#define SEARCH_BENCHMARK_ROUTE "./db/search_benchmark.csv"
#define SORT_BENCHMARK_ROUTE "./db/sort_benchmark.csv"


void runExperiment();
void run_search_benchmark();
void run_sort_benchmark();
void search_by_id(int targetId);
void show_ranking(int rankingAmount);
void print_help(const char *programName);



#endif
