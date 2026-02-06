#include "apc.h"

void parse_operands(char **argv, int i, int j, Dlist **head, Dlist **tail)
{
    // Iterate 'j' to move through the string characters. Keep 'i' constant.
    for(; argv[i][j]; j++) 
    {
        // Use 'i' to select the string, 'j' to select the character
        int num = argv[i][j] - '0'; 
        
        // Pass 'head' and 'tail' directly (they are already Dlist **)
        insert_at_last(head, tail, num); 
    }
}