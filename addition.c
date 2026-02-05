/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;
    int carry = 0; // MUST initialize carry to 0

    // Loop as long as there are digits or a pending carry
    while (temp1 || temp2 || carry)
    {
        int val1 = (temp1) ? temp1->data : 0;
        int val2 = (temp2) ? temp2->data : 0;

        int sum = val1 + val2 + carry;

        // Calculate new carry and the digit to store
        // If data stores digits 0-9, use sum % 10. 
        // If data stores 0-9999 (4 digits), use sum % 10000.
        carry = sum / 10; 
        int digit_to_store = sum % 10;

        // Insert the result at the front of the result list
        if (insert_at_first(headR, digit_to_store) == FAILURE)
        {
            return FAILURE;
        }

        // Move pointers backwards
        if (temp1) temp1 = temp1->prev;
        if (temp2) temp2 = temp2->prev;
    }

    return SUCCESS;
}

