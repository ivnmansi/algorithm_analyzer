/**
 * @file sequential_search.c
 * @brief Implementación de búsqueda secuencial.
 */

#include "searching.h"

int sequential_search_by_id(Deportista *deportistas, int length, int targetId)
{
    int i;

    if(deportistas == NULL){
        return -1;
    }

    for(i = 0; i < length; i++){
        if(deportistas[i] == NULL){
            continue;
        }

        if(deportistas[i]->ID == targetId){
            return i;
        }
    }

    return -1;
}
