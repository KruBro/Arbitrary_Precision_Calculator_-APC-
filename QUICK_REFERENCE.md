# QUICK REFERENCE GUIDE

## 🚀 Getting Started (30 seconds)

```
# Build
make

# Test
./calculator 123.45 + 67.89

# Clean
make clean
```

---

## 📝 Command Syntax

```
./calculator <number1> <operator> <number2>
```

### Operators:

* `+` Addition
* `-` Subtraction
* `x` Multiplication
* `/` Division

### Number Format:

* Integers: `123`, `-456`
* Decimals: `123.45`, `-67.89`
* Leading zeros OK: `00123` (becomes `123`)
* Trailing zeros OK: `123.450` (becomes `123.45`)

---

## 💡 Examples

```
# Basic
./calculator 10 + 5              # = 15
./calculator 10 - 5              # = 5
./calculator 10 x 5              # = 50
./calculator 10 / 2              # = 5

# Decimals
./calculator 10.5 + 5.25         # = 15.75
./calculator 10.5 - 5.25         # = 5.25
./calculator 2.5 x 4             # = 10
./calculator 13.5 / 2.5          # = 5.4

# Negatives
./calculator -10 + 5             # = -5
./calculator -10 - 5             # = -15
./calculator -10 x 5             # = -50
./calculator -10 + -5            # = -15

# Mixed
./calculator 100.5 + -50.25      # = 50.25
./calculator -100 - -50          # = -50
./calculator -5.5 x 3            # = -16.5

# Large numbers
./calculator 999999999 + 1       # = 1000000000
./calculator 123456789 x 987654321  # Works!

# Small decimals
./calculator 0.001 + 0.002       # = 0.003
./calculator 0.1 x 0.1           # = 0.01
./calculator 0.01 x 0.01         # = 0.0001
./calculator 1 / 3               # = 0.3333333333
```

---

## 🔍 Common Issues

### Issue: "Invalid first operand"

**Cause:** Non-numeric input
**Fix:** Use only digits, optional decimal, optional minus

```
❌ ./calculator abc + 123
✅ ./calculator 123 + 456
```

### Issue: "Invalid operator"

**Cause:** Wrong operator symbol
**Fix:** Use +, -, x, / only (not *, %)

```
❌ ./calculator 10 * 5
✅ ./calculator 10 x 5
```

### Issue: "Insufficient arguments"

**Cause:** Missing operand or operator
**Fix:** Provide all three: num1 operator num2

```
❌ ./calculator 10 +
✅ ./calculator 10 + 5
```

---

## 🧪 Testing

### Run built-in tests:

```
make test
```

### Check for memory leaks:

```
valgrind --leak-check=full ./calculator 123 + 456
```

### Stress test with large numbers:

```bash
./calculator 99999999999999999999 + 1
```

---

## 📚 Documentation Files

| File | Purpose |
| --- | --- |
| **README.md** | Complete project documentation |
| **CHANGELOG.md** | All changes from v1.0 to v2.0 |
| **TEST_PLAN.md** | 85+ test cases |
| **IMPROVEMENT_SUMMARY.md** | Summary of fixes |
| **QUICK_REFERENCE.md** | This file |

---

## 🛠️ Makefile Targets

```bash
make          # Build the calculator
make clean    # Remove build files
make rebuild  # Clean and rebuild
make test     # Run test cases
make help     # Show available targets

```

---

## 🎯 Key Features

✅ **Arbitrary Precision** - No limit on number size

✅ **Decimal Support** - Automatic alignment

✅ **Negative Numbers** - Full support

✅ **Auto Cleanup** - Removes trailing/leading zeros

✅ **Error Handling** - Descriptive messages

✅ **Memory Safe** - No leaks

---

## 📖 Code Organization

```
Core Operations:
├── addition.c           # Add two numbers
├── subtraction.c        # Subtract two numbers
├── multiplication.c     # Multiply two numbers
└── division.c           # Divide two numbers

Utilities:
├── decimal_utils.c      # Decimal handling
├── validate_number.c    # Input validation
├── compare.c            # Number comparison
└── is_negative.c        # Sign detection

List Operations:
├── insert_at_first.c    # Insert at head
├── insert_at_last.c     # Insert at tail
├── free_list.c          # Memory cleanup
└── remove_dot.c         # Remove decimal point

Main Program:
├── main.c               # Driver program
└── main_helpers.c       # Helper functions

```

---

## 🐛 Debugging Tips

### Enable verbose output:

Add debug prints in your code or use gdb:

```
gdb ./calculator
(gdb) run 123 + 456
(gdb) break addition
(gdb) continue
```

### Check intermediate values:

Add temporary print statements in the operation functions.

### Memory debugging:

```
valgrind --leak-check=full --show-leak-kinds=all ./calculator 123 + 456
```

---

## ⚡ Performance Notes

* **Small numbers** (< 10 digits): Instant
* **Medium numbers** (10-100 digits): < 1ms
* **Large numbers** (100-1000 digits): < 10ms
* **Very large** (1000+ digits): Depends on operation

Multiplication is slowest (O(n²)), addition/subtraction are O(n).

---

## 🎓 Understanding Decimal Handling

### How decimals work:

```
123.45 + 67.8

Step 1: Align
  123.45
+  67.80

Step 2: Remove decimal (store position)
  12345
+  6780

Step 3: Add normally
  19125

Step 4: Insert decimal (2 places from right)
  191.25
```

### Multiplication example:

```
2.5 x 4.2

Step 1: Count decimals (1 + 1 = 2 total)
Step 2: Multiply as integers (25 x 42 = 1050)
Step 3: Insert decimal 2 places from right (10.50)
Step 4: Remove trailing zero (10.5)
```

---

## 🔐 Safety Features

1. **NULL pointer checks** - Before every dereference
2. **Malloc verification** - Every allocation checked
3. **Bounds checking** - No buffer overflows
4. **Input validation** - All inputs verified
5. **Memory cleanup** - All mallocs have corresponding frees

---

## 📊 Comparison: v1.0 vs v2.0

| Feature | v1.0 | v2.0 |
| --- | --- | --- |
| Decimals | ❌ | ✅ |
| Input validation | ❌ | ✅ |
| Memory leaks | ❌ | ✅ |
| Error messages | Minimal | Comprehensive |
| Documentation | Sparse | Complete |
| Test coverage | 0% | 85+ tests |
| Code organization | 200+ line main | Modular |

---

## 💻 Platform Compatibility

**Tested on:**

* Linux (Ubuntu, Debian, etc.)
* macOS
* WSL (Windows Subsystem for Linux)

**Requirements:**

* GCC or Clang compiler
* Make utility
* Standard C library

---

## 🆘 Getting Help

1. **Read README.md** for full documentation
2. **Check TEST_PLAN.md** for expected behavior
3. **Review CHANGELOG.md** for what changed
4. **Look at IMPROVEMENT_SUMMARY.md** for overview

---

## ✅ Quick Checklist

Before using:

* [ ] Run `make` to build
* [ ] Run `make test` to verify
* [ ] Try a simple calculation
* [ ] Check memory with valgrind (optional)

Common first-time issues:

* [ ] Forgot to build with `make`
* [ ] Used `*` instead of `x` for multiplication
* [ ] Forgot quotes around negative numbers (not needed!)
* [ ] Checked that `/` works for division

---

**Remember:** This calculator can handle numbers of ANY size with ANY number of decimal places. The only limit is your computer's memory!

```

```