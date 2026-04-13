/**
 * @file print_format.c
 * @brief Implementacion de utilidades de formato.
 */

#include "print_format.h"

void print_deportistas_array(Deportista *deportistas, int rankingAmount)
{
    if(deportistas == NULL || rankingAmount <= 0) {
        return;
    }

    for(int i = 0; i < rankingAmount; i++) {
        print_deportista(deportistas[i]);
    }
}
