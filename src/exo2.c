#include <stdio.h>
#include <stdlib.h>
#include "lexer_utils.c"


int main(){
    printf("=== Testing Token Structure ===\n\n");

    // Token 1: Keyword
    Token t1 = {
        .type = TOKEN_KEYWORD,
        .lexeme = "if",
        .numberValue = 0.0,
        .line = 1
    };
    printToken(&t1);

    // Token 2: Identifier
    Token t2 = {
        .type = TOKEN_IDENTIFIER,
        .lexeme = "myVariable",
        .numberValue = 0.0,
        .line = 2
    };
    printToken(&t2);

    // Token 3: Number
    Token t3 = {
        .type = TOKEN_NUMBER,
        .lexeme = "42.5",
        .numberValue = 42.5,
        .line = 3
    };
    printToken(&t3);

    // Token 4: Operator
    Token t4 = {
        .type = TOKEN_OPERATOR,
        .lexeme = "+=",
        .numberValue = 0.0,
        .line = 4
    };
    printToken(&t4);

    // Token 5: String
    Token t5 = {
        .type = TOKEN_STRING,
        .lexeme = "hello",
        .numberValue = 0.0,
        .line = 5
    };
    printToken(&t5);

    return 0;
}
