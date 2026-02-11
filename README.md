# Arbitrary Precision Calculator (APC)

## Overview
A high-precision calculator that performs arithmetic operations on arbitrarily large numbers with decimal support. The calculator uses doubly linked lists to store digits, allowing operations on numbers of any size limited only by available memory.

## Features
- ✅ Addition with decimals
- ✅ Subtraction with decimals  
- ✅ Multiplication with decimals
- ✅ Division with decimals
- ✅ Support for negative numbers
- ✅ Automatic decimal point alignment
- ✅ Trailing zero removal
- ✅ Leading zero removal

## Project Structure
```
apc_improved/
├── apc.h                  # Header file with all declarations
├── main.c                 # Main driver program
├── main_helpers.c         # Helper functions for main
├── addition.c             # Addition implementation
├── subtraction.c          # Subtraction implementation
├── multiplication.c       # Multiplication implementation
├── division.c             # Division stub (not implemented)
├── insert_at_first.c      # Insert node at list beginning
├── insert_at_last.c       # Insert node at list end
├── free_list.c            # Free all list nodes
├── parse_operands.c       # Parse command line numbers
├── compare.c              # Compare two numbers
├── is_negative.c          # Check for negative sign
├── validate_number.c      # Validate number format
├── remove_dot.c           # Remove decimal point from list
├── decimal_utils.c        # Decimal handling utilities
├── makefile               # Build configuration
└── README.md              # This file
```

## Build Instructions

### Compile the program:
```
make
```

### Clean build artifacts:

```
make clean
```

### Rebuild from scratch:

```
make rebuild
```

### Run test cases:

```
make test
```

## Usage

### Basic syntax:

```
./calculator <number1> <operator> <number2>
```

### Supported operators:

* `+` : Addition
* `-` : Subtraction
* `x` : Multiplication
* `/` : Division

### Examples:

#### Addition:

```
./calculator 123.45 + 67.89
= 191.34
./calculator -50.5 + 100.25
= 49.75
./calculator -25.5 + -30.5
= -56
```

#### Subtraction:

```
./calculator 100.5 - 45.25
= 55.25
./calculator 50 - 100
= -50
./calculator -50 - -30
= -20
```

#### Multiplication:

```
./calculator 12.5 x 4.2
= 52.5
./calculator 0.1 x 0.1
= 0.01
./calculator -5.5 x 3
= -16.5
```

#### Division:

```
./calculator 10 / 2
= 5
./calculator 13.5 / 2.5
= 5.4
./calculator 1 / 3
= 0.3333333333
```

## Algorithm Details

### Addition with Decimals

1. Count decimal places in both numbers
2. Align decimal points by padding zeros
3. Remove decimal points temporarily
4. Perform digit-by-digit addition from right to left
5. Insert decimal point in result
6. Remove leading and trailing zeros

### Subtraction with Decimals

1. Count decimal places in both numbers
2. Align decimal points by padding zeros
3. Remove decimal points temporarily
4. Perform digit-by-digit subtraction with borrow
5. Insert decimal point in result
6. Remove leading and trailing zeros

### Multiplication with Decimals

1. Count decimal places in both operands (d1 + d2 = total)
2. Remove decimal points from both numbers
3. Perform standard multiplication:
* Multiply each digit of second number with entire first number
* Add positional zeros (for tens, hundreds places)
* Accumulate partial products


4. Insert decimal point at position (total decimals)
5. Handle special case: result smaller than decimal places (e.g., 0.01 × 0.01)
6. Remove leading and trailing zeros

### Division with Decimals

1. Scale both numbers to integers (remove decimals by multiplying by 10^n).
2. Perform Long Division:
* Bring down digits one by one.
* Find how many times the divisor fits into the current remainder.
* Append quotient digit.


3. If remainder exists after integer digits, add decimal point.
4. Continue dividing for up to 10 decimal places (precision limit).
5. Clean up leading/trailing zeros.

## Data Structures

### Doubly Linked List Node:

```c
typedef struct node {
    struct node *prev;
    int data;              // Stores single digit (0-9) or '.' for decimal
    struct node *next;
} Dlist;
```

### Comparison Result Enum:
```c
typedef enum {
    NUMBERS_EQUAL = 0,
    FIRST_LARGER = 1,
    SECOND_LARGER = 2
} ComparisonResult;
```

## Input Validation

The program validates:

* Correct number of arguments (minimum 4)
* Valid number format (digits, optional decimal point, optional minus sign)
* Valid operators (+, -, x, /)
* No multiple decimal points
* At least one digit present

Invalid inputs:

* `abc` (non-numeric)
* `12..34` (multiple decimals)
* `-` (minus sign alone)
* `12.34.56` (multiple decimals)

## Memory Management

* All dynamically allocated memory is properly freed
* No memory leaks in normal operation
* Each list is freed after use
* Error handling prevents memory leaks on failure

## Error Handling

The program handles:

* Insufficient command line arguments
* Invalid number format
* Invalid operators
* Memory allocation failures
* Division by zero (returns error)

Error messages are printed to stderr with descriptive information.

## Limitations

1. **Division Precision** - Limited to 10 decimal places for non-terminating fractions
2. **Integer overflow in individual digits** - Each digit is stored as int (0-9)
3. **No scientific notation support** - Only decimal notation
4. **No parentheses** - Single operation at a time
5. **No operator precedence** - Single operation only

## Code Quality Improvements

### From Original Version:

1. ✅ Fixed `free_list()` logic error (missing braces)
2. ✅ Added return value checking for all operations
3. ✅ Extracted main() logic into helper functions
4. ✅ Added comprehensive input validation
5. ✅ Used enums for comparison results
6. ✅ Standardized naming conventions (snake_case)
7. ✅ Removed magic numbers
8. ✅ Added proper error messages
9. ✅ Removed commented-out code
10. ✅ Added decimal support for all operations

### New Features:

1. ✅ Decimal alignment in arithmetic operations
2. ✅ Automatic trailing zero removal (123.4500 → 123.45)
3. ✅ Automatic leading zero removal (00123 → 123)
4. ✅ Comprehensive documentation for all functions
5. ✅ Input validation with descriptive errors
6. ✅ Memory leak prevention
7. ✅ Better code organization

## Testing Examples

### Test Case 1: Large numbers with decimals

```
./calculator 999999999.99 + 0.01
= 1000000000
```

### Test Case 2: Negative subtraction
```
./calculator -100 - -50
= -50
```

### Test Case 3: Small decimal multiplication

```
./calculator 0.001 x 0.001
= 0.000001
```

### Test Case 4: Mixed signs

```
./calculator -50.5 + 100.25
= 49.75
```

## Contributing

When adding new features:

1. Follow existing code style (snake_case, proper documentation)
2. Add function prototypes to `apc.h`
3. Add comprehensive header comments
4. Test with edge cases
5. Update this README

## Future Enhancements

* [ ] Add modulo operation
* [ ] Add power/exponent operation
* [ ] Support for very large exponents (scientific notation)
* [ ] Interactive mode (REPL)
* [ ] Expression parsing (multiple operations)
* [ ] Save/load results to file
* [ ] Unit test framework

## Authors

```
Author       : Shahad K
Website      : https://portfolio-murex-delta-39.vercel.app/
Github       : https://github.com/KruBro
Project Repo : https://github.com/KruBro/Arbitrary_Precision_Calculator_-APC-.git 
```

## Acknowledgments

Built as a demonstration of arbitrary precision arithmetic using linked list data structures.
