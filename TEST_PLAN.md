# TEST PLAN - Arbitrary Precision Calculator

## Test Strategy

### Test Categories:
1. **Unit Tests** - Individual function testing
2. **Integration Tests** - Operation flow testing
3. **Edge Case Tests** - Boundary conditions
4. **Error Handling Tests** - Invalid input handling
5. **Memory Tests** - Leak detection and cleanup

---

## 1. UNIT TESTS

### 1.1 List Operations

#### Test: insert_at_first()
```
// Test Case 1: Insert into empty list
head = NULL;
result = insert_at_first(&head, 5);
Expected: SUCCESS, head->data == 5

// Test Case 2: Insert multiple elements
Expected: List = 3 -> 2 -> 1 (reverse order)

// Test Case 3: NULL pointer
result = insert_at_first(NULL, 5);
Expected: FAILURE
```

#### Test: insert_at_last()

```
// Test Case 1: Insert into empty list
head = tail = NULL;
result = insert_at_last(&head, &tail, 5);
Expected: SUCCESS, head == tail, data == 5

// Test Case 2: Insert multiple elements
Expected: List = 1 -> 2 -> 3 (same order)

// Test Case 3: NULL pointers
result = insert_at_last(NULL, &tail, 5);
Expected: FAILURE
```

#### Test: free_list()

```
// Test Case 1: Free non-empty list
create list: 1 -> 2 -> 3
free_list(&head);
Expected: head == NULL, no memory leak

// Test Case 2: Free empty list
head = NULL;
free_list(&head);
Expected: No crash, no error

// Test Case 3: Free after partial operation
Expected: All nodes freed, no leak
```

### 1.2 Validation Functions

#### Test: validate_number()

```
# Valid inputs
✅ "123"
✅ "-456"
✅ "123.456"
✅ "-123.456"
✅ "0"
✅ "0.5"
✅ ".5" (should this be valid? Currently: NO)

# Invalid inputs
❌ "abc"
❌ "12.34.56"
❌ "-"
❌ "."
❌ ""
❌ "12a34"
❌ "12.34.56"
```

#### Test: is_negative()

```
✅ is_negative("-123", 0) == TRUE
✅ is_negative("123", 0) == FALSE
✅ is_negative(NULL, 0) == FALSE
```

#### Test: compare()

```
// Test Case 1: Different lengths
compare(3, 2, "123", "45") == FIRST_LARGER
compare(2, 3, "45", "123") == SECOND_LARGER

// Test Case 2: Same length, different values
compare(3, 3, "123", "456") == SECOND_LARGER
compare(3, 3, "789", "456") == FIRST_LARGER

// Test Case 3: Equal numbers
compare(3, 3, "123", "123") == NUMBERS_EQUAL
```

### 1.3 Decimal Utilities

#### Test: count_decimal_places()

```
count_decimal_places("123.45") == 2
count_decimal_places("123") == 0
count_decimal_places("0.001") == 3
count_decimal_places("123.") == 0
```

#### Test: pad_decimal_places()

```
Input: "123.4", pad 2
Expected: "123.400"

Input: "123", pad 3
Expected: "123000" (or should add decimal?)
```

#### Test: remove_leading_zeros()

```
"00123" → "123"
"00000" → "0"
"0.5" → "0.5" (don't remove the zero)
"000.123" → "0.123"
```

#### Test: remove_trailing_zeros()

```
"123.4500" → "123.45"
"123.000" → "123"
"0.000" → "0"
"100.00" → "100"
```

---

## 2. INTEGRATION TESTS - ADDITION

### 2.1 Basic Addition (No Decimals)

```
# Test 1: Simple positive
./calculator 123 + 456
Expected: = 579

# Test 2: Different lengths
./calculator 999 + 1
Expected: = 1000

# Test 3: Large numbers
./calculator 999999999 + 1
Expected: = 1000000000

# Test 4: Zero cases
./calculator 0 + 0
Expected: = 0

./calculator 123 + 0
Expected: = 123
```

### 2.2 Addition with Decimals

