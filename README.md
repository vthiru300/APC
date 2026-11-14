# APC — Arbitrary Precision Calculator

[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg?style=flat&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Makefile-007acc.svg?style=flat)](makefile)
[![Data Structure: Doubly Linked List](https://img.shields.io/badge/Data%20Structure-Doubly%20Linked%20List-brightgreen.svg)](#data-structures--architecture)

---

## 📌 Abbreviation & Terminology

| Abbreviation | Expanded Form | Description |
|:---|:---|:---|
| **APC** | **Arbitrary Precision Calculator** | A computational system capable of performing arithmetic calculations on numbers whose digits exceed standard native primitive data types (e.g., 32-bit `int`, 64-bit `long long`) with precision bounded only by available system memory. |
| **DLL** | **Doubly Linked List** | Bidirectional linear data structure utilized to represent large integers digit-by-digit, enabling $O(1)$ operations from both ends. |
| **MSB** | **Most Significant Digit / Bit** | The highest-order digit in the number, represented at the `head` of the linked list. |
| **LSB** | **Least Significant Digit / Bit** | The lowest-order digit in the number, represented at the `tail` of the linked list. |
| **OPR** | **Operand** | Input numbers passed via the command line to be computed. |
| **CLI** | **Command Line Interface** | Terminal-based user interaction mechanism. |

---

## 📖 Overview

Standard primitive data types in C have strict capacity limits:
* `int` (32-bit signed): $-2,147,483,648$ to $+2,147,483,647$ (approx. 10 decimal digits)
* `unsigned long long` (64-bit): up to $18,446,744,073,709,551,615$ (approx. 20 decimal digits)

When calculations require hundreds or thousands of digits (e.g., cryptography, scientific computing, mathematical simulations), standard types overflow.

**APC (Arbitrary Precision Calculator)** resolves this limitation by storing numbers dynamically as **Doubly Linked Lists**, where each node contains a single decimal digit. This architecture allows arithmetic operations on numbers of virtually unlimited size.

---

## ✨ Features

- **Arbitrary Size Capacity**: Compute operations on numbers with hundreds or thousands of digits without overflow.
- **Full Signed Arithmetic**: Native support for positive (`+`) and negative (`-`) operands across all operations.
- **Four Core Arithmetic Operations**:
  - ➕ **Addition (`+`)**: LSB-to-MSB traversal with carry propagation.
  - ➖ **Subtraction (`-`)**: Digit borrowing, sign resolution, and magnitude comparison.
  - ✖️ **Multiplication (`x` or `X`)**: Grade-school multiplication with place-value shifting and partial sum accumulation.
  - ➗ **Division (`/`)**: Long division using repeated subtraction with remainder tracking and quotient assembly.
- **Robust Input Validation**: Validates all arguments, rejects illegal non-digit characters, and detects division by zero.
- **Leading Zero Stripping**: Automatically normalizes inputs and intermediate results (e.g., `00045` becomes `45`).

---

## 🏗️ Data Structures & Architecture

### Node Structure

Each digit is encapsulated in a doubly linked list node defined in [`apc.h`](apc.h):

```c
typedef struct node
{
    struct node *prev;   /* Pointer to higher place-value digit (towards MSB) */
    int data;            /* Single digit (0 - 9) */
    struct node *next;   /* Pointer to lower place-value digit (towards LSB)  */
} node;
```

### Visual Representation

An operand like `12345` is stored as:

```text
       (Head / MSB)                                         (Tail / LSB)
          +---+---+---+     +---+---+---+     +---+---+---+     +---+---+---+     +---+---+---+
NULL <--- |   | 1 | --+---> |   | 2 | --+---> |   | 3 | --+---> |   | 4 | --+---> |   | 5 |   | ---> NULL
          |---|---|---|     |---|---|---|     |---|---|---|     |---|---|---|     |---|---|---|
          |   |   |   | <--+-- |   |   | <--+-- |   |   | <--+-- |   |   | <--+-- |   |   |   |
          +---+---+---+     +---+---+---+     +---+---+---+     +---+---+---+     +---+---+---+
```

### Traversal Strategy
* **LSB to MSB (Tail to Head)**: Used for **Addition**, **Subtraction**, and **Multiplication** (aligned with traditional grade-school arithmetic where carries and borrows propagate right-to-left).
* **MSB to LSB (Head to Tail)**: Used for **Division** (bringing down digits one by one) and **Printing/Displaying** output.

---

## 📁 Project Directory Structure

```text
APC/
├── apc.h         # Header file: Struct definitions, macros, and function prototypes
├── main.c        # Entry point: CLI argument validation, sign detection, dispatcher
├── apc.c         # Core utilities: Node insertion, list creation, print, compare, zero stripping
├── add.c         # Addition algorithm implementation
├── sub.c         # Subtraction algorithm implementation
├── mul.c         # Multiplication algorithm implementation
├── div.c         # Division algorithm implementation
├── makefile      # Compilation instructions
└── README.md     # Project documentation
```

---

## ⚙️ Compilation & Build

### Prerequisites
* GCC (GNU Compiler Collection) or Clang
* GNU Make (optional, for `make` command)

### Build with Make
```bash
make
```
This generates the executable `apc.exe` (or `a.out` on Linux).

### Clean Build Artifacts
```bash
make clean
```

### Manual Compilation
```bash
gcc -o apc.exe *.c
```

---

## 🚀 Usage & Syntax

### Command Syntax

```bash
./apc.exe <operand1> <operator> <operand2>
```

> **Note**: In POSIX/Linux shells, if using `*` for multiplication, escape it as `\*` or use `x` / `X`. The program natively accepts `x` and `X` as multiplication operators.

### Arguments

| Parameter | Type | Description |
|:---|:---|:---|
| `<operand1>` | String | First number (arbitrary length, optional leading `+` or `-`). |
| `<operator>` | Character | Operation symbol: `+`, `-`, `x`, `X`, or `/`. |
| `<operand2>` | String | Second number (arbitrary length, optional leading `+` or `-`). |

---

## 💡 Examples & Expected Output

### 1. Addition (`+`)
```bash
$ ./apc.exe 98765432109876543210 + 12345678901234567890
SUCCESS: Argument validated
SUCCESS: Argument validated
98765432109876543210
12345678901234567890
Result : 111111111011111111100
```

### 2. Subtraction (`-`)
```bash
$ ./apc.exe 100000000000000000000 - 1
SUCCESS: Argument validated
SUCCESS: Argument validated
100000000000000000000
1
Result : 99999999999999999999
```

### 3. Multiplication (`x` / `X`)
```bash
$ ./apc.exe 123456789123456789 x 987654321987654321
SUCCESS: Argument validated
SUCCESS: Argument validated
123456789123456789
987654321987654321
Result : 121932631356500531347203169112635269
```

### 4. Division (`/`)
```bash
$ ./apc.exe 100000000000000000000 / 25
SUCCESS: Argument validated
SUCCESS: Argument validated
100000000000000000000
25
Result : 4000000000000000000
```

### 5. Signed Numbers
```bash
$ ./apc.exe -5000000000000000000 + 2000000000000000000
SUCCESS: Argument validated
SUCCESS: Argument validated
5000000000000000000
2000000000000000000
Result : -3000000000000000000
```

---

## 🛡️ Error Handling

* **Invalid Argument Count**: Exits with `ERROR: Argument count must be 4 only` if fewer or more than 3 arguments are provided.
* **Non-numeric Characters**: Exits with `ERROR: Entered argument are not digits` if non-digit characters are supplied in operands.
* **Division by Zero**: Detects zero divisor (`head2 == NULL` or all digits are `0`) and rejects execution with:
  ```text
  ERROR: Division by zero not allowed
  ```
* **Invalid Operator**: Exits with `ERROR: Invalid operator` if an unsupported operation is specified.

---

## 👤 Author

* **Varsha Thirumalai** — [vthiru300](https://github.com/vthiru300)
