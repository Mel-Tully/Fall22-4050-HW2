#include <stdlib.h>
#include <stdio.h>

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

/// @brief Frees the linked_list, including all of its nodes.
/// @param list The list to be freed. 
void free_linked_list(Linked_list_t * list);

/// @brief Inserts the node value at the head of the given linked list.
/// @param list The list to insert the given value into.
/// @param node_value a non-negative integer.
void insert_at_head(Linked_list_t * list, int node_value);