```
# Test 1: Same decimal places
./calculator 123.45 + 67.89
Expected: = 191.34

# Test 2: Different decimal places
./calculator 123.4 + 67.89
Expected: = 191.29

./calculator 123.456 + 67.8
Expected: = 191.256

# Test 3: Integer + Decimal
./calculator 100 + 0.5
Expected: = 100.5

# Test 4: Carry into integer part
./calculator 99.9 + 0.1
Expected: = 100

# Test 5: Very small decimals
./calculator 0.001 + 0.002
Expected: = 0.003
```

### 2.3 Addition with Negatives

```
# Test 1: Both positive (covered above)

# Test 2: Both negative
./calculator -123 + -456
Expected: = -579

./calculator -12.5 + -7.5
Expected: = -20

# Test 3: Positive + Negative (larger positive)
./calculator 100 + -30
Expected: = 70

./calculator 100.5 + -30.25
Expected: = 70.25

# Test 4: Positive + Negative (larger negative)
./calculator 30 + -100
Expected: = -70

./calculator 30.5 + -100.25
Expected: = -69.75

# Test 5: Negative + Positive (same as test 3/4 reversed)
./calculator -30 + 100
Expected: = 70

./calculator -100 + 30
Expected: = -70

# Test 6: Equal magnitude, opposite signs
./calculator 50 + -50
Expected: = 0

./calculator 50.5 + -50.5
Expected: = 0
```

---

## 3. INTEGRATION TESTS - SUBTRACTION

### 3.1 Basic Subtraction (No Decimals)

```
# Test 1: Positive - Positive (larger - smaller)
./calculator 100 - 30
Expected: = 70

# Test 2: Positive - Positive (smaller - larger)
./calculator 30 - 100
Expected: = -70

# Test 3: Equal numbers
./calculator 100 - 100
Expected: = 0

# Test 4: Subtract zero
./calculator 100 - 0
Expected: = 100

# Test 5: Zero minus number
./calculator 0 - 100
Expected: = -100
```

### 3.2 Subtraction with Decimals

```
# Test 1: Same decimal places
./calculator 123.45 - 67.89
Expected: = 55.56

# Test 2: Different decimal places
./calculator 100.5 - 45.25
Expected: = 55.25

# Test 3: Result is decimal
./calculator 100 - 0.5
Expected: = 99.5

# Test 4: Borrow across decimal
./calculator 100.1 - 99.9
Expected: = 0.2
```

### 3.3 Subtraction with Negatives

```
# Test 1: Positive - Negative (becomes addition)
./calculator 100 - -30
Expected: = 130

./calculator 100.5 - -30.5
Expected: = 131

# Test 2: Negative - Positive (becomes addition, stays negative)
./calculator -100 - 30
Expected: = -130

./calculator -100.5 - 30.5
Expected: = -131

# Test 3: Negative - Negative (larger magnitude - smaller)
./calculator -100 - -30
Expected: = -70

./calculator -100.5 - -30.25
Expected: = -70.25

# Test 4: Negative - Negative (smaller magnitude - larger)
./calculator -30 - -100
Expected: = 70

./calculator -30.5 - -100.25
Expected: = 69.75

# Test 5: Equal negative numbers
./calculator -50 - -50
Expected: = 0
```

---

## 4. INTEGRATION TESTS - MULTIPLICATION

### 4.1 Basic Multiplication (No Decimals)

```
# Test 1: Simple positive
./calculator 12 x 13
Expected: = 156

# Test 2: Large numbers
./calculator 999 x 999
Expected: = 998001

# Test 3: Multiply by zero
./calculator 12345 x 0
Expected: = 0

./calculator 0 x 12345
Expected: = 0

# Test 4: Multiply by one
./calculator 12345 x 1
Expected: = 12345
```

### 4.2 Multiplication with Decimals

```
# Test 1: Both have decimals
./calculator 12.5 x 4.2
Expected: = 52.5

# Test 2: One decimal, one integer
./calculator 10 x 0.5
Expected: = 5

./calculator 0.5 x 10
Expected: = 5

# Test 3: Small decimals
./calculator 0.1 x 0.1
Expected: = 0.01

./calculator 0.01 x 0.01
Expected: = 0.0001

# Test 4: Result needs leading zeros
./calculator 0.001 x 0.1
Expected: = 0.0001

# Test 5: Trailing zeros removed
./calculator 2.5 x 4
Expected: = 10 (not 10.0)

./calculator 1.25 x 8
Expected: = 10 (not 10.00)
```

