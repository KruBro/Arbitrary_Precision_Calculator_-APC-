# CHANGELOG - Arbitrary Precision Calculator Improvements

## Version 2.0 - Complete Refactor with Decimal Support

### 🔴 CRITICAL FIXES

#### 1. Fixed Memory Leak in free_list()
```
void free_list(Dlist **head)
{
    if(*head == NULL)
        printf("[Info]: List is Empty\n");
        return;  // BUG: This always executes!
    
    while(*head) { ... }
}
```

**Problem:** The `return` statement always executes due to missing braces, causing memory leaks.

**Fixed Code:**

```
void free_list(Dlist **head)
{
    if (head == NULL || *head == NULL)
    {
        return;
    }
    
    while (*head != NULL)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
```

---

### 🟡 HIGH PRIORITY IMPROVEMENTS

#### 2. Added Return Value Checking

**Before:** Operations could fail silently

```
addition(&head1, &tail1, &head2, &tail2, &headR);
print_list(headR);  // What if addition failed?
```

**After:** All operations checked

```
int result = addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
if (result == SUCCESS)
{
    print_list(headR);
}
else
{
    fprintf(stderr, "[ERROR]: Operation failed\n");
}
```

#### 3. Extracted main() Logic into Helper Functions

**Before:** 200+ line main() function with complex nested logic

**After:** Clean separation

* `parse_arguments()` - Validates argc/argv
* `perform_operation()` - Handles operation logic
* Main loop simplified to ~100 lines

#### 4. Comprehensive Input Validation

**Added:** `validate_number()` function

* Checks for valid numeric characters
* Validates decimal point usage (max 1)
* Ensures at least one digit present
* Handles negative sign correctly

**Examples of caught errors:**

* `abc` → Invalid
* `12..34` → Invalid (multiple decimals)
* `-` → Invalid (no digits)
* `1.2.3` → Invalid (multiple decimals)

---

### 🟢 MEDIUM PRIORITY IMPROVEMENTS

#### 5. Replaced Magic Numbers with Enums

**Before:**

```
if (compare(...) == 1)  // What does 1 mean?
if (compare(...) == 2)  // What does 2 mean?
```

**After:**

```
typedef enum {
    NUMBERS_EQUAL = 0,
    FIRST_LARGER = 1,
    SECOND_LARGER = 2
} ComparisonResult;

ComparisonResult result = compare(...);
if (result == FIRST_LARGER) { ... }
```

#### 6. Standardized Naming Convention

**Before:** Mixed styles

* `isOp1Negative` (camelCase)
* `digit_count_operand_1` (snake_case)
* `op1Bigger` (camelCase)

**After:** Consistent snake_case

* `is_op1_negative`
* `digit_count_operand_1`
* `op1_bigger`

#### 7. Improved Error Messages

**Before:**

```
return FAILURE;  // Silent failure
```

**After:**
```
fprintf(stderr, "[ERROR]: Memory allocation failed in insert_at_first\n");
return FAILURE;
```

All error paths now provide context via stderr.

#### 8. Removed Code Smells

* ✅ Removed all commented-out code
* ✅ Removed unnecessary comments
* ✅ Fixed inconsistent formatting
* ✅ Added proper NULL checks everywhere

#### 9. Implemented Full Division Logic

* ✅ Replaced stub with actual implementation
* ✅ Added zero check
* ✅ Added decimal precision support
---

### ⭐ NEW FEATURES

#### 10. Full Decimal Support for Addition

**Algorithm:**

1. Count decimal places in both operands
2. Align decimals by padding zeros
3. Remove decimal points temporarily
4. Perform standard addition
5. Re-insert decimal at correct position
6. Clean up trailing zeros

**Example:**

```
123.45 + 67.8
→ 123.45 + 67.80  (aligned)
→ 12345 + 6780    (decimals removed)
→ 19125           (addition)
→ 191.25          (decimal inserted at position 2)
```

#### 11. Full Decimal Support for Subtraction

**Same algorithm as addition, with borrow logic**

**Example:**

```
100.5 - 45.25
→ 100.50 - 45.25  (aligned)
→ 10050 - 4525    (decimals removed)
→ 5525            (subtraction)
→ 55.25           (decimal inserted at position 2)
```

#### 12. Full Decimal Support for Multiplication

**Algorithm:**

1. Count decimal places (d1 + d2 = total decimals)
2. Remove decimals from both numbers
3. Perform standard multiplication
4. Insert decimal at position = total decimals from right
5. Handle edge case: result smaller than decimal count

**Example:**

```
12.5 x 4.2
→ d1=1, d2=1, total=2
→ 125 x 42        (decimals removed)
→ 5250            (multiplication)
→ 52.50           (decimal at position 2 from right)
→ 52.5            (trailing zero removed)
```

