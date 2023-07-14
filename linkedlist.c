#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pgm.h"
#include "linkedlist.h"


void init_linked_list(LinkedList *ll) {
    ll->head = malloc(sizeof(Node));
    ll->tail = malloc(sizeof(Node));

    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    ll->tail->next = NULL;
    
    ll->number_of_nodes = 2;
}

void destroy_linked_list(LinkedList *ll) {
    Node *ptr = ll->head;

    while (ptr) {
        Node *tmp = ptr->next; 
        free(ptr);
        ptr = tmp;
    }
}

void append_node(Node *node, LinkedList *ll) {
    Node *temp = ll->head;

    while (temp->next != ll->tail)
        temp = temp->next;

    temp->next = node;
    node->next = ll->tail;

    ll->number_of_nodes++;
}