### 4.3 Multiplication with Negatives

```
# Test 1: Positive x Negative
./calculator 12 x -13
Expected: = -156

./calculator 12.5 x -4.2
Expected: = -52.5

# Test 2: Negative x Positive
./calculator -12 x 13
Expected: = -156

./calculator -12.5 x 4.2
Expected: = -52.5

# Test 3: Negative x Negative
./calculator -12 x -13
Expected: = 156

./calculator -12.5 x -4.2
Expected: = 52.5

# Test 4: Zero cases
./calculator -123 x 0
Expected: = 0

./calculator 0 x -123
Expected: = 0
```

---

## 5. INTEGRATION TESTS - DIVISION

### 5.1 Basic Division

```
# Test 1: Exact integer result
./calculator 10 / 2
Expected: = 5

# Test 2: Result with decimals
./calculator 10 / 4
Expected: = 2.5

# Test 3: Large numbers
./calculator 1000000 / 100
Expected: = 10000
```

### 5.2 Division with Decimals

```
# Test 1: Decimal / Integer
./calculator 12.5 / 5
Expected: = 2.5

# Test 2: Integer / Decimal
./calculator 10 / 0.5
Expected: = 20

# Test 3: Decimal / Decimal
./calculator 13.5 / 2.5
Expected: = 5.4
```

### 5.3 Precision and Edge Cases

```
# Test 1: Recurring decimal (limit 10 places)
./calculator 1 / 3
Expected: = 0.3333333333

# Test 2: Smaller than divisor
./calculator 1 / 100
Expected: = 0.01

# Test 3: Negative division
./calculator -10 / 2
Expected: = -5

./calculator 10 / -2
Expected: = -5

./calculator -10 / -2
Expected: = 5
```

---

## 6. EDGE CASE TESTS

### 6.1 Very Large Numbers

```
# Test 1: Many digits
./calculator 12345678901234567890 + 98765432109876543210
Expected: Should work (no overflow)

# Test 2: Multiplication of large numbers
./calculator 999999999 x 999999999
Expected: Should work
```

### 6.2 Very Small Decimals

```
# Test 1: Many decimal places
./calculator 0.123456789 + 0.987654321
Expected: = 1.11111111

# Test 2: Multiplication creates more decimals
./calculator 0.123 x 0.456
Expected: = 0.056088
```

### 6.3 Boundary Cases

```
# Test 1: Single digit
./calculator 1 + 1
Expected: = 2

# Test 2: Just decimal part
./calculator 0.5 + 0.5
Expected: = 1

# Test 3: Equal numbers, different signs
./calculator 123.456 + -123.456
Expected: = 0
```

---

## 7. ERROR HANDLING TESTS

### 7.1 Invalid Input

```
# Test 1: Non-numeric input
./calculator abc + 123
Expected: [ERROR]: Invalid first operand 'abc'

# Test 2: Multiple decimals
./calculator 12.34.56 + 1
Expected: [ERROR]: Invalid first operand '12.34.56'

# Test 3: Invalid operator
./calculator 123 & 456
Expected: [ERROR]: Invalid operator '&'

# Test 4: Missing arguments
./calculator 123 +
Expected: [ERROR]: Insufficient arguments

./calculator 123
Expected: [ERROR]: Insufficient arguments

./calculator
Expected: [ERROR]: Insufficient arguments
```

### 7.2 Division Errors

```
# Test 1: Division by zero
./calculator 100 / 0
Expected: [ERROR]: Division by zero is undefined
```

---

## 8. MEMORY LEAK TESTS

### 8.1 Valgrind Tests

```
# Run with valgrind
valgrind --leak-check=full ./calculator 123.45 + 67.89

Expected output:
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: X allocs, X frees, Y bytes allocated

All heap blocks were freed -- no leaks are possible
```

### 8.2 Repeated Operations

```
# Test retry loop doesn't leak
./calculator 123 + 456
y
y
y
n

Expected: No memory leaks after multiple iterations
```

---

## 9. STRESS TESTS

### 9.1 Performance Tests

