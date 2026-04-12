/**
 * @file selection_sort.c
 * @brief Implementacion de selection sort
 */

#include "sorting.h"

void selection_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order)
{
	if(deportistas == NULL || length < 2){
		return;
	}

	for(int i = 0; i < length - 1; i++){
		int selected_index = i;

		for(int j = i + 1; j < length; j++){
			int cmp = compare_by_criteria(deportistas[selected_index], deportistas[j], criteria);
			int should_select = (order == ASCENDING) ? (cmp > 0) : (cmp < 0);

			if(should_select){
				selected_index = j;
			}
		}

		if(selected_index != i){
			swap_deportistas(&deportistas[i], &deportistas[selected_index]);
		}
	}
}