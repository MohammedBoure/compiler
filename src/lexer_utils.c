#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void todo(const char* caller_name){
    // Helper function for functions that arent implemented yet
    // print the caller name and exit
    // always pass __func__ to it
    fprintf(stderr,"Function: '%s' is not implimented yet, Exiting..\n",caller_name);
    exit(74);
}

/*
-------------------------------------------------------------
 TokenType Enumeration
-------------------------------------------------------------
 Defines the finite set of token categories recognized during
 lexical analysis (the first phase of compilation).

 Each token t ∈ TokenType represents a class of lexical elements:
 - TOKEN_IDENTIFIER : variable or function names
 - TOKEN_KEYWORD    : reserved language keywords
 - TOKEN_NUMBER     : numeric literals (ℝ or ℤ)
 - TOKEN_OPERATOR   : arithmetic/logical operators
 - TOKEN_STRING     : string literals ("...")
 - TOKEN_SYMBOL     : punctuation symbols (;, (), {})
 - TOKEN_EOF        : end-of-file marker
 - TOKEN_UNKNOWN    : undefined or invalid token

 Formally, TokenType = {IDENTIFIER, KEYWORD, NUMBER, OPERATOR,
                        STRING, SYMBOL, EOF, UNKNOWN}
-------------------------------------------------------------
*/
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_STRING,
    TOKEN_SYMBOL,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

//exo2
typedef struct {
    TokenType type;
    char* lexeme;
    double numberValue;
    int line;
} Token;

const char *Keywords[] = {"int", "if", "else", "while", "return"};
const int KeywordCount = 5;

// exo3
int isKeyword(const char* word){
    for (int i = 0; i < KeywordCount; i++) {
        if (strcmp(word, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}

// exo4
int isIdentifierStart(char c){
    return ( (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             (c == '_') );
}

// exo4
int isIdentifierChar(char c){
    return ( (c >= 'A' && c <= 'Z') ||
             (c >= 'a' && c <= 'z') ||
             (c >= '0' && c <= '9') ||
             (c == '_') );
}

// exo5
static const char OPERATOR_CHARS[] = "+-*/=< >!";
int isOperatorChar(char c) {
    for (int i = 0; OPERATOR_CHARS[i] != '\0'; i++) {
        if (c == OPERATOR_CHARS[i]) {
            return 1;
        }
    }
    return 0;
}