```
# Test 1: Very long numbers (1000+ digits)
./calculator [1000 digit number] + [1000 digit number]
Expected: Should complete in reasonable time

# Test 2: Many decimal places (100+)
./calculator 0.[100 decimals] + 0.[100 decimals]
Expected: Should handle correctly
```

---

## 10. REGRESSION TESTS

### 10.1 Previously Fixed Bugs

```
# Test 1: free_list() bug (from changelog)
# Run any operation and check memory
Expected: No memory leaks

# Test 2: Leading zeros
./calculator 00123 + 00456
Expected: = 579 (zeros removed)
```

---

## 11. TEST EXECUTION CHECKLIST

* [ ] All unit tests pass
* [ ] All integration tests pass
* [ ] All edge cases handled
* [ ] All error cases caught
* [ ] No memory leaks (valgrind clean)
* [ ] No segmentation faults
* [ ] Makefile test target works
* [ ] README examples work
* [ ] Stress tests pass
* [ ] Regression tests pass

---

## Test Automation Script

```
#!/bin/bash
# test_all.sh

echo "Running APC Test Suite..."
echo "=========================="

# Test counter
TESTS=0
PASSED=0
FAILED=0

# Function to run test
run_test() {
    local input="$1"
    local expected="$2"
    local description="$3"
    
    TESTS=$((TESTS + 1))
    echo -n "Test $TESTS: $description... "
    
    result=$(echo "n" | $input 2>&1 | grep "^=" | cut -d' ' -f2-)
    
    if [ "$result" == "$expected" ]; then
        echo "✓ PASSED"
        PASSED=$((PASSED + 1))
    else
        echo "✗ FAILED (got: $result, expected: $expected)"
        FAILED=$((FAILED + 1))
    fi
}

# Addition tests
run_test "./calculator 123.45 + 67.89" "191.34" "Decimal addition"
run_test "./calculator 100 + -30" "70" "Positive + negative"
run_test "./calculator -50 + -50" "-100" "Negative + negative"

# Subtraction tests
run_test "./calculator 100.5 - 45.25" "55.25" "Decimal subtraction"
run_test "./calculator 30 - 100" "-70" "Smaller - larger"

# Multiplication tests
run_test "./calculator 12.5 x 4.2" "52.5" "Decimal multiplication"
run_test "./calculator -5 x 3" "-15" "Negative multiplication"

# Division tests
run_test "./calculator 10 / 2" "5" "Basic division"
run_test "./calculator 1 / 4" "0.25" "Decimal division"
run_test "./calculator 13.5 / 2.5" "5.4" "Decimal division with args"

# Summary
echo "=========================="
echo "Tests run: $TESTS"
echo "Passed: $PASSED"
echo "Failed: $FAILED"

if [ $FAILED -eq 0 ]; then
    echo "✓ All tests passed!"
    exit 0
else
    echo "✗ Some tests failed"
    exit 1
fi
```

---

## Manual Testing Procedure

1. **Build the project:**
```
make clean && make
```


2. **Run makefile tests:**
```
make test
```


3. **Run automated test script:**
```
chmod +x test_all.sh
./test_all.sh
```


4. **Memory leak check:**
```
valgrind --leak-check=full --show-leak-kinds=all ./calculator 123.45 + 67.89
```


5. **Manual edge case testing:**
* Test with very large numbers
* Test with many decimal places
* Test invalid inputs


6. **Interactive testing:**
* Use the retry feature
* Test multiple operations in sequence



---

## Expected Results Summary

| Test Category | Total Tests | Expected Pass |
| --- | --- | --- |
| Unit Tests | 15 | 15 |
| Addition | 20 | 20 |
| Subtraction | 15 | 15 |
| Multiplication | 15 | 15 |
| Division | 15 | 15 |
| Edge Cases | 10 | 10 |
| Error Handling | 8 | 8 |
| Memory Tests | 2 | 2 |
| **TOTAL** | **100** | **100** |

---

## Bug Reporting Template

When a test fails, report using:

```
Test      : [Test name]
Input     : [Command used]
Expected  : [Expected output]
Actual    : [Actual output]
Error     : [Error message if any]
Valgrind  : [Memory leak info if applicable]
```

```

```