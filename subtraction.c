/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int borrow = 0;

    // Standard school-grade subtraction logic
    while (temp1 || temp2)
    {
        int val1 = (temp1) ? temp1->data : 0;
        int val2 = (temp2) ? temp2->data : 0;

        // Apply any previous borrow
        val1 = val1 - borrow;

        if (val1 < val2)
        {
            val1 = val1 + 10; // "Borrow" 10 to make subtraction positive
            borrow = 1;       // Mark borrow for the next node
        }
        else
        {
            borrow = 0;
        }

        int ret = val1 - val2; // ret will now always be 0-9

        if (insert_at_first(headR, ret) == FAILURE)
            return FAILURE;

        if (temp1) temp1 = temp1->prev;
        if (temp2) temp2 = temp2->prev;
    }

    remove_tailing_zeros(headR);
    return SUCCESS;
}

