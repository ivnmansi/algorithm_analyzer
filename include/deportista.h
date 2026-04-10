/**
 * @file deportista.h
 * @brief
 *
 */

#ifndef DEPORTISTA_H
#define DEPORTISTA_H

#include <stdlib.h>

typedef struct {
    int ID;
    char* Nombre;
    char* Equipo;
    float Puntaje;
    int Competencias;
} Deportista_;

typedef Deportista_* Deportista;

Deportista createDeportista(int id, char* nombre, char* equipo, float puntaje, int competencias);

void deleteDeportista(Deportista deportista);

#endif