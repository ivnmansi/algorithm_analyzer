/**
 * @file insertion_sort.c
 * @brief Implementación de insertion sort para deportistas.
 */

#include "sorting.h"

#include <string.h>

static int compare_deportistas(Deportista left, Deportista right, int field)
{
    if(field == 1){
        return left->ID - right->ID;
    }

    if(field == 2){
        return strcmp(left->Nombre, right->Nombre);
    }

    if(field == 3){
        return strcmp(left->Equipo, right->Equipo);
    }

    if(field == 4){
        if(left->Puntaje < right->Puntaje){
            return -1;
        }

        if(left->Puntaje > right->Puntaje){
            return 1;
        }

        return 0;
    }

    return left->Competencias - right->Competencias;
}

void insertion_sort_deportistas(Deportista *deportistas, int length, int field, int descending)
{
    int i, j;

    if(deportistas == NULL){
        return;
    }

    for(i = 1; i < length; i++){
        Deportista key = deportistas[i];
        j = i - 1;

        while(j >= 0){
            int comparison = compare_deportistas(deportistas[j], key, field);

            if(descending == 0 && comparison <= 0){
                break;
            }

            if(descending != 0 && comparison >= 0){
                break;
            }

            deportistas[j + 1] = deportistas[j];
            j--;
        }

        deportistas[j + 1] = key;
    }
}
