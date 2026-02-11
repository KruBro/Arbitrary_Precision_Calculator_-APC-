#include "apc.h"

void remove_tailing_zeros(Dlist **head)
{
    //If Zero is not only element, remove the zeros;
    while((*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *temp = *head;
        *head = temp->next;
        free(temp);
    }
}
