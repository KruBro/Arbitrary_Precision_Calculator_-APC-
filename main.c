/*******************************************************************************************************************************************************************
 * File Name     : main.c
 * Description   : Main driver function for Arbitrary Precision Calculator
 *                 Supports addition, subtraction, multiplication, and division of large numbers with decimals
 * Author        : [Your Name]
 * Date          : [Date]
 *******************************************************************************************************************************************************************/

#include "apc.h"

/**
 * Print a linked list representing a number
 */
void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("0");
        return;
    }
    
    while (head != NULL)
    {
        if (head->data == '.')
        {
            printf(".");
        }
        else
        {
            printf("%d", head->data);
        }
        head = head->next;
    }
}

/**
 * Swap two doubly linked lists
 */
void swap(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    Dlist *temp_head = *head1;
    *head1 = *head2;
    *head2 = temp_head;

    Dlist *temp_tail = *tail1;
    *tail1 = *tail2;
    *tail2 = temp_tail;
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    char *operand1_str = NULL;
    char *operand2_str = NULL;
    char operator = '\0';
    char retry_option;

    /* Parse and validate arguments (only once, not in retry loop) */
    if (parse_arguments(argc, argv, &operand1_str, &operand2_str, &operator) == FAILURE)
    {
        return EXIT_FAILURE;
    }

    do
    {
        /* Initialize list pointers */
        Dlist *head1 = NULL, *tail1 = NULL; 
        Dlist *head2 = NULL, *tail2 = NULL;
        Dlist *headR = NULL, *tailR = NULL;

        /* Flags for operand properties */
        int is_op1_negative = FALSE;
        int is_op2_negative = FALSE;
        int op1_bigger = FALSE;
        int op2_bigger = FALSE;
        int is_both_equal = FALSE;

        /* Parse first operand */
        int start_index = 0;
        
        if (is_negative(argv, 1, 0))
        {
            start_index = 1;
            is_op1_negative = TRUE;
        }
        
        parse_operands(argv, 1, start_index, &head1, &tail1);
        
        /* Count decimal places and digits in first operand */
        int decimal1 = count_decimal_places(head1);
        int digit_count1 = 0;
        Dlist *temp = head1;
        while (temp != NULL)
        {
            if (temp->data != '.')
            {
                digit_count1++;
            }
            temp = temp->next;
        }
        digit_count1 -= decimal1;  /* Exclude decimal places from integer count */

        /* Parse second operand */
        start_index = 0;
        
        if (is_negative(argv, 3, 0))
        {
            start_index = 1;
            is_op2_negative = TRUE;
        }
        
        parse_operands(argv, 3, start_index, &head2, &tail2);
        
        /* Count decimal places and digits in second operand */
        int decimal2 = count_decimal_places(head2);
        int digit_count2 = 0;
        temp = head2;
        while (temp != NULL)
        {
            if (temp->data != '.')
            {
                digit_count2++;
            }
            temp = temp->next;
        }
        digit_count2 -= decimal2;  /* Exclude decimal places from integer count */

        /* Compare operands (ignoring signs and decimals for magnitude comparison) */
        Dlist *head1_copy = head1;
        Dlist *head2_copy = head2;
        
        /* Skip to first non-decimal digit for comparison */
        while (head1_copy != NULL && head1_copy->data == '.')
        {
            head1_copy = head1_copy->next;
        }
        while (head2_copy != NULL && head2_copy->data == '.')
        {
            head2_copy = head2_copy->next;
        }
        
        ComparisonResult comparison = compare(digit_count1, digit_count2, head1_copy, head2_copy);
        
        if (comparison == FIRST_LARGER)
        {
            op1_bigger = TRUE;
        }
        else if (comparison == SECOND_LARGER)
        {
            op2_bigger = TRUE;
        }
        else
        {
            is_both_equal = TRUE;
        }

        /* Perform the operation */
        int result = perform_operation(&head1, &tail1, &head2, &tail2, &headR, &tailR,
                                       operator, is_op1_negative, is_op2_negative,
                                       op1_bigger, op2_bigger, is_both_equal,
                                       decimal1, decimal2);

        /* Display result */
        if (result == SUCCESS)
        {
            print_list(headR);
            printf("\n");
        }
        else
        {
            fprintf(stderr, "[ERROR]: Operation failed\n");
        }

        /* Clean up memory */
        free_list(&head1);
        free_list(&head2);
        free_list(&headR);

        /* Ask user if they want to retry */
        printf("\nWant to perform another calculation? Press [yY]: ");
        scanf(" %c", &retry_option);
        
    } while (retry_option == 'y' || retry_option == 'Y');

    printf("Thank you for using the calculator!\n");
    return EXIT_SUCCESS;
}