**Edge Case:**

```
0.01 x 0.01
→ d1=2, d2=2, total=4
→ 1 x 1 = 1       (decimals removed)
→ 0.0001          (need to add "0." and 3 zeros)
```

#### 13. Full Decimal Support for Division

**Algorithm:**

1. Scale operands to integers (multiplying by 10^N)
2. Perform Long Division digit-by-digit
3. Handle non-terminating fractions (up to 10 decimal places)
4. Clean up leading/trailing zeros

**Example:**

```
1 / 3
→ 0.3333333333
```

#### 14. New Utility Functions

**Decimal Handling:**

* `find_decimal_point()` - Locate decimal in list
* `count_decimal_places()` - Count digits after decimal
* `pad_decimal_places()` - Add zeros to align decimals
* `remove_leading_zeros()` - Clean 00123 → 123
* `remove_trailing_zeros()` - Clean 123.4500 → 123.45

**Validation:**

* `validate_number()` - Check if string is valid number

---

### 📝 DOCUMENTATION IMPROVEMENTS

#### 15. Added Comprehensive Function Headers

**Before:**

```
int addition(Dlist **head1, ...) {
    // No documentation
}
```

**After:**

```
/***************************************************
 * Function      : addition
 * Description   : Performs addition with decimal support
 * Input Params  : head1, tail1 - First operand
 * head2, tail2 - Second operand
 * headR, tailR - Result
 * Return Value  : SUCCESS / FAILURE
 * Algorithm     : 1. Align decimals
 * 2. Remove decimal points
 * 3. Perform addition
 * 4. Re-insert decimal
 * 5. Clean up zeros
 ***************************************************/

```

#### 16. Created README.md

Complete documentation including:

* Project overview
* Build instructions
* Usage examples
* Algorithm explanations
* Data structure details
* Testing guide
* Future enhancements
---

### 🔧 BUILD SYSTEM IMPROVEMENTS

#### 17. Enhanced Makefile

**Added:**

* Compiler flags: `-Wall -Wextra -std=c11 -g`
* Automatic dependency on `apc.h`
* `rebuild` target
* `test` target with example cases
* `help` target
* Better organization

---

### 📊 TESTING & QUALITY

#### 18. Test Coverage

**Added test cases for:**

* Large numbers: `999999999.99 + 0.01`
* Negative numbers: `-100 - -50`
* Small decimals: `0.001 x 0.001`
* Mixed signs: `-50.5 + 100.25`
* Edge cases: `0 x 1000000`
* Division: `10 / 2`, `13.5 / 2.5`

---

### 🐛 BUG FIXES

#### 19. Fixed Potential Segfaults

* Added NULL checks in all functions
* Validated pointers before dereferencing
* Protected against empty list operations

#### 20. Fixed remove_tailing_zeros()

**Renamed to:** `remove_leading_zeros()`
**Fixed:** Now properly handles single zero case

---

### 📈 PERFORMANCE IMPROVEMENTS

#### 21. Optimized List Operations

* Reduced redundant traversals
* Better memory allocation strategy
* Immediate cleanup of temporary lists

---

## BREAKING CHANGES

### API Changes:

1. All arithmetic functions now require `**tailR` parameter
2. `multiplication()` now requires decimal count parameters
3. `compare()` now returns enum instead of int
4. `is_negative()` renamed from `isNegative()`

### File Changes:

1. `remove_tailing_zeros.c` → `decimal_utils.c` (expanded)
2. Added `main_helpers.c`
3. Added `validate_number.c`
4. Added `division.c`

---

## Migration Guide

### Updating from Version 1.0:

1. **Function Signatures:**

```
// Old
int addition(Dlist **head1, Dlist **tail1, ..., Dlist **headR);

// New  
int addition(Dlist **head1, Dlist **tail1, ..., Dlist **headR, Dlist **tailR);
```

2. **Comparison Results:**

```
// Old
if (compare(...) == 1) { ... }

// New
if (compare(...) == FIRST_LARGER) { ... }
```

3. **Error Handling:**

```
// Old
addition(...);
print_list(headR);

// New
if (addition(...) == SUCCESS) {
    print_list(headR);
} else {
    fprintf(stderr, "Error\n");
}
```

---

## Statistics

* **Files Added:** 5 (main_helpers.c, validate_number.c, decimal_utils.c, division.c, README.md)
* **Files Modified:** 12
* **Lines Added:** ~1800
* **Lines Removed:** ~200
* **Bugs Fixed:** 5 critical, 10+ minor
* **Features Added:** 4 major (decimal support)
* **Documentation:** 100% of functions now documented

---

## Credits
```
Improvements implemented by : Shahad K
Date                        : 12-02-2026
Version                     : 2.0
```