/*******************************************************************************************************************************************************************
 * File Name     : insert_at_first.c
 * Description   : Function to insert a new node at the beginning of a doubly linked list
 * Function      : insert_at_first
 * Input Params  : head - Pointer to the head pointer of the list
 *                 data - Data to be inserted
 * Return Value  : SUCCESS on successful insertion, FAILURE otherwise
 *******************************************************************************************************************************************************************/

#include "apc.h"

int insert_at_first(Dlist **head, int data)
{
    /* Validate input parameter */
    if (head == NULL)
    {
        return FAILURE;
    }

    /* Allocate memory for new node */
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        fprintf(stderr, "[ERROR]: Memory allocation failed in insert_at_first\n");
        return FAILURE;
    }

    /* Initialize the new node */
    new->data = data;
    new->prev = NULL;
    new->next = *head;

    /* Link the old head to the new node if list is not empty */
    if (*head != NULL)
    {
        (*head)->prev = new;
    }

    /* Update head to point to the new node */
    *head = new;

    return SUCCESS;
}