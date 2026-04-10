#include "base.h"

void runExperiment(){
    LinkedList linkedList = createEmptyList();

    if(linkedList == NULL){
        printf("No se pudo crear la lista.\n");
        return;
    }

    loadDeportistasCSV(linkedList);
    printList(linkedList);
    deleteList(linkedList);
}

