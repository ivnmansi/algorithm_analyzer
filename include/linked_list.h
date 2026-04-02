/**
 * @file linked_list.h
 * @brief Lista doblemente enlazada circular
 * 
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>
#include "deportista.h"

typedef struct Node_* Node;

typedef struct Node_ {
    Deportista data;
    Node prev;
    Node next;
} Node_;

typedef struct {
    int num;
    Node firstNode;
} LinkedList_;

typedef LinkedList_* LinkedList;

LinkedList createEmptyList();
void addDeportistaToList(LinkedList linkedList, Deportista deportista);

void moveNode(Node node, Node position);
void deleteNode(Node node);

void deleteList(LinkedList linkedList);

#endif