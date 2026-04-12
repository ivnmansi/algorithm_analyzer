#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "deportista.h"

void createDeportistasCSV(int cantidadDatos);
Deportista* loadDeportistasArray(int *count);
void freeDeportistasArray(Deportista *deportistas, int count);


#endif
