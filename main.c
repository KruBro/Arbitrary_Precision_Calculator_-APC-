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

// Accept Dlist ** (pointer to pointer) to modify the caller's variables
void swap(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    Dlist *temp1 = *head1;
    *head1 = *head2;
    *head2 = temp1;

    Dlist *temp2 = *tail1;
    *tail1 = *tail2;
    *tail2 = temp2;
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

        int digit_count_operand_1 = strlen(argv[1]);
        int digit_count_operand_2 = strlen(argv[3]);

        int isOp1Negative = 0;
        int isOp2Negative = 0;
        int isBothNegative = 0;

        int op1Bigger = 0;
        int op2Bigger = 0;
        int isBothEqual = 0;

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
            digit_count_operand_1--;
        }

        parse_operands(argv, 1, i, &head1, &tail1);

        // --- Operator ---
        operator = argv[2][0];

        // --- Operand 2 Parsing ---
        int j = 0;

        //if it is negative number, skip the first character
        if(isNegative(argv, 3, j))
        {
            j = 1;
            isOp2Negative = 1;
            digit_count_operand_2--;
        }

        parse_operands(argv, 3, j, &head2, &tail2);

        //Check if Both Operand Negative
        if(isOp1Negative == 1 && isOp2Negative == 1)
            isBothNegative = 1;

        //Check which operand is bigger
        if(compare(digit_count_operand_1, digit_count_operand_2, head1, head2) == 1)
        {
            op1Bigger = 1;
            op2Bigger = 0;
        }
        else if(compare(digit_count_operand_1, digit_count_operand_2, head1, head2) == 2)
        {
            op1Bigger = 0;
            op2Bigger = 1;
        }
        else
        {
            isBothEqual = 1;
        }
        

        switch (operator)
        {
            case '+':
                printf("= ");

                // Scenario 1: Different Signs (One is + and the other is -)
                // Rule: Subtract smaller absolute value from larger, sign follows the "larger" number.
                if (isOp1Negative != isOp2Negative) 
                {
                    if (op2Bigger) 
                    {
                        swap(&head1, &tail1, &head2, &tail2);
                        // If the original Op2 was negative and was bigger, result is negative
                        if (isOp2Negative) printf("-");
                    }
                    else if (op1Bigger)
                    {
                        // If the original Op1 was negative and was bigger, result is negative
                        if (isOp1Negative) printf("-");
                    }
        
                    subtraction(&head1, &tail1, &head2, &tail2, &headR);
                }       
                // Scenario 2: Same Signs (Both + or Both -)
                // Rule: Add values normally. If both were negative, result is negative.
                else 
                {   
                    if (isBothNegative && !isBothEqual) printf("-"); 
        
                    addition(&head1, &tail1, &head2, &tail2, &headR);
                }

                print_list(headR);
                printf("\n");
                break;

                
            case '-':
                printf("= ");
    
                // 1. Determine if we are doing ADDITION or SUBTRACTION
                // If signs are different (e.g., 5 - (-3) or -5 - 3), it's actually ADDITION
                if (isOp1Negative != isOp2Negative) 
                {
                    addition(&head1, &tail1, &head2, &tail2, &headR);
                    // If the first number was negative, the result is always negative: -5 - 3 = -(5+3)
                    if (isOp1Negative) printf("-");
                }
                // 2. If signs are the same (e.g., 10 - 4 or -10 - (-4)), it's SUBTRACTION
                else 
                {
                    // Always subtract smaller from larger
                    if (op2Bigger) 
                    {
                    swap(&head1, &tail1, &head2, &tail2);
                    subtraction(&head1, &tail1, &head2, &tail2, &headR);
            
                    // Sign logic: 
                    // If both (+): 4 - 10 = -6 (result is negative)
                    // If both (-): -4 - (-10) = +6 (result is positive)
                    if (!isBothNegative) printf("-");
                    } 
                    else 
                    {
                        subtraction(&head1, &tail1, &head2, &tail2, &headR);
            
                         // Sign logic:
                        // If both (-): -10 - (-4) = -6 (result is negative)
                        if (isBothNegative && !isBothEqual) printf("-");
                    }
                }

                print_list(headR);
                printf("\n");
                break;

            case 'x':   
                printf("= ");
                if(isOp1Negative != isOp2Negative)
                    printf("-");
                multiplication(&head1, &tail1, &head2, &tail2, &headR);
                print_list(headR);
                printf("\n");
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
