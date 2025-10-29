"# compiler" 


# Exercise to Filename Mapping
This mapping tells where each exercise live in the code

- Phase 1
  - Exercise 1 → src/exo1.c
  - Exercise 2 
    - Struct Token → src/lexer_utils.c
    - Test program → src/exo2.c

- Phase 2
  - Exercise 3 → src/lexer_utils.c
  - Exercise 4 → src/lexer_utils.c
  - Exercise 5 → src/lexer_utils.c

- Phase 3
  - Exercise 6 → src/lexer.c

- Phase 4
  - Exercise 7 → src/lexer.c
  - Exercise 8 → src/lexer.c
  - Exercise 9 → src/lexer.c
  - Exercise 10 → src/lexer.c

- Phase 5
  - Exercise 11 → src/lexer.c
  - Exercise 12 → src/lexer.c



how to use:
  ```
    gcc lexer.c
  ```
  ---
  ```
    ./a.exe test_input.txt 
  ```

  - output: 
  ```
  --- Lexing file: test_input.txt ---
    Token{ type: KEYWORD, lexeme: 'int', line: 2 }
    Token{ type: IDENTIFIER, lexeme: 'x', line: 2 }
    Token{ type: OPERATOR, lexeme: '= ', line: 2 }
    Token{ type: NUMBER, lexeme: '10', value: 10.00, line: 2 }
    Token{ type: SYMBOL, lexeme: ';', line: 2 }
    Token{ type: KEYWORD, lexeme: 'if', line: 3 }
    Token{ type: SYMBOL, lexeme: '(', line: 3 }
    Token{ type: IDENTIFIER, lexeme: 'x', line: 3 }
    Token{ type: OPERATOR, lexeme: '> ', line: 3 }
    Token{ type: NUMBER, lexeme: '5', value: 5.00, line: 3 }
    Token{ type: SYMBOL, lexeme: ')', line: 3 }
    Token{ type: SYMBOL, lexeme: '{', line: 3 }
    Token{ type: IDENTIFIER, lexeme: 'x', line: 4 }
    Token{ type: OPERATOR, lexeme: '+= ', line: 4 }
    Token{ type: NUMBER, lexeme: '1', value: 1.00, line: 4 }
    Token{ type: SYMBOL, lexeme: ';', line: 4 }
    Token{ type: SYMBOL, lexeme: '}', line: 5 }
    Token{ type: OPERATOR, lexeme: '/* ', line: 6 }
    Token{ type: IDENTIFIER, lexeme: 'test', line: 7 }
    Token{ type: IDENTIFIER, lexeme: 'test', line: 8 }
    Token{ type: IDENTIFIER, lexeme: 'test', line: 9 }
    Token{ type: OPERATOR, lexeme: '*/', line: 10 }
    Token{ type: KEYWORD, lexeme: 'return', line: 12 }
    Token{ type: IDENTIFIER, lexeme: 'x', line: 12 }
    Token{ type: SYMBOL, lexeme: ';', line: 12 }
    Token{ type: EOF, lexeme: 'EOF', line: 12 }
    --- End of file. ---
  ```
