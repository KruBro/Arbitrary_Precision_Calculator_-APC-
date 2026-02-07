/*******************************************************************************************************************************************************************
*Title          : Multiplication
*Description    : This function performs multiplication of two given large numbers and store the result in the resultant list.
*******************************************************************************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *temp2 = *tail2; 
    Dlist *resHead = NULL, *resTail = NULL; // To store accumulated sum
    int count = 0;

    while (temp2)
    {
        Dlist *stepHead = NULL, *stepTail = NULL;
        
        // Step 1: Add padding zeros (for tens, hundreds place, etc.)
        for (int i = 0; i < count; i++) 
            insert_at_last(&stepHead, &stepTail, 0);

        int carry = 0;
        Dlist *temp1 = *tail1;
        
        // Step 2: Multiply current digit of Op2 with entire Op1
        while (temp1)
        {
            int prod = (temp1->data * temp2->data) + carry;
            insert_at_first(&stepHead, prod % 10);
            
            //If stepTail is NULL (first digit inserted), point it to head
            if (stepTail == NULL)
                stepTail = stepHead;

            carry = prod / 10;
            temp1 = temp1->prev;
        }
        
        if (carry) 
        {
            insert_at_first(&stepHead, carry);
            // [Safety] Ensure tail is set if carry was the only digit inserted
            if (stepTail == NULL) stepTail = stepHead;
        }

        // Step 3: Add the step result to the total result
        Dlist *newResHead = NULL;
        
        // Perform addition: resHead + stepHead -> newResHead
        addition(&stepHead, &stepTail, &resHead, &resTail, &newResHead);
        
        // [CLEANUP 1] Free the old accumulator list because 'addition' created a fresh list
        if (resHead != NULL)
        {
            free_list(&resHead);
        }

        // Update the accumulators to point to the new result
        resHead = newResHead;
        
        //Manually find the new tail, because addition() didn't return it
        if (resHead)
        {
            Dlist *temp = resHead;
            while (temp->next)
                temp = temp->next;
            resTail = temp;
        }
        else
        {
            resTail = NULL;
        }

        // [CLEANUP 2] Free the partial product list (stepList) as requested
        free_list(&stepHead);

        temp2 = temp2->prev;
        count++;
    }
    
    *headR = resHead;
    return SUCCESS;
}