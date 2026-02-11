/*******************************************************************************************************************************************************************
 * File Name     : compare.c
 * Description   : Function to compare two numbers based on their absolute values
 * Function      : compare
 * Input Params  : len1 - Number of digits in first number (excluding decimal)
 *                 len2 - Number of digits in second number (excluding decimal)
 *                 head1 - Pointer to the head of first list
 *                 head2 - Pointer to the head of second list
 * Return Value  : FIRST_LARGER if num1 > num2
 *                 SECOND_LARGER if num1 < num2
 *                 NUMBERS_EQUAL if num1 == num2
 *******************************************************************************************************************************************************************/

#include "apc.h"

ComparisonResult compare(int len1, int len2, Dlist *head1, Dlist *head2)
{
    /* First compare lengths - longer number is always larger */
    if (len1 > len2)
    {
        return FIRST_LARGER;
    }
    
    if (len1 < len2)
    {
        return SECOND_LARGER;
    }

    /* If lengths are equal, compare digit by digit from left to right */
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
        {
            return FIRST_LARGER;
        }
        
        if (head1->data < head2->data)
        {
            return SECOND_LARGER;
        }

        head1 = head1->next;
        head2 = head2->next;
    }

    /* Both numbers are equal */
    return NUMBERS_EQUAL;
}