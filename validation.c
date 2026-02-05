#include "apc.h"

int isNegative(char **argv, int i, int j)
{
    if(argv[i][j] == '-')
        return 1;
    return 0;
}

int compare(int len1, int len2, Dlist *head1, Dlist *head2)
{
    // Check length first - this is non-negotiable for math!
    if (len1 > len2) return 1;
    if (len1 < len2) return 0;

    // If lengths are identical, find the first digit that differs
    while (head1 != NULL)
    {
        if (head1->data > head2->data)
            return 1;
        
        if (head1->data < head2->data)
            return 0;

        head1 = head1->next;
        head2 = head2->next;
    }

    // If they are equal, return 0 (doesn't matter which is first)
    return 0;
}
