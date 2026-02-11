/*******************************************************************************************************************************************************************
 * File Name     : decimal_utils.c
 * Description   : Utility functions for handling decimal numbers in arithmetic operations
 * Functions     : find_decimal_point, count_decimal_places, pad_decimal_places, 
 *                 remove_leading_zeros, remove_trailing_zeros
 *******************************************************************************************************************************************************************/

#include "apc.h"

/**
 * Find the decimal point node in a list
 */
Dlist* find_decimal_point(Dlist *head)
{
    if (head == NULL)
    {
        return NULL;
    }

    Dlist *temp = head;
    while (temp != NULL)
    {
        if (temp->data == '.')
        {
            return temp;
        }
        temp = temp->next;
    }
    
    return NULL;
}

/**
 * Count the number of decimal places in a number
 */
int count_decimal_places(Dlist *head)
{
    Dlist *decimal_node = find_decimal_point(head);
    
    /* No decimal point found */
    if (decimal_node == NULL)
    {
        return 0;
    }
    
    /* Count digits after decimal point */
    int count = 0;
    Dlist *temp = decimal_node->next;
    
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    
    return count;
}

/**
 * Pad a number with zeros at the end to match decimal places
 */
int pad_decimal_places(Dlist **head, Dlist **tail, int places)
{
    if (head == NULL || tail == NULL || places <= 0)
    {
        return SUCCESS;
    }
    
    /* Add zeros at the end */
    for (int i = 0; i < places; i++)
    {
        if (insert_at_last(head, tail, 0) == FAILURE)
        {
            return FAILURE;
        }
    }
    
    return SUCCESS;
}

/**
 * Remove leading zeros from a number (e.g., 00123 -> 123)
 * Special case: preserve single zero (e.g., 0 or 0.5)
 */
void remove_leading_zeros(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }

    /* Remove leading zeros, but keep at least one digit before decimal */
    while (*head != NULL && (*head)->data == 0)
    {
        /* Stop if this is the last digit before decimal or end */
        if ((*head)->next == NULL || (*head)->next->data == '.')
        {
            break;
        }
        
        Dlist *temp = *head;
        *head = (*head)->next;
        
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
        
        free(temp);
    }
}

/**
 * Remove trailing zeros after decimal point (e.g., 123.4500 -> 123.45)
 * If all decimals are zero, remove the decimal point too (e.g., 123.000 -> 123)
 */
void remove_trailing_zeros(Dlist **tail, Dlist *decimal_pos)
{
    if (tail == NULL || *tail == NULL || decimal_pos == NULL)
    {
        return;
    }

    /* Remove trailing zeros */
    while (*tail != NULL && (*tail)->data == 0 && *tail != decimal_pos)
    {
        Dlist *temp = *tail;
        *tail = (*tail)->prev;
        
        if (*tail != NULL)
        {
            (*tail)->next = NULL;
        }
        
        free(temp);
    }
    
    /* If tail is now the decimal point, remove it too */
    if (*tail == decimal_pos)
    {
        *tail = (*tail)->prev;
        
        if (*tail != NULL)
        {
            (*tail)->next = NULL;
        }
        
        free(decimal_pos);
    }
}