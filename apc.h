/*******************************************************************************************************************************************************************
 * File Name     : apc.h
 * Description   : Header file for Arbitrary Precision Calculator
 *                 Contains all structure definitions, enums, and function prototypes
 * Author        : [Your Name]
 * Date          : [Date]
 *******************************************************************************************************************************************************************/

#ifndef APC_H
#define APC_H

/* Standard Library Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macro Definitions */
#define SUCCESS 0
#define FAILURE -1
#define TRUE 1
#define FALSE 0

/* Type Definitions */
typedef int data_t;

/* Comparison Result Enumeration */
typedef enum {
    NUMBERS_EQUAL = 0,
    FIRST_LARGER = 1,
    SECOND_LARGER = 2
} ComparisonResult;

/* Doubly Linked List Node Structure */
typedef struct node {
    struct node *prev;
    data_t data;
    struct node *next;
} Dlist;

/* Big Number Structure (for future enhancement) */
typedef struct {
    Dlist *head;
    Dlist *tail;
    int is_negative;
    int decimal_places;  /* Number of digits after decimal point */
} BigNumber;

/* ========================================
 * LIST MANIPULATION FUNCTIONS
 * ======================================== */

/**
 * @brief Insert a new node at the beginning of the list
 * @param head Pointer to the head pointer of the list
 * @param data Data to be inserted
 * @return SUCCESS on successful insertion, FAILURE otherwise
 */
int insert_at_first(Dlist **head, data_t data);

/**
 * @brief Insert a new node at the end of the list
 * @param head Pointer to the head pointer of the list
 * @param tail Pointer to the tail pointer of the list
 * @param data Data to be inserted
 * @return SUCCESS on successful insertion, FAILURE otherwise
 */
int insert_at_last(Dlist **head, Dlist **tail, data_t data);

/**
 * @brief Print all elements in the list
 * @param head Pointer to the head of the list
 */
void print_list(Dlist *head);

/**
 * @brief Free all nodes in the list and reset head pointer to NULL
 * @param head Pointer to the head pointer of the list
 */
void free_list(Dlist **head);

/* ========================================
 * UTILITY FUNCTIONS
 * ======================================== */

/**
 * @brief Swap two doubly linked lists
 * @param head1 Pointer to the head pointer of first list
 * @param tail1 Pointer to the tail pointer of first list
 * @param head2 Pointer to the head pointer of second list
 * @param tail2 Pointer to the tail pointer of second list
 */
void swap(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);

/**
 * @brief Remove leading zeros from a number (e.g., 00123 -> 123)
 * @param head Pointer to the head pointer of the list
 */
void remove_leading_zeros(Dlist **head);

/**
 * @brief Remove trailing zeros after decimal point (e.g., 123.4500 -> 123.45)
 * @param tail Pointer to the tail pointer of the list
 * @param decimal_pos Pointer to the decimal point node
 */
void remove_trailing_zeros(Dlist **tail, Dlist *decimal_pos);

/**
 * @brief Remove the decimal point from the list
 * @param head Pointer to the head pointer of the list
 * @return Pointer to the node that was before the decimal point (NULL if not found)
 */
Dlist* remove_dot(Dlist **head);

/**
 * @brief Find the decimal point in the list
 * @param head Pointer to the head of the list
 * @return Pointer to the decimal point node, or NULL if not found
 */
Dlist* find_decimal_point(Dlist *head);

/**
 * @brief Count decimal places in a number
 * @param head Pointer to the head of the list
 * @return Number of digits after decimal point, or 0 if no decimal
 */
int count_decimal_places(Dlist *head);

/**
 * @brief Pad a number with zeros to match decimal places
 * @param head Pointer to the head pointer of the list
 * @param tail Pointer to the tail pointer of the list
 * @param places Number of zeros to add at the end
 * @return SUCCESS on successful padding, FAILURE otherwise
 */
int pad_decimal_places(Dlist **head, Dlist **tail, int places);

/**
 * @brief Check if a string starts with a negative sign
 * @param argv Command line arguments array
 * @param arg_index Index of the argument to check
 * @param char_index Character index within the argument
 * @return TRUE if negative, FALSE otherwise
 */
int is_negative(char **argv, int arg_index, int char_index);

/**
 * @brief Compare two numbers based on their absolute values
 * @param len1 Number of digits in first number (excluding decimal)
 * @param len2 Number of digits in second number (excluding decimal)
 * @param head1 Pointer to the head of first list
 * @param head2 Pointer to the head of second list
 * @return FIRST_LARGER if num1 > num2, SECOND_LARGER if num1 < num2, NUMBERS_EQUAL if equal
 */
