/*******************************************************************************************************************************************************************
 * File Name     : insert_at_last.c
 * Description   : Function to insert a new node at the end of a doubly linked list
 * Function      : insert_at_last
 * Input Params  : head - Pointer to the head pointer of the list
 *                 tail - Pointer to the tail pointer of the list
 *                 data - Data to be inserted
 * Return Value  : SUCCESS on successful insertion, FAILURE otherwise
 *******************************************************************************************************************************************************************/

#include "apc.h"

int insert_at_last(Dlist **head, Dlist **tail, data_t data)
{
    /* Validate input parameters */
    if (head == NULL || tail == NULL)
    {
        return FAILURE;
    }

    /* Allocate memory for new node */
    Dlist *new = malloc(sizeof(Dlist));
    if (new == NULL)
    {
        fprintf(stderr, "[ERROR]: Memory allocation failed in insert_at_last\n");
        return FAILURE;
    }

    /* Initialize the new node */
    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    /* If the list is empty, new node becomes both head and tail */
    if (*head == NULL && *tail == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }
    
    /* Link the new node at the end */
    (*tail)->next = new; 
    new->prev = *tail;
    *tail = new;
    
    return SUCCESS;
}