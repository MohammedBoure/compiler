# Lexical Analyzer (Lexer) Project

> **A step-by-step implementation of a lexical analyzer in C**  
> **Course: Compiler Design**  
> **Phase 1 to Phase 5 – Full Exercises as per the provided document**

---

## Overview

This project implements a **Lexical Analyzer (Lexer)** for a C-like language. The lexer reads source code from a file and breaks it into meaningful **tokens** such as keywords, identifiers, numbers, operators, strings, and comments — while skipping whitespace and handling comments.

The implementation is divided into **5 phases**, each building upon the previous one.

---

## Phases Overview

| Phase | Description |
|------|-------------|
| **1** | File Handling and Line Counting |
| **2** | Token Structure and Character Classification |
| **3** | Skipping Whitespace and Comments |
| **4** | Token Recognition Functions |
| **5** | Full Lexer Integration and Output |

---

## Phase 1: File Handling and Line Counting

### Exercise 1
Write a program that opens a source file using `fopen()`, reads it character by character with `fgetc()`, and counts the number of lines. Print the final line count at the end.

---

## Phase 2: Token Structure and Character Classification

### Exercise 2: Define a Token Structure
Define a `struct Token` that contains the fields `lexeme`, `type`, `value`, and `line`. Write a small test program that initializes a token and prints its contents.

### Exercise 3: Keyword Detection
Write a function `int isKeyword(const char *word)` that returns `1` if the word is one of the reserved keywords (`int`, `if`, `else`, `while`, `return`), and `0` otherwise.

---

## Phase 3: Skipping Whitespace and Comments

### Exercise 6: Skipping Whitespace and Comments
Write a function that ignores spaces, tabs, and newlines (while updating line numbers), as well as comments. Single-line comments begin with `//` and multi-line comments are enclosed between `/*` and `*/`. Test this by printing only the meaningful characters that remain.

---

## Phase 4: Token Recognition Functions

### Exercise 4: Identifier Rules
In most programming languages, the rule for identifiers distinguishes between the first character and the following characters:
- The first character must be a letter or underscore.
- The following characters may be letters, digits, or underscores.

For this reason, implement two functions:
```c
int isIdentifierStart(char c);  // letter or _
int isIdentifierChar(char c);   // letter, digit, or _
```

### Exercise 5: Operator Rules
Write a function `int isOperatorChar(char c)` that returns `1` if the character is one of `+`, `-`, `*`, `/`, `=`, `<`, `>`, `!`, and `0` otherwise.

### Exercise 7: Identifiers and Keywords
Write a function that recognizes identifiers. Use `isKeyword()` to decide whether the lexeme should be classified as a **keyword** or as an **identifier**.

### Exercise 8: Numbers
Write a function that recognizes integers. The token must include both the lexeme and its numeric value stored in the `value` field.

### Exercise 9: Operators and Delimiters
Extend recognition to operators (`+`, `-`, `*=`, `==`, `<`, `<=`, `>`, `>=`) and delimiters `(`, `)`, `{`, `}`, `;`, `,`).

### Exercise 10: Strings and Character Literals
Write a function that recognizes string literals (`"..."`) and character literals (`'c'`). Handle escape sequences such as `\"` or `\\`.

---

## Phase 5: Integration

### Exercise 11: Implement `getNextToken()`
Write the main function `Token getNextToken(FILE *fp)` that integrates all previous parts. It should:
- Skip whitespace and comments
- Recognize identifiers/keywords, numbers, operators, delimiters, and literals
- Return a token each time it is called

### Exercise 12: Complete the Lexer
In the `main()` function, repeatedly call `getNextToken(fp)` until the end of the file is reached. Print each token in a table showing:
- **Line**
- **Lexeme**
- **Token Type**
- **Value** (if applicable)

---

## 4. Test Cases

### 4.1. Example 01

#### Input for Lexer:
```c
int main() {
    int x = 10;
    char c = 'A';
    if (x > 0) {
        // print message
        x = x - 1;
        printf("Hello World");
        return c;
    }
}
```

#### Expected Tokens (Lexer Output)

| Line | Lexeme       | Token Type  | Value     |
|------|--------------|-------------|-----------|
| 1    | `int`        | KEYWORD     | -         |
| 1    | `main`       | IDENTIFIER  | -         |
| 1    | `(`          | DELIMITER   | -         |
| 1    | `)`          | DELIMITER   | -         |
| 1    | `{`          | DELIMITER   | -         |
| 2    | `int`        | KEYWORD     | -         |
| 2    | `x`          | IDENTIFIER  | -         |
| 2    | `=`          | OPERATOR    | -         |
| 2    | `10`         | NUMBER      | 10        |
| 2    | `;`          | DELIMITER   | -         |
| 3    | `char`       | KEYWORD     | -         |
| 3    | `c`          | IDENTIFIER  | -         |
| 3    | `=`          | OPERATOR    | -         |
| 3    | `'A'`        | CHAR_LIT    | A         |
| 3    | `;`          | DELIMITER   | -         |
| 4    | `if`         | KEYWORD     | -         |
| 4    | `(`          | DELIMITER   | -         |
| 4    | `x`          | IDENTIFIER  | -         |
| 4    | `>`          | OPERATOR    | -         |
| 4    | `0`          | NUMBER      | 0         |
| 4    | `)`          | DELIMITER   | -         |
| 4    | `{`          | DELIMITER   | -         |
| 6    | `x`          | IDENTIFIER  | -         |
| 6    | `=`          | OPERATOR    | -         |
| 6    | `x`          | IDENTIFIER  | -         |
| 6    | `-`          | OPERATOR    | -         |
| 6    | `1`          | NUMBER      | 1         |
| 6    | `;`          | DELIMITER   | -         |
| 7    | `printf`     | IDENTIFIER  | -         |
| 7    | `(`          | DELIMITER   | -         |
| 7    | `"Hello World"` | STRING_LIT | Hello World |
| 7    | `)`          | DELIMITER   | -         |
| 7    | `;`          | DELIMITER   | -         |
| 8    | `return`     | KEYWORD     | -         |
| 8    | `c`          | IDENTIFIER  | -         |
| 8    | `;`          | DELIMITER   | -         |
| 9    | `}`          | DELIMITER   | -         |
| 10   | `}`          | DELIMITER   | -         |

---
