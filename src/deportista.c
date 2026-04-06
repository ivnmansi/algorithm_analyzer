/**
 * @file deportista.c
 * @brief 
 * 
 */

#include "deportista.h"

Deportista createDeportista(int id, char* nombre, char* equipo, float puntaje, int competencias){
    Deportista newDeportista = malloc(sizeof(Deportista_));
    if(newDeportista == NULL){
        return NULL;
    }
    newDeportista->id = id;
    newDeportista->nombre = nombre;
    newDeportista->equipo = equipo;
    newDeportista->puntaje = puntaje;
    newDeportista->competencias = competencias;

    return newDeportista;
}

void deleteDeportista(Deportista deportista){
    free(deportista->nombre);
    free(deportista->equipo);
    free(deportista);
}