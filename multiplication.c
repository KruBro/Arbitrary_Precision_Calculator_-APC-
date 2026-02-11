/*******************************************************************************************************************************************************************
 * File Name     : multiplication.c
 * Description   : Function to perform multiplication of two large numbers with decimal support
 * Function      : multiplication
 * Input Params  : head1, tail1 - First operand list
 *                 head2, tail2 - Second operand list
 *                 headR, tailR - Result list
 *                 decimal1 - Number of decimal places in first operand
 *                 decimal2 - Number of decimal places in second operand
 * Return Value  : SUCCESS on successful operation, FAILURE otherwise
 * 
 * Algorithm     : 1. Remove decimal points from both numbers
 *                 2. Perform standard multiplication (multiply each digit, add partial products)
 *                 3. Insert decimal point in result (total decimals = decimal1 + decimal2)
 *                 4. Clean up leading/trailing zeros
 *******************************************************************************************************************************************************************/

#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, 
                   Dlist **headR, Dlist **tailR, int decimal1, int decimal2)
{
    /* Validate input parameters */
    if (head1 == NULL || tail1 == NULL || head2 == NULL || tail2 == NULL || headR == NULL)
    {
        return FAILURE;
    }

    /* Step 1: Remove decimal points from both operands */
    remove_dot(head1);
    remove_dot(head2);
    
    /* Update tail pointers */
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

    /* Step 2: Perform multiplication using standard algorithm */
    Dlist *temp2 = *tail2; 
    Dlist *result_head = NULL;
    Dlist *result_tail = NULL;
    int position = 0;

    while (temp2 != NULL)
    {
        Dlist *partial_head = NULL;
        Dlist *partial_tail = NULL;
        
        /* Add positional zeros (for tens, hundreds, etc.) */
        for (int i = 0; i < position; i++) 
        {
            if (insert_at_last(&partial_head, &partial_tail, 0) == FAILURE)
            {
                free_list(&result_head);
                free_list(&partial_head);
                return FAILURE;
            }
        }

        /* Multiply current digit of second number with all digits of first number */
        int carry = 0;
        Dlist *temp1 = *tail1;
        
        while (temp1 != NULL)
        {
            int product = (temp1->data * temp2->data) + carry;
            
            if (insert_at_first(&partial_head, product % 10) == FAILURE)
            {
                free_list(&result_head);
                free_list(&partial_head);
                return FAILURE;
            }
            
            /* Update tail if first insertion */
            if (partial_tail == NULL)
            {
                partial_tail = partial_head;
            }

            carry = product / 10;
            temp1 = temp1->prev;
        }
        
        /* Add remaining carry */
        if (carry > 0) 
        {
            if (insert_at_first(&partial_head, carry) == FAILURE)
            {
                free_list(&result_head);
                free_list(&partial_head);
                return FAILURE;
            }
            
            if (partial_tail == NULL)
            {
                partial_tail = partial_head;
            }
        }

        /* Add partial product to total result */
        Dlist *new_result_head = NULL;
        Dlist *new_result_tail = NULL;
        
        if (addition(&partial_head, &partial_tail, &result_head, &result_tail, 
                    &new_result_head, &new_result_tail) == FAILURE)
        {
            free_list(&result_head);
            free_list(&partial_head);
            return FAILURE;
        }
        
        /* Free old result and partial product lists */
        free_list(&result_head);
        free_list(&partial_head);
        
        /* Update result pointers */
        result_head = new_result_head;
        result_tail = new_result_tail;

        temp2 = temp2->prev;
        position++;
    }
    
    *headR = result_head;
    
    /* Step 3: Insert decimal point if needed */
    int total_decimals = decimal1 + decimal2;
    
    if (total_decimals > 0 && *headR != NULL)
    {
        /* Find position from right to insert decimal */
        Dlist *temp_r = *headR;
        
        /* Move to the end */
        while (temp_r != NULL && temp_r->next != NULL)
        {
            temp_r = temp_r->next;
        }
        
        /* Move back total_decimals positions */
        for (int i = 0; i < total_decimals && temp_r != NULL; i++)
        {
            temp_r = temp_r->prev;
        }
        
        /* Insert decimal point */
        if (temp_r != NULL)
        {
            Dlist *decimal_node = malloc(sizeof(Dlist));
            if (decimal_node == NULL)
            {
                free_list(headR);
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
        else if (total_decimals > 0)
        {
            /* Special case: result is smaller than decimal places (e.g., 0.01 * 0.01 = 0.0001) */
            /* Need to add leading zeros */
            int digits_count = 0;
            Dlist *counter = *headR;
            while (counter != NULL)
            {
                digits_count++;
                counter = counter->next;
            }
            
            int zeros_needed = total_decimals - digits_count;
            
            /* Insert "0." at the beginning */
            if (insert_at_first(headR, '.') == FAILURE)
            {
                free_list(headR);
                return FAILURE;
            }
            
            if (insert_at_first(headR, 0) == FAILURE)
            {
                free_list(headR);
                return FAILURE;
            }
            
            /* Add required zeros after decimal point */
            Dlist *decimal_node = (*headR)->next;
            for (int i = 0; i < zeros_needed; i++)
            {
                Dlist *zero_node = malloc(sizeof(Dlist));
                if (zero_node == NULL)
                {
                    free_list(headR);
                    return FAILURE;
                }
                
                zero_node->data = 0;
                zero_node->next = decimal_node->next;
                zero_node->prev = decimal_node;
                
                if (decimal_node->next != NULL)
                {
                    decimal_node->next->prev = zero_node;
                }
                decimal_node->next = zero_node;
                decimal_node = zero_node;
            }
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

    /* Step 4: Clean up zeros */
    remove_leading_zeros(headR);
    
    if (total_decimals > 0)
    {
        Dlist *decimal_pos = find_decimal_point(*headR);
        if (tailR != NULL)
        {
            remove_trailing_zeros(tailR, decimal_pos);
        }
    }

    return SUCCESS;
}