/*******************************************************************************************************************************************************************
 * File Name     : division.c
 * Description   : Performs division of two large numbers with decimal support using the Long Division algorithm.
 * Function      : division
 *
 * Input Params  : head1, tail1 - Dividend (the number being divided)
 *                 head2, tail2 - Divisor  (the number to divide by)
 *                 headR, tailR - Quotient (the result)
 *
 * Return Value  : SUCCESS on successful operation
 *                 FAILURE on division by zero or memory allocation error
 *
 * Algorithm (Long Division):
 *
 *   The algorithm mirrors exactly how you do long division on paper.
 *   Given:  dividend / divisor = quotient
 *
 *   Example: 135 / 4
 *
 *   Step 1 - Handle decimals:
 *            Both numbers are scaled to integers by multiplying by 10^(max_decimal).
 *            e.g. 13.5 / 2.5  ->  135 / 25   (multiply both by 10)
 *
 *   Step 2 - Check for division by zero:
 *            If the divisor list represents zero, return FAILURE.
 *
 *   Step 3 - Long division digit by digit:
 *
 *       Maintain a "current remainder" list, initially empty.
 *
 *       For each digit in the dividend (left to right):
 *           a) Bring down the digit: append it to the right of the remainder.
 *           b) Count how many times the divisor fits into the remainder (0-9).
 *              This is done by repeated subtraction - subtract divisor from
 *              remainder until remainder < divisor, counting each subtraction.
 *           c) Append that count (the quotient digit) to the result list.
 *           d) The leftover after subtraction becomes the new remainder.
 *
 *       e.g. 135 / 4:
 *           bring down 1  -> remainder=1,  1 < 4,  digit=0,  remainder=1
 *           bring down 3  -> remainder=13, 13/4=3, digit=3,  remainder=1
 *           bring down 5  -> remainder=15, 15/4=3, digit=3,  remainder=3
 *           integer quotient = 033 -> 33, remainder = 3
 *
 *   Step 4 - Produce decimal places in the result:
 *
 *       After all dividend digits are consumed, if there is still a remainder,
 *       continue by bringing down a zero each iteration (appending 0 to the
 *       remainder), exactly like doing long division past the decimal point.
 *
 *       We produce DIVISION_PRECISION decimal digits this way.
 *
 *       After the integer part ends, insert '.' into the result list,
 *       then keep computing up to DIVISION_PRECISION more digits.
 *
 *   Step 5 - Final cleanup:
 *       Remove leading zeros, then remove trailing zeros after the decimal.
 *
 * Internal Helpers (static, private to this file):
 *   - is_zero_list()         : checks if a list represents the value 0
 *   - copy_list()            : deep-copies a list (used to duplicate divisor)
 *   - bring_down_digit()     : appends a digit to the right of the remainder
 *   - count_quotient_digit() : counts how many times divisor fits in remainder
 *                              using the existing subtraction() function
 *
 *******************************************************************************************************************************************************************/

#include "apc.h"

/* Number of decimal places to compute after the decimal point */
#define DIVISION_PRECISION 10

/* ============================================================
 * PRIVATE HELPER FUNCTIONS (static = not visible outside file)
 * ============================================================ */

/**
 * @brief Check if a linked list represents the value zero.
 *        A list is zero if it is NULL or every node's data is 0.
 * @param head Head of the list to check
 * @return TRUE if the list is zero, FALSE otherwise
 */
static int is_zero_list(Dlist *head)
{
    if (head == NULL)
    {
        return TRUE;
    }

    Dlist *temp = head;
    while (temp != NULL)
    {
        if (temp->data != 0)
        {
            return FALSE;
        }
        temp = temp->next;
    }

    return TRUE;
}

/**
 * @brief Deep-copy a linked list into a new independent list.
 *        Used to duplicate the divisor before each subtraction,
 *        because subtraction() internally modifies the lists it operates on.
 * @param src_head  Head of the source list
 * @param dest_head Output: head of the new copy
 * @param dest_tail Output: tail of the new copy
 * @return SUCCESS on successful copy, FAILURE on memory error
 */
static int copy_list(Dlist *src_head, Dlist **dest_head, Dlist **dest_tail)
{
    *dest_head = NULL;
    *dest_tail = NULL;

    Dlist *temp = src_head;
    while (temp != NULL)
    {
        if (insert_at_last(dest_head, dest_tail, temp->data) == FAILURE)
        {
            free_list(dest_head);
            return FAILURE;
        }
        temp = temp->next;
    }

    return SUCCESS;
}

