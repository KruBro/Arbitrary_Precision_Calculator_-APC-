/*******************************************************************************************************************************************************************
 * File Name     : subtraction.c
 * Description   : Function to perform subtraction of two large numbers with decimal support
 * Function      : subtraction
 * Input Params  : head1, tail1 - First operand list (must be larger or equal)
 *                 head2, tail2 - Second operand list (must be smaller or equal)
 *                 headR, tailR - Result list
 * Return Value  : SUCCESS on successful operation, FAILURE otherwise
 * 
 * Algorithm     : 1. Find decimal points and count decimal places in both numbers
 *                 2. Align decimal points by padding zeros
 *                 3. Remove decimal points from both numbers
 *                 4. Perform standard subtraction from right to left with borrow
 *                 5. Insert decimal point in result at appropriate position
 *                 6. Clean up leading/trailing zeros
 *******************************************************************************************************************************************************************/

#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Validate input parameters */
    if (head1 == NULL || tail1 == NULL || head2 == NULL || tail2 == NULL || headR == NULL)
    {
        return FAILURE;
    }

    /* Step 1: Count decimal places in both numbers */
    int decimal1 = count_decimal_places(*head1);
    int decimal2 = count_decimal_places(*head2);
    int max_decimal = (decimal1 > decimal2) ? decimal1 : decimal2;

    /* Step 2: Align decimal places by padding zeros */
    if (decimal1 < decimal2)
    {
        if (pad_decimal_places(head1, tail1, decimal2 - decimal1) == FAILURE)
        {
            return FAILURE;
        }
    }
    else if (decimal2 < decimal1)
    {
        if (pad_decimal_places(head2, tail2, decimal1 - decimal2) == FAILURE)
        {
            return FAILURE;
        }
    }

    /* Step 3: Remove decimal points */
    remove_dot(head1);
    remove_dot(head2);
    
    /* Update tail pointers after removing decimal */
    Dlist *temp = *head1;
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    *tail1 = temp;
    
    temp = *head2;
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    *tail2 = temp;

    /* Step 4: Perform subtraction from right to left */
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;
    int borrow = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int val1 = (t1 != NULL) ? t1->data : 0;
        int val2 = (t2 != NULL) ? t2->data : 0;

        /* Apply borrow from previous digit */
        val1 = val1 - borrow;

        /* Check if we need to borrow */
        if (val1 < val2)
        {
            val1 = val1 + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int result = val1 - val2;

        if (insert_at_first(headR, result) == FAILURE)
        {
            return FAILURE;
        }

        if (t1 != NULL) t1 = t1->prev;
        if (t2 != NULL) t2 = t2->prev;
    }

    /* Step 5: Insert decimal point if needed */
    if (max_decimal > 0)
    {
        /* Find the position to insert decimal from the right */
        Dlist *temp_r = *headR;
        
        /* Move to the end */
        while (temp_r != NULL && temp_r->next != NULL)
        {
            temp_r = temp_r->next;
        }
        
        /* Move back max_decimal positions */
        for (int i = 0; i < max_decimal && temp_r != NULL; i++)
        {
            temp_r = temp_r->prev;
        }
        
        /* Insert decimal point */
        if (temp_r != NULL)
        {
            Dlist *decimal_node = malloc(sizeof(Dlist));
            if (decimal_node == NULL)
            {
                return FAILURE;
            }
            
            decimal_node->data = '.';
            decimal_node->next = temp_r->next;
            decimal_node->prev = temp_r;
            
            if (temp_r->next != NULL)
            {
                temp_r->next->prev = decimal_node;
            }
            temp_r->next = decimal_node;
        }
    }

    /* Update tailR pointer */
    temp = *headR;
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    if (tailR != NULL)
    {
        *tailR = temp;
    }

    /* Step 6: Clean up zeros */
    remove_leading_zeros(headR);
    
    if (max_decimal > 0)
    {
        Dlist *decimal_pos = find_decimal_point(*headR);
        if (tailR != NULL)
        {
            remove_trailing_zeros(tailR, decimal_pos);
        }
    }

    return SUCCESS;
}