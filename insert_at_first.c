#include "apc.h"

int insert_at_first(Dlist **head, int data)
{
    // Create new node
    Dlist *new = malloc(sizeof(Dlist));
    if (!new) return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    // If list isn't empty, link old head back to new node
    if (*head != NULL)
    {
        (*head)->prev = new;
    }

    // Move head to point to the new node
    *head = new;

    return SUCCESS;
}
