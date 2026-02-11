/*******************************************************************************************************************************************************************
 * File Name     : is_negative.c
 * Description   : Function to check if a command line argument starts with a negative sign
 * Function      : is_negative
 * Input Params  : argv - Command line arguments array
 *                 arg_index - Index of the argument to check
 *                 char_index - Character index within the argument
 * Return Value  : TRUE if the character is '-', FALSE otherwise
 *******************************************************************************************************************************************************************/

#include "apc.h"

int is_negative(char **argv, int arg_index, int char_index)
{
    /* Validate input parameters */
    if (argv == NULL || argv[arg_index] == NULL)
    {
        return FALSE;
    }

    /* Check if the character at the given position is a minus sign */
    if (argv[arg_index][char_index] == '-')
    {
        return TRUE;
    }
    
    return FALSE;
}