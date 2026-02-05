#include "apc.h"

void free_list(Dlist **head)
{
    if(*head == NULL)
        printf("[Info]: List is Empty\n");
        return;
    
    while(*head)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    printf("[Info]: List is Cleared\n");
}