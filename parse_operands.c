/*******************************************************************************************************************************************************************
 * File Name     : parse_operands.c
 * Description   : Function to parse a command line operand string and create a linked list representation
 * Function      : parse_operands
 * Input Params  : argv - Command line arguments array
 *                 arg_index - Index of the argument to parse
 *                 start_char - Starting character index (used to skip '-' sign)
 *                 head - Pointer to the head pointer of the list
 *                 tail - Pointer to the tail pointer of the list
 * Return Value  : void
 *******************************************************************************************************************************************************************/

#include "apc.h"

void parse_operands(char **argv, int arg_index, int start_char, Dlist **head, Dlist **tail)
{
    /* Validate input parameters */
    if (argv == NULL || argv[arg_index] == NULL || head == NULL || tail == NULL)
    {
        return;
    }

    /* Iterate through each character in the string */
    for (int i = start_char; argv[arg_index][i] != '\0'; i++) 
    {
        char current_char = argv[arg_index][i];
        
        /* Handle decimal point */
        if (current_char == '.')
        {
            insert_at_last(head, tail, '.');
            continue;
        }
        
        /* Convert character to integer and insert into list */
        int digit = current_char - '0';
        insert_at_last(head, tail, digit);
    }
}