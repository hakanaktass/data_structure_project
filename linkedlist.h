#ifndef LL_H
#define LL_H

/* Structure for creating
   the linked list
*/
typedef struct _node {
    struct _node *next;
    struct _node *prev;

    int  run_length;
    int data;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;

    int number_of_nodes;
} LinkedList;

void init_linked_list(LinkedList *ll);
void destroy_linked_list(LinkedList *ll);
void append_node(Node *node, LinkedList *ll);

#endif