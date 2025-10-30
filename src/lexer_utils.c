#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void todo(const char* caller_name){
    // Helper function for functions that arent implemented yet
    // print the caller name and exit
    // always pass __func__ to it
    fprintf(stderr,"Function: '%s' is not implimented yet, Exiting..\n",caller_name);
    exit(74);
}

double myFmod(double x, double y) {
    if (y == 0.0) {
        fprintf(stderr, "Error: Division by zero in myFmod\n");
        exit(1);
    }
    
    int quotient = (int)(x / y);
    return x - quotient * y;  
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

const char *Keywords[] = {
    "int", "float", "double", "char", "void", "short", "long", "signed", "unsigned",

    "if", "else", "switch", "case", "default",
    "while", "do", "for", "break", "continue", "return",

    "const", "static", "typedef",

    "struct", "union", "enum",

    "sizeof", 
};
const int KeywordCount = sizeof(Keywords) / sizeof(Keywords[0]);

// exo3
int isKeyword(const char* word){
    for (int i = 0; i < KeywordCount; i++) {
        if (strcmp(word, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isNumber(const char* s) {
    if (s == NULL || *s == '\0')
        return 0;

    int i = 0;
    int hasDecimal = 0;

    // Optional leading sign
    if (s[i] == '+' || s[i] == '-')
        i++;

    // Must contain at least one digit
    int hasDigit = 0;

    for (; s[i] != '\0'; i++) {
        if (isdigit((unsigned char)s[i])) {
            hasDigit = 1;
            continue;
        }
        if (s[i] == '.') {
            if (hasDecimal)  // second dot ⇒ invalid number
                return 0;
            hasDecimal = 1;
            continue;
        }
        return 0;
    }

    return hasDigit;
}

int isDelimiter(const char* s) {
    static const char DELIMITERS[] = {
        '(', ')', '{', '}', '[', ']', ';', ',', '.', ':'
    };
    int count = sizeof(DELIMITERS) / sizeof(DELIMITERS[0]);

    if (s == NULL || strlen(s) != 1)
        return 0;

    for (int i = 0; i < count; i++) {
        if (s[0] == DELIMITERS[i])
            return 1;
    }
    return 0;
}


int isOperator(const char* s) {
    static const char* OPERATORS[] = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", "<=", ">", ">=",
        "++", "--", "+=", "-=", "*=", "/=", "&&", "||", "!"
    };
    int count = sizeof(OPERATORS) / sizeof(OPERATORS[0]);

    for (int i = 0; i < count; i++) {
        if (strcmp(s, OPERATORS[i]) == 0)
            return 1;
    }
    return 0;
}

int isString(const char* s) {
    if (s == NULL)
        return 0;

    size_t len = strlen(s);

    if (len < 2)
        return 0;

    if (s[0] == '"' && s[len - 1] == '"')
        return 1;

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

int isIdentifier(const char* word) {
    if (word == NULL || *word == '\0')
        return 0;

    if (!isIdentifierStart(word[0]))
        return 0;

    for (int i = 1; word[i] != '\0'; i++) {
        if (!isIdentifierChar(word[i]))
            return 0;
    }

    return 1;
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


const char* getTokenTypeString(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_KEYWORD:    return "KEYWORD";
        case TOKEN_NUMBER:     return "NUMBER";
        case TOKEN_OPERATOR:   return "OPERATOR";
        case TOKEN_STRING:     return "STRING";
        case TOKEN_EOF:        return "EOF";
        case TOKEN_UNKNOWN:    return "UNKNOWN";
        default:               return "UNKNOWN";
    }
}

void printTokenHeader() {
    printf("+--------------+----------------------+-------------+--------+\n");
    printf("| Type         | Lexeme               | Value       | Line   |\n");
    printf("+--------------+----------------------+-------------+--------+\n");
}

void printTokenFooter() {
    printf("+--------------+----------------------+-------------+--------+\n");
}


void printToken(const Token* t) {
    char valueStr[32] = "-";

    if (t->type == TOKEN_NUMBER) {
        if (myFmod(t->numberValue, 1.0) == 0.0) // for test if integer
            sprintf(valueStr, "%d", (int)t->numberValue); 
        else
            sprintf(valueStr, "%.2f", t->numberValue);
    }

    printf("| %-12s | %-20s | %-11s | %-6d |\n",
        getTokenTypeString(t->type),
        t->lexeme ? t->lexeme : "NULL",
        valueStr,
        t->line
    );
}
