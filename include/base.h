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

#define NAMES_LENGHT_MIN 3
#define NAMES_LENGHT_MAX 8
#define MAX_DATA 100000
#define MIN_DATA 10
#define MAX_SCORE 100.0
#define MIN_SCORE 0.0
#define MAX_COMPETITIONS 45
#define MIN_COMPETITIONS 1
#define CSV_ROUTE "db/deportistas.csv"


void runExperiment();
void search_by_id(int targetId);
void show_ranking(int rankingAmount);
void print_help(const char *programName);



#endif
