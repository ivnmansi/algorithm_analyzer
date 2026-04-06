#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "linked_list.h"

#define CSV_NAME "db/test.csv"

void createDeportistasCSV(LinkedList linkedList);
void loadDeportistasCSV(LinkedList linkedList);


#endif