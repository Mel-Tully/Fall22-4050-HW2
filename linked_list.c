#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

void free_linked_list(Linked_list_t * list)
{
    Node_t * new_head;

    while (list->size > 0)
    {
        new_head = list->head->next;
        free(list->head);
        list->head = new_head;
        list->size = list->size - 1;
    }
    
    free(list);
}

void insert_at_head(Linked_list_t * list, int node_value)
{
    Node_t * new_node = malloc(sizeof(Node_t));
    new_node->next = list->head;
    new_node->number = node_value;
    list->head = new_node;
    list->size = list->size + 1;
}