ComparisonResult compare(int len1, int len2, Dlist *head1, Dlist *head2);

/**
 * @brief Parse command line operand and create a linked list
 * @param argv Command line arguments array
 * @param arg_index Index of the argument to parse
 * @param start_char Starting character index (to skip '-' sign)
 * @param head Pointer to the head pointer of the list
 * @param tail Pointer to the tail pointer of the list
 */
void parse_operands(char **argv, int arg_index, int start_char, Dlist **head, Dlist **tail);

/**
 * @brief Validate if a string is a valid number
 * @param str String to validate
 * @return TRUE if valid, FALSE otherwise
 */
int validate_number(const char *str);

/* ========================================
 * ARITHMETIC OPERATION FUNCTIONS
 * ======================================== */

/**
 * @brief Add two large numbers (supports decimals)
 * @param head1 Pointer to the head pointer of first number
 * @param tail1 Pointer to the tail pointer of first number
 * @param head2 Pointer to the head pointer of second number
 * @param tail2 Pointer to the tail pointer of second number
 * @param headR Pointer to the head pointer of result
 * @param tailR Pointer to the tail pointer of result
 * @return SUCCESS on successful operation, FAILURE otherwise
 */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/**
 * @brief Subtract two large numbers (supports decimals)
 * @param head1 Pointer to the head pointer of first number (larger)
 * @param tail1 Pointer to the tail pointer of first number
 * @param head2 Pointer to the head pointer of second number (smaller)
 * @param tail2 Pointer to the tail pointer of second number
 * @param headR Pointer to the head pointer of result
 * @param tailR Pointer to the tail pointer of result
 * @return SUCCESS on successful operation, FAILURE otherwise
 */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/**
 * @brief Multiply two large numbers (supports decimals)
 * @param head1 Pointer to the head pointer of first number
 * @param tail1 Pointer to the tail pointer of first number
 * @param head2 Pointer to the head pointer of second number
 * @param tail2 Pointer to the tail pointer of second number
 * @param headR Pointer to the head pointer of result
 * @param tailR Pointer to the tail pointer of result
 * @param decimal1 Number of decimal places in first number
 * @param decimal2 Number of decimal places in second number
 * @return SUCCESS on successful operation, FAILURE otherwise
 */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR, int decimal1, int decimal2);

/**
 * @brief Divide two large numbers using long division with decimal support.
 *        Produces up to 10 decimal places for non-terminating results.
 * @param head1 Pointer to the head pointer of dividend
 * @param tail1 Pointer to the tail pointer of dividend
 * @param head2 Pointer to the head pointer of divisor
 * @param tail2 Pointer to the tail pointer of divisor
 * @param headR Pointer to the head pointer of result
 * @param tailR Pointer to the tail pointer of result
 * @return SUCCESS on successful operation, FAILURE otherwise
 */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* ========================================
 * MAIN PROGRAM HELPER FUNCTIONS
 * ======================================== */

/**
 * @brief Parse and validate command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @param operand1 Output: first operand string
 * @param operand2 Output: second operand string
 * @param operator Output: operator character
 * @return SUCCESS if valid, FAILURE otherwise
 */
int parse_arguments(int argc, char *argv[], char **operand1, char **operand2, char *operator);

/**
 * @brief Perform the requested arithmetic operation
 * @param head1 Pointer to the head pointer of first number
 * @param tail1 Pointer to the tail pointer of first number
 * @param head2 Pointer to the head pointer of second number
 * @param tail2 Pointer to the tail pointer of second number
 * @param headR Pointer to the head pointer of result
 * @param tailR Pointer to the tail pointer of result
 * @param operator Arithmetic operator (+, -, x, /)
 * @param is_op1_negative Flag indicating if operand 1 is negative
 * @param is_op2_negative Flag indicating if operand 2 is negative
 * @param op1_bigger Flag indicating if operand 1 is bigger
 * @param op2_bigger Flag indicating if operand 2 is bigger
 * @param decimal1 Number of decimal places in operand 1
 * @param decimal2 Number of decimal places in operand 2
 * @return SUCCESS if operation completed, FAILURE otherwise
 */
int perform_operation(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, 
                      Dlist **headR, Dlist **tailR, char operator,
                      int is_op1_negative, int is_op2_negative, 
                      int op1_bigger, int op2_bigger, int is_both_equal,
                      int decimal1, int decimal2);

#endif /* APC_H */