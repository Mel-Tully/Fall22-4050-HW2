#include "linked_list.h"

/* Function Definitions */

Linked_list_t * new_linked_list()
{
    Linked_list_t * input = malloc(sizeof(Linked_list_t));
    input->head = NULL;
    input->size = 0;
    return input;
}

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

int * list_to_array(Linked_list_t * input)
{
    int * arr = malloc((size_t)(input->size * sizeof(int)));
    Node_t * current_node = input->head;
    for (size_t i = 0; i < input->size; i++)
    {
        arr[i] = current_node->number;
        current_node = current_node->next;
    }

    return arr;
}