/**
 * @brief Bring one digit down onto the right end of the remainder list.
 *        Mirrors the "bring down" step in paper long division.
 *
 *        e.g. remainder=13, bring down digit=5  ->  remainder=135
 *
 *        Special case: if remainder is currently a lone zero,
 *        replace it with the new digit to avoid accumulating
 *        leading zeros such as "05", "005", etc.
 *
 * @param rem_head  Pointer to head pointer of remainder list (modified)
 * @param rem_tail  Pointer to tail pointer of remainder list (modified)
 * @param digit     The digit to append (0-9)
 * @return SUCCESS on success, FAILURE on memory error
 */
static int bring_down_digit(Dlist **rem_head, Dlist **rem_tail, int digit)
{
    /* If remainder is empty or is a single zero, replace it with the digit */
    if (*rem_head == NULL
        || (*rem_head == *rem_tail && (*rem_head)->data == 0))
    {
        free_list(rem_head);
        *rem_tail = NULL;
        return insert_at_last(rem_head, rem_tail, digit);
    }

    return insert_at_last(rem_head, rem_tail, digit);
}

/**
 * @brief Find how many times divisor fits into remainder (0 to 9).
 *
 *        Computes:  quotient_digit = floor(remainder / divisor)
 *        using repeated subtraction. This is always 0-9 because
 *        long division brings down only one digit at a time, so
 *        remainder is always < divisor * 10.
 *
 *        After the function returns, remainder has been updated to:
 *            remainder = remainder - (quotient_digit * divisor)
 *        i.e. the remainder is what is "left over" for the next step.
 *
 * @param rem_head   Pointer to head pointer of remainder (modified in-place)
 * @param rem_tail   Pointer to tail pointer of remainder (modified in-place)
 * @param div_head   Head of divisor list (read-only, never modified)
 * @param div_tail   Tail of divisor list (read-only, never modified)
 * @param digit_out  Output: the quotient digit found (0-9)
 * @return SUCCESS on success, FAILURE on memory error
 */
static int count_quotient_digit(Dlist **rem_head, Dlist **rem_tail,
                                Dlist *div_head, Dlist *div_tail,
                                int *digit_out)
{
    /* div_tail is required by the public interface for consistency with
     * other functions, but compare() and subtraction() re-find the tail
     * internally from the head, so it is not directly used here. */
    (void)div_tail;

    int count = 0;

    while (TRUE)
    {
        /* Get current list lengths so compare() can work */
        int rem_len = 0, div_len = 0;
        Dlist *t = *rem_head;
        while (t != NULL) { rem_len++; t = t->next; }
        t = div_head;
        while (t != NULL) { div_len++; t = t->next; }

        /* Stop when remainder < divisor — divisor no longer fits */
        ComparisonResult cmp = compare(rem_len, div_len, *rem_head, div_head);
        if (cmp == SECOND_LARGER)
        {
            break;
        }

        /* Also stop if remainder has already reached zero */
        if (is_zero_list(*rem_head))
        {
            break;
        }

        /* Copy the divisor — subtraction() modifies its inputs */
        Dlist *div_copy_head = NULL, *div_copy_tail = NULL;
        if (copy_list(div_head, &div_copy_head, &div_copy_tail) == FAILURE)
        {
            return FAILURE;
        }

        /* remainder = remainder - divisor */
        Dlist *new_rem_head = NULL, *new_rem_tail = NULL;
        if (subtraction(rem_head, rem_tail,
                        &div_copy_head, &div_copy_tail,
                        &new_rem_head, &new_rem_tail) == FAILURE)
        {
            free_list(&div_copy_head);
            return FAILURE;
        }

        free_list(&div_copy_head);
        free_list(rem_head);

        *rem_head = new_rem_head;
        *rem_tail = new_rem_tail;
        count++;

        /* Sanity guard: should never exceed 9, but protect anyway */
        if (count > 9)
        {
            break;
        }
    }

    *digit_out = count;
    return SUCCESS;
}

