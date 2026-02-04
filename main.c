/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
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

void print_list(Dlist *head, Dlist *tail)
{
	if(head == NULL)
		printf("[INFO]: List is Empty\n");
	else
	{
		while(head)
		{
			printf("%d ", head->data);
			head = head->next;
		}
	}
}


int main(int argc, char *argv[])
{
    /* SAFETY CHECK: Ensure arguments exist before accessing them */
    if (argc < 4)
    {
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return 1;
    }

    /* Declare pointers - Initialization happens inside the loop if reusing, 
       but good practice to set NULL here too */
    Dlist *head1 = NULL, *tail1 = NULL; 
    Dlist *head2 = NULL, *tail2 = NULL;
    char option, operator;

    do
    {
        /* IMPORTANT: Reset pointers for every retry loop */
        head1 = tail1 = NULL;
        head2 = tail2 = NULL;

        // --- Operand 1 Parsing ---
        // Iterate through the string character by character
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            // Convert char digit to integer (e.g., '5' - '0' = 5)
            int num = argv[1][i] - '0';
            insert_at_last(&head1, &tail1, num);
        }

        // --- Operator ---
        operator = argv[2][0];

        // --- Operand 2 Parsing ---
        for (int j = 0; argv[3][j] != '\0'; j++)
        {
            int num = argv[3][j] - '0';
            insert_at_last(&head2, &tail2, num);
        }

        printf("List 1: ");
        print_list(head1, tail1);
        printf("\nOperator: %c\n", operator);
        printf("List 2: ");
        print_list(head2, tail2);
        printf("\n");

        switch (operator)
        {
            case '+':
                // dl_add(head1, tail1, head2, tail2, &headR);
                break;
            case '-':   
                // dl_sub(...);
                break;
            case '*':   
                // dl_mul(...);
                break;
            case '/':   
                // dl_div(...);
                break;
            default:
                printf("Invalid Operator\n");
        }

        printf("Want to continue? Press [yY]: ");
        scanf("\n%c", &option);
        
        // Note: Since you use argv inside the loop, continuing will 
        // just recalculate the same command line arguments again.
        
    } while (option == 'y' || option == 'Y');

    return 0;
}
