/*******************************************************************************************************************************************************************
 * File Name     : main_helpers.c
 * Description   : Helper functions for main program
 * Functions     : parse_arguments, perform_operation
 *******************************************************************************************************************************************************************/

#include "apc.h"

/**
 * Parse and validate command line arguments
 */
int parse_arguments(int argc, char *argv[], char **operand1, char **operand2, char *operator)
{
    /* Check if correct number of arguments provided */
    if (argc < 4)
    {
        fprintf(stderr, "[ERROR]: Insufficient arguments\n");
        fprintf(stderr, "Usage: %s <number1> <operator> <number2>\n", argv[0]);
        fprintf(stderr, "Example: %s 123.45 + 67.89\n", argv[0]);
        fprintf(stderr, "Supported operators: +, -, x\n");
        return FAILURE;
    }

    /* Validate operand 1 */
    if (!validate_number(argv[1]))
    {
        fprintf(stderr, "[ERROR]: Invalid first operand '%s'\n", argv[1]);
        return FAILURE;
    }

    /* Validate operator */
    if (strlen(argv[2]) != 1 || (argv[2][0] != '+' && argv[2][0] != '-' && 
                                  argv[2][0] != 'x' && argv[2][0] != '/'))
    {
        fprintf(stderr, "[ERROR]: Invalid operator '%s'\n", argv[2]);
        fprintf(stderr, "Supported operators: +, -, x, /\n");
        return FAILURE;
    }

    /* Validate operand 2 */
    if (!validate_number(argv[3]))
    {
        fprintf(stderr, "[ERROR]: Invalid second operand '%s'\n", argv[3]);
        return FAILURE;
    }

    /* Assign outputs */
    *operand1 = argv[1];
    *operand2 = argv[3];
    *operator = argv[2][0];

    return SUCCESS;
}

/**
 * Perform the requested arithmetic operation
 */
int perform_operation(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, 
                      Dlist **headR, Dlist **tailR, char operator,
                      int is_op1_negative, int is_op2_negative, 
                      int op1_bigger, int op2_bigger, int is_both_equal,
                      int decimal1, int decimal2)
{
    int result = FAILURE;
    int is_both_negative = (is_op1_negative && is_op2_negative);

    switch (operator)
    {
        case '+':
            printf("= ");

            /* Different signs: Subtract smaller from larger */
            if (is_op1_negative != is_op2_negative) 
            {
                if (op2_bigger) 
                {
                    swap(head1, tail1, head2, tail2);
                    result = subtraction(head1, tail1, head2, tail2, headR, tailR);
                    
                    /* Result takes sign of the larger number */
                    if (is_op2_negative && !is_both_equal)
                    {
                        printf("-");
                    }
                }
                else if (op1_bigger)
                {
                    result = subtraction(head1, tail1, head2, tail2, headR, tailR);
                    
                    /* Result takes sign of the larger number (op1) */
                    if (is_op1_negative)
                    {
                        printf("-");
                    }
                }
                else
                {
                    /* Equal magnitude, opposite signs: result is 0 */
                    result = subtraction(head1, tail1, head2, tail2, headR, tailR);
                }
            }
            /* Same signs: Add values, result has same sign */
            else 
            {   
                result = addition(head1, tail1, head2, tail2, headR, tailR);
                
                if (is_both_negative && !is_both_equal)
                {
                    printf("-");
                }
            }
            break;

        case '-':
            printf("= ");

            /* Different signs: Actually addition, result takes sign of first number */
            if (is_op1_negative != is_op2_negative) 
            {
                result = addition(head1, tail1, head2, tail2, headR, tailR);
                
                if (is_op1_negative)
                {
                    printf("-");
                }
            }
            /* Same signs: Subtraction */
            else 
            {
                if (op2_bigger) 
                {
                    swap(head1, tail1, head2, tail2);
                    result = subtraction(head1, tail1, head2, tail2, headR, tailR);
                    
                    /* Sign logic: (+)-(+) with op2>op1 = negative, (-)-(-)  with op2>op1 = positive */
                    if (!is_both_negative)
                    {
                        printf("-");
                    }
                } 
                else 
                {
                    result = subtraction(head1, tail1, head2, tail2, headR, tailR);
                    
                    /* Sign logic: (-)-(-)  with op1>op2 = negative */
                    if (is_both_negative && !is_both_equal)
                    {
                        printf("-");
                    }
                }
            }
            break;

        case 'x':   
            printf("= ");
            
            /* Result is negative if signs differ */
            if (is_op1_negative != is_op2_negative)
            {
                printf("-");
            }
            
            result = multiplication(head1, tail1, head2, tail2, headR, tailR, decimal1, decimal2);
            break;

        case '/':
            printf("= ");

            /* Result is negative if signs differ (positive / negative or vice versa) */
            if (is_op1_negative != is_op2_negative)
            {
                printf("-");
            }

            result = division(head1, tail1, head2, tail2, headR, tailR);
            break;

        default:
            fprintf(stderr, "[ERROR]: Invalid operator\n");
            result = FAILURE;
    }

    return result;
}