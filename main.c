/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"

void print_list(Dlist *head)
{
	if(head == NULL)
		printf("[INFO]: List is Empty\n");
	else
	{
		while(head)
		{
			printf("%d", head->data);
			head = head->next;
		}
	}
    printf(" ");
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
    Dlist *headR = NULL;
    char option, operator;

    do
    {
        /* IMPORTANT: Reset pointers for every retry loop */
        head1 = tail1 = NULL;
        head2 = tail2 = NULL;
        headR = NULL;
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

        print_list(head1);
        printf("%c ", operator);
        print_list(head2);

        switch (operator)
        {
            case '+':
                addition(&head1, &tail1, &head2, &tail2, &headR);
                printf("= ");
                print_list(headR);
                printf("\n");
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

        free_list(&head1);
        free_list(&head2);
        free_list(&headR);

        printf("Want to Re-check the calculation ? Press [yY]: ");
        scanf("\n%c", &option);
        
    } while (option == 'y' || option == 'Y');

    return 0;
}
