#include <stdio.h>
#include <ctype.h>
#include "lexer_utils.c"

// exo6: Skip whitespace and comments, need simple rework
// int skipWhitespaceAndComments(FILE* fp)
char skipWhitespaceAndComments(FILE* fp, int* lineNumber) {
    int c;
    int state = 0;  // for comment state: 0 = no comment, 1 = in /* */ comment

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ' || c == '\t') {
            continue;
        }

        if (c == '\n') {
            (*lineNumber)++;
            continue;
        }

        if (c == '/' && !state) {
            int next = fgetc(fp);
            if (next == '/') {
                while ((c = fgetc(fp)) != EOF && c != '\n') {
                }
                if (c == '\n') {
                    (*lineNumber)++;
                }
                continue;
            } else {
                ungetc(next, fp);
                return '/';
            }
        }

        if (c == '/' && !state) {
            int next = fgetc(fp);
            if (next == '*') {
                state = 1;  
                continue;
            } else {
                ungetc(next, fp);
                return '/';
            }
        }

        if (state == 1) {
            if (c == '\n') {
                (*lineNumber)++;
            } else if (c == '*') {
                int next = fgetc(fp);
                if (next == '/') {
                    state = 0; 
                    continue;
                } else {
                    ungetc(next, fp);
                }
            }
            continue;
        }

        return c;
    }

    return EOF;
}



// simple string recognition functions
int isKeyword(const char* s);
int isNumber(const char* s);
int isOperator(const char* s);
int isDelimiter(const char* s);



//exo11
Token getNextToken(FILE* file) {
    static int line = 1;
    Token token;

    // Skip comments,spaces and update line count
    line += skipWhitespaceAndComments(file);

    // check EOF
    int c = fgetc(file);
    if (c == EOF) {
        token.type = TOKEN_EOF;
        return token;
    }

    // Read lexeme until token boundary
    char buffer[256];
    int i = 0;
    buffer[i++] = c;

    while ((c = fgetc(file)) != EOF) {
        char s[2] = {c, 0};
        if (isspace(c) || isOperator(s) || isDelimiter(s)) {
            ungetc(c, file); // stop at token boundary
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    token.lexeme = strdup(buffer);
    token.line = line;

    // Determine token type using helper functions
    if (isKeyword(token.lexeme)) {
        token.type = TOKEN_KEYWORD;
    } else if (isNumber(token.lexeme)) {
        token.type = TOKEN_NUMBER;
        token.numberValue = atof(token.lexeme);
    } else if (isOperator(token.lexeme)) {
        token.type = TOKEN_OPERATOR;
    } else if (isDelimiter(token.lexeme)) {
        token.type = TOKEN_SYMBOL;
    } else if (isIdentifier(token.lexeme)) {  // fallback
        token.type = TOKEN_IDENTIFIER;
    } else {
        token.type = TOKEN_UNKNOWN;
    }

    return token;
}

//exo12
int main(int argc, char *argv[]) {
    // compile with gcc lexer.c -o lexer
    // run with lexer filename

    // Warning: token type printing isnt implemented yet

    if (argc == 1){ printf("provide filename as a command line argument\n");}

    FILE *file = fopen(argv[1], "r");
    if (file==NULL){
        fprintf(stderr,"Cannot open file: '%s'.\n",argv[1]);
        return 1;
    }

    printf("Warning: Token type printing not implemented yet.\n");
    printf("Line | Lexeme          | Token Type   | Value\n");
    printf("-----------------------------------------------\n");
    for (Token t = getNextToken(file); t.type != TOKEN_EOF; t = getNextToken(file)) {
        if (t.type == TOKEN_NUMBER)
            printf("%4d | %-15s | %-12s | %.2f\n", t.line, t.lexeme, "idk", t.numberValue);
        else
            printf("%4d | %-15s | %-12s | -\n", t.line, t.lexeme, "idk");
    }

    fclose(file);
    return 0;
}

