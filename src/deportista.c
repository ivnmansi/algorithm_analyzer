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
    newDeportista->ID = id;
    newDeportista->Nombre = nombre;
    newDeportista->Equipo = equipo;
    newDeportista->Puntaje = puntaje;
    newDeportista->Competencias = competencias;

    return newDeportista;
}

void deleteDeportista(Deportista deportista){
    free(deportista->Nombre);
    free(deportista->Equipo);
    free(deportista);
}
