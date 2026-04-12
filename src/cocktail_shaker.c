/**
 * @file cocktail_shaker.c
 * @brief Desarrollo del algoritmo cocktail shaker sort
 */


#include "sorting.h"
#include "deportista.h"


void cocktail_shaker_sort_desc(Deportista* array, int n, SortCriteria criteria){
    if(array == NULL || n < 2){
        return;
    }
    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while(swapped){
        swapped = 0;
        for(int i = left; i < right; i++){
            int shouldSwap = 0;
            switch(criteria) {
                case SORT_BY_PUNTAJE:
                    shouldSwap = array[i]->Puntaje < array[i + 1]->Puntaje;
                    break;
                case SORT_BY_ID:
                    shouldSwap = array[i]->ID < array[i + 1]->ID;
                    break;
                case SORT_BY_COMPETENCIAS:
                    shouldSwap = array[i]->Competencias < array[i + 1]->Competencias;
                    break;
                case SORT_BY_NOMBRE:
                    shouldSwap = strcmp(array[i]->Nombre, array[i + 1]->Nombre) < 0;
                    break;
                case SORT_BY_EQUIPO:
                    shouldSwap = strcmp(array[i]->Equipo, array[i + 1]->Equipo) < 0;
                    break;
                default:
                    break;
            }
            if(shouldSwap) {
                swap_deportistas(&array[i], &array[i + 1]);
                swapped = 1;
            }
        }
        if(!swapped){
            break;
        }

        right--;
        swapped = 0;

        for(int i = right; i > left; i--){
            int shouldSwap = 0;
            switch(criteria) {
                case SORT_BY_PUNTAJE:
                    shouldSwap = array[i - 1]->Puntaje < array[i]->Puntaje;
                    break;
                case SORT_BY_ID:
                    shouldSwap = array[i - 1]->ID < array[i]->ID;
                    break;
                case SORT_BY_COMPETENCIAS:
                    shouldSwap = array[i - 1]->Competencias < array[i]->Competencias;
                    break;
                case SORT_BY_NOMBRE:
                    shouldSwap = strcmp(array[i - 1]->Nombre, array[i]->Nombre) < 0;
                    break;
                case SORT_BY_EQUIPO:
                    shouldSwap = strcmp(array[i - 1]->Equipo, array[i]->Equipo) < 0;
                    break;
                default:
                    break;
            }
            if(shouldSwap) {
                swap_deportistas(&array[i - 1], &array[i]);
                swapped = 1;
            }
        }

        left++;
    }
}