/* ============================================================
 * MAIN DIVISION FUNCTION
 * ============================================================ */

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR)
{
    /* ── Validate inputs ───────────────────────────────────────────── */
    if (head1 == NULL || tail1 == NULL || head2 == NULL || tail2 == NULL
        || headR == NULL || tailR == NULL)
    {
        return FAILURE;
    }

    /* ── Step 1: Scale both operands to integers ───────────────────── *
     *
     *  Pad the operand with fewer decimal places so both have the same
     *  number of fractional digits, then remove both decimal points.
     *  This converts the division to a pure-integer problem.
     *
     *  e.g. 13.5 / 2.75
     *       decimal1=1, decimal2=2, max_decimal=2
     *       pad op1 by 1: 13.50  -> remove dot -> 1350
     *       pad op2 by 0: 2.75   -> remove dot ->  275
     *       now compute: 1350 / 275
     */
    int decimal1 = count_decimal_places(*head1);
    int decimal2 = count_decimal_places(*head2);
    int max_decimal = (decimal1 > decimal2) ? decimal1 : decimal2;

    if (decimal1 < max_decimal)
    {
        if (pad_decimal_places(head1, tail1, max_decimal - decimal1) == FAILURE)
        {
            return FAILURE;
        }
    }
    if (decimal2 < max_decimal)
    {
        if (pad_decimal_places(head2, tail2, max_decimal - decimal2) == FAILURE)
        {
            return FAILURE;
        }
    }

    remove_dot(head1);
    remove_dot(head2);

    /* Re-sync tail pointers — list lengths changed after removing dots */
    Dlist *sync = *head1;
    while (sync != NULL && sync->next != NULL) { sync = sync->next; }
    *tail1 = sync;

    sync = *head2;
    while (sync != NULL && sync->next != NULL) { sync = sync->next; }
    *tail2 = sync;

    /* Remove leading zeros introduced by scaling.
     * e.g. 0.5 scaled to 2 decimals becomes "05" — strip to "5".
     * This is safe because we already checked for zero above and
     * both values are treated as plain integers from here on. */
    remove_leading_zeros(head1);
    remove_leading_zeros(head2);

    /* Re-sync tails again after leading-zero removal */
    sync = *head1;
    while (sync != NULL && sync->next != NULL) { sync = sync->next; }
    *tail1 = sync;

    sync = *head2;
    while (sync != NULL && sync->next != NULL) { sync = sync->next; }
    *tail2 = sync;

    /* ── Step 2: Division by zero check ───────────────────────────── */
    if (is_zero_list(*head2))
    {
        fprintf(stderr, "[ERROR]: Division by zero is undefined\n");
        return FAILURE;
    }

    /* ── Steps 3 & 4: Long division ───────────────────────────────── */

    Dlist *rem_head = NULL;       /* Running remainder, starts empty   */
    Dlist *rem_tail = NULL;
    Dlist *dividend_ptr = *head1; /* Walk dividend left to right       */
    int decimal_inserted = FALSE;

    /* ── Phase A: Process all real dividend digits ─────────────────── */
    while (dividend_ptr != NULL)
    {
        /* Bring the next dividend digit down into the remainder */
        if (bring_down_digit(&rem_head, &rem_tail, dividend_ptr->data) == FAILURE)
        {
            free_list(&rem_head);
            return FAILURE;
        }

        /* Compute quotient digit for this position */
        int q_digit = 0;
        if (count_quotient_digit(&rem_head, &rem_tail,
                                 *head2, *tail2, &q_digit) == FAILURE)
        {
            free_list(&rem_head);
            return FAILURE;
        }

        /* Append quotient digit to result */
        if (insert_at_last(headR, tailR, q_digit) == FAILURE)
        {
            free_list(&rem_head);
            return FAILURE;
        }

        dividend_ptr = dividend_ptr->next;
    }

    /* ── Phase B: Extend into decimal places ───────────────────────── *
     *
     *  If remainder != 0 after all dividend digits are consumed,
     *  the division is not exact. Continue bringing down zeros to
     *  generate up to DIVISION_PRECISION fractional digits.
     *
     *  First, insert '.' into the result to mark where decimals begin.
     */
    if (!is_zero_list(rem_head))
    {
        /* Insert decimal point into result */
        if (insert_at_last(headR, tailR, '.') == FAILURE)
        {
            free_list(&rem_head);
            return FAILURE;
        }
        decimal_inserted = TRUE;

        for (int i = 0; i < DIVISION_PRECISION; i++)
        {
            /* Bring down a virtual zero */
            if (bring_down_digit(&rem_head, &rem_tail, 0) == FAILURE)
            {
                free_list(&rem_head);
                return FAILURE;
            }

            int q_digit = 0;
            if (count_quotient_digit(&rem_head, &rem_tail,
                                     *head2, *tail2, &q_digit) == FAILURE)
            {
                free_list(&rem_head);
                return FAILURE;
            }

            if (insert_at_last(headR, tailR, q_digit) == FAILURE)
            {
                free_list(&rem_head);
                return FAILURE;
            }

            /* Exact division reached — no need for more decimal digits */
            if (is_zero_list(rem_head))
            {
                break;
            }
        }
    }

    /* Free the final remainder */
    free_list(&rem_head);

    /* ── Step 5: Cleanup ───────────────────────────────────────────── */
    remove_leading_zeros(headR);

    if (decimal_inserted)
    {
        Dlist *decimal_pos = find_decimal_point(*headR);
        if (decimal_pos != NULL)
        {
            remove_trailing_zeros(tailR, decimal_pos);
        }
    }

    /* Edge case: result is completely empty (0 / anything) -> output "0" */
    if (*headR == NULL)
    {
        if (insert_at_last(headR, tailR, 0) == FAILURE)
        {
            return FAILURE;
        }
    }

    return SUCCESS;
}