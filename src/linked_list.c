/**
 * @file linked_list.c
 * @brief 
 * 
 */
#include "linked_list.h"

/**
 * @brief Crea una lista doblemente enlazada circular
 * 
 * @return LinkedList 
 */
LinkedList createEmptyList(){
    LinkedList newLinkedList = malloc(sizeof(LinkedList_));
    if(newLinkedList == NULL){
        return NULL;
    }
    newLinkedList->num = 0;
    newLinkedList->firstNode = NULL;
    
    return newLinkedList;
}

/**
 * @brief Añade un deportista a la lista enlazada (al final de la lista)
 * 
 * @param linkedList 
 * @param deportista 
 */
void addDeportistaToList(LinkedList linkedList, Deportista deportista){
    if(linkedList == NULL){
        return;
    }

    Node newNode = malloc(sizeof(Node_));
    if(newNode == NULL){
        return;
    }
    newNode->data = deportista;
    
    if(linkedList->num == 0){
        newNode->next = newNode;
        newNode->prev = newNode;
        linkedList->firstNode = newNode;
    }
    else {
        linkedList->firstNode->prev->next = newNode;
        newNode->prev = linkedList->firstNode->prev;
        newNode->next = linkedList->firstNode;
        linkedList->firstNode->prev = newNode;
    }
    linkedList->num++;
}

/**
 * @brief Mueve un nodo a la posición dada
 * 
 * @param node 
 * @param position 
 */
void moveNode(Node node, Node position){
    if(node == NULL || position == NULL){
        return;
    }

    if(node == position || node->prev == position){
        return;
    }

    Node nodePrev = node->prev;
    Node nodeNext = node->next;
    Node positionNext = position->next;

    nodePrev->next = nodeNext;
    nodeNext->prev = nodePrev;

    position->next = node;
    node->prev = position;
    node->next = positionNext;
    positionNext->prev = node;
}

/**
 * @brief Elimina un nodo de una lista
 * 
 * @param node 
 */
void deleteNode(Node node){
    if(node == NULL){
        return;
    }
    Node prevNode = node->prev;
    prevNode->next = node->next;
    node->next->prev = prevNode;
    free(node->data);
    free(node);
}

/**
 * @brief Libera lista enlazada
 * 
 * @param linkedList 
 */
void deleteList(LinkedList linkedList){
    if(linkedList == NULL){
        return;
    }

    if(linkedList->firstNode == NULL){
        free(linkedList);
        return;
    }

    Node firstNode = linkedList->firstNode;
    Node currentNode = firstNode->next;

    while(currentNode != firstNode){
        Node nodeToDelete = currentNode;
        currentNode = currentNode->next;
        free(nodeToDelete->data);
        free(nodeToDelete);
    }

    free(firstNode->data);
    free(firstNode);

    free(linkedList);
}
