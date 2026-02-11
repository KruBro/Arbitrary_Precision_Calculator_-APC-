/*******************************************************************************************************************************************************************
 * File Name     : validate_number.c
 * Description   : Function to validate if a string represents a valid number
 * Function      : validate_number
 * Input Params  : str - String to validate
 * Return Value  : TRUE if valid number, FALSE otherwise
 *******************************************************************************************************************************************************************/

#include "apc.h"

int validate_number(const char *str)
{
    /* Check for NULL or empty string */
    if (str == NULL || *str == '\0')
    {
        return FALSE;
    }

    int i = 0;
    int decimal_count = 0;
    int digit_count = 0;

    /* Skip leading minus sign */
    if (str[i] == '-')
    {
        i++;
        
        /* A minus sign alone is not a valid number */
        if (str[i] == '\0')
        {
            return FALSE;
        }
    }

    /* Check each character */
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            decimal_count++;
            
            /* Only one decimal point allowed */
            if (decimal_count > 1)
            {
                return FALSE;
            }
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            digit_count++;
        }
        else
        {
            /* Invalid character found */
            return FALSE;
        }
        
        i++;
    }

    /* Must have at least one digit */
    if (digit_count == 0)
    {
        return FALSE;
    }

    return TRUE;
}