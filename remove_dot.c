/*******************************************************************************************************************************************************************
 * File Name     : remove_dot.c
 * Description   : Function to remove the decimal point from a linked list representing a number
 * Function      : remove_dot
 * Input Params  : head - Pointer to the head pointer of the list
 * Return Value  : Pointer to the node that was before the decimal point (NULL if not found)
 *******************************************************************************************************************************************************************/

#include "apc.h"

Dlist* remove_dot(Dlist **head)
{
    /* Validate input parameter */
    if (head == NULL || *head == NULL)
    {
        return NULL;
    }

    /* Search for the decimal point */
    Dlist *temp = *head;
    while (temp != NULL && temp->data != '.')
    {
        temp = temp->next;
    }

    /* Return NULL if decimal point not found */
    if (temp == NULL)
    {
        return NULL;
    }
    
    /* Store the previous node to return */
    Dlist *prev_node = temp->prev;
    
    /* Update head if decimal point is at the beginning */
    if (temp == *head)
    {
        *head = temp->next;
    }

    /* Adjust the 'next' pointer of the previous node */
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    /* Adjust the 'prev' pointer of the next node */
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    /* Free the decimal point node */
    free(temp);
    
    return prev_node;
}