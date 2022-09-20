#include <stdlib.h>
#include <stdio.h>


/* Struct Definitions */

typedef struct node
{
    int number;
    struct node *next;
} Node_t;

typedef struct linked_list
{
    int size;
    Node_t * head;
} Linked_list_t;


/* Function Declarations */

/// @brief Creates a new, empty linked list.
/// @return A pointer to an empty list with size of zero and a null head.
Linked_list_t * new_linked_list();

/// @brief Frees the linked_list, including all of its nodes.
/// @param list The list to be freed. 
void free_linked_list(Linked_list_t * list);

/// @brief Inserts the node value at the head of the given linked list.
/// @param list The list to insert the given value into.
/// @param node_value a non-negative integer.
void insert_at_head(Linked_list_t * list, int node_value);


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
