#include "apc.h"

int insert_at_last(Dlist **head, Dlist **tail, data_t data)
{
	//Dynamic Memory allocation for new node
	Dlist *new = malloc(sizeof(Dlist));
	if(new == NULL)	return FAILURE; //Safety Check;

	new->data = data;
	new->prev = NULL;
	new->next = NULL;

	//if the list is Empty
	if(!(*head) && !(*tail))
	{
		*head = *tail = new;
		return SUCCESS;
	}
	
	//If not Empty
	(*tail)->next = new; 
	new->prev = *tail;
	*tail = new;
	return SUCCESS;
}