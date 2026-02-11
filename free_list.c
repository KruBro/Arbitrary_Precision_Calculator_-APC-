/*******************************************************************************************************************************************************************
 * File Name     : free_list.c
 * Description   : Function to free all nodes in a doubly linked list
 * Function      : free_list
 * Input Params  : head - Pointer to the head pointer of the list
 * Return Value  : void
 *******************************************************************************************************************************************************************/

#include "apc.h"

void free_list(Dlist **head)
{
    /* Check if the list is empty */
    if (head == NULL || *head == NULL)
    {
        return;
    }
    
    /* Traverse the list and free each node */
    while (*head != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}