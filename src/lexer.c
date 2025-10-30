#include <stdio.h>
#include <ctype.h>
#include "lexer_utils.c"

// int skipWhitespaceAndComments(FILE* fp)
int skipWhitespaceAndComments(FILE* fp) {
    int c;
    int lineNumber = 0;
    int state = 0; 

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ' || c == '\t')
            continue;
        if (c == '\n') {
            lineNumber++;
            continue;
        }
        if (c == '/') {
            int next = fgetc(fp);
            if (next == '/') {
                while ((c = fgetc(fp)) != EOF && c != '\n') {}
                if (c == '\n') lineNumber++;
                continue;
            } 
            else if (next == '*') {
                state = 1;
                while (state && (c = fgetc(fp)) != EOF) {
                    if (c == '\n') lineNumber++;
                    else if (c == '*') {
                        int maybeEnd = fgetc(fp);
                        if (maybeEnd == '/')
                            state = 0;
                        else
                            ungetc(maybeEnd, fp);
                    }
                }
                continue;
            } 
            else {
                ungetc(next, fp);
                ungetc(c, fp);
                break;
            }
        }
        ungetc(c, fp);
        break;
    }
    return lineNumber;
}


//exo11
Token getNextToken(FILE* file) {
    static int line = 1;

    // Skip comments,spaces and update line count
    line += skipWhitespaceAndComments(file);

    Token token;
    token.line = line;

    // check EOF
    int c = fgetc(file);
    if (c == EOF) {
        token.type = TOKEN_EOF;
        token.lexeme = strdup("");
        return token;
    }

    // --- Lexeme construction ---
    char buffer[256];
    int i = 0;

    buffer[i++] = c;
    

    // if string literal
    if (c == '"') {
        while ((c = fgetc(file)) != EOF && c != '"') {
            if (c == '\n') {
                fprintf(stderr, "Error: Unterminated string at line %d\n", line);
                break;
            }
            if (i < sizeof(buffer) - 2)
                buffer[i++] = c;
        }
        if (c == '"' && i < sizeof(buffer) - 1)
            buffer[i++] = '"';
    }
    else if (c == '\'') {
        while ((c = fgetc(file)) != EOF && c != '\'') {
            if (c == '\n') {
                fprintf(stderr, "Error: Unterminated char at line %d\n", line);
                break;
            }
            if (i < sizeof(buffer) - 2)
                buffer[i++] = c;
        }
        buffer[i++] = '\''; // close quote
    }
    else if (isalpha(c) || c == '_') {
        // identifier
        while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_')) {
            if (i < sizeof(buffer) - 2)
                buffer[i++] = c;
        }
        if (c != EOF)
            ungetc(c, file);
    }

    buffer[i] = '\0';
    token.lexeme = strdup(buffer);

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
    } else if (isIdentifier(token.lexeme)) {
        token.type = TOKEN_IDENTIFIER;
    } else if (isString(token.lexeme)) {
        token.type = TOKEN_STRING;
    } else if (isChar(token.lexeme)) {
        token.type = TOKEN_CHAR;
    } else {
        token.type = TOKEN_UNKNOWN;
    }

    return token;
}

//exo12
int main(int argc, char *argv[]) {
    if (argc == 1){ 
        printf("provide filename as a command line argument\n");
        return 0; 
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        fprintf(stderr, "Cannot open file: '%s'.\n", argv[1]);
        return 1;
    }

    printf("--- Lexing file: %s ---\n", argv[1]);
    printTokenHeader();
    
    Token t;
    do {
        t = getNextToken(file);
        
        printToken(&t); 

        if (t.lexeme != NULL) {
            free(t.lexeme);
            t.lexeme = NULL;
        }
        
    } while (t.type != TOKEN_EOF);

    printTokenFooter();

    fclose(file);
    return 0;
}


