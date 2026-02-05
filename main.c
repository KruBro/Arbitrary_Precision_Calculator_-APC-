/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"

// int compare(*head, *tail);

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

// void swap(char **argv, int i, int j)
// {
//     char *temp = argv[i];
//     argv[i] = argv[j];
//     argv[j] = temp;
// }

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

        

        int isOp1Negative = 0;
        int isOp2Negative = 0;
        int isBothNegative = 0;

        // int digit_count_operand_1 = 0;
        // int digit_count_operand_2 = 0;
        // --- Operand 1 Parsing ---
        // Iterate through the string character by character

        int i = 0;
        
        //if it is negative number, skip the first character
        if(isNegative(argv, 1, i))
        {
            i = 1;
            isOp1Negative = 1;
        }

        for (; argv[1][i] != '\0'; i++)
        {
            // Convert char digit to integer (e.g., '5' - '0' = 5)
            int num = argv[1][i] - '0';
            // digit_count_operand_1++;
            insert_at_last(&head1, &tail1, num);
        }

        // --- Operator ---
        operator = argv[2][0];

        // --- Operand 2 Parsing ---
        int j = 0;

        //if it is negative number, skip the first character
        if(isNegative(argv, 3, j))
        {
            j = 1;
            isOp2Negative = 1;
        }

        for (; argv[3][j] != '\0'; j++)
        {
            int num = argv[3][j] - '0';
            // digit_count_operand_2++;
            insert_at_last(&head2, &tail2, num);
        }

        //Check if Both Operand Negative
        if(isOp1Negative == 1 && isOp2Negative == 1)
            isBothNegative = 1;

        // printf("%d %d\n", digit_count_operand_1, digit_count_operand_2);
        int digit_count_operand_1 = strlen(argv[1]);
        int digit_count_operand_2 = strlen(argv[3]);
        
        if(isOp1Negative)
        {
            digit_count_operand_1--;
            printf("-");
        }
        print_list(head1);

        printf("%c ", operator);

        if(isOp2Negative)
        {
            digit_count_operand_2--;
            printf("-");
        }    
        print_list(head2);

        switch (operator)
        {
            case '+':
                addition(&head1, &tail1, &head2, &tail2, &headR);
                printf("= ");
                if(isBothNegative)
                    printf("-");
                print_list(headR);
                printf("\n");
                break;
            case '-':   
                subtraction(&head1, &tail1, &head2, &tail2, &headR);
                printf("= ");
                if(isBothNegative && headR->data)
                    printf("-");
                print_list(headR);
                printf("\n");
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

        printf("Total Digits of Operand 1 : %d\n", digit_count_operand_1);
        printf("Total Digits of Operand 2 : %d\n", digit_count_operand_2);

        free_list(&head1);
        free_list(&head2);
        free_list(&headR);

        printf("Want to Re-check the calculation ? Press [yY]: ");
        scanf("\n%c", &option);
        
    } while (option == 'y' || option == 'Y');

    return 0;
}
