/**
 * @file deportista.h
 * @brief 
 * 
 */

#ifndef DEPORTISTA_H
#define DEPORTISTA_H

typedef struct {
    int id;
    char* nombre;
    char* equipo;
    float puntaje;
    int competencias;
} Deportista_;

typedef Deportista_* Deportista;

#endif