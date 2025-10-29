#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "lexer_utils.c"

// exo6: Skip whitespace and comments
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

// exo7: Recognize identifiers and keywords
Token recognizeIdentifierOrKeyword(FILE* fp, char firstChar, int line){
    size_t capacity = 32;
    size_t length = 0;
    char* lexeme = malloc(capacity);
    if (!lexeme) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    lexeme[length++] = firstChar;

    int c;
    // Continue reading while characters are valid for identifiers
    while ((c = fgetc(fp)) != EOF && isIdentifierChar(c)) {
        // Resize buffer if needed
        if (length + 1 >= capacity) {
            capacity *= 2;
            lexeme = realloc(lexeme, capacity);
            if (!lexeme) {
                fprintf(stderr, "Memory reallocation failed\n");
                exit(1);
            }
        }
        lexeme[length++] = c;
    }

    lexeme[length] = '\0';

    // Return the last non-identifier character to the stream
    if (c != EOF) {
        ungetc(c, fp);
    }

    Token token;
    token.line = line;
    token.lexeme = lexeme;

    if (isKeyword(lexeme)) {
        token.type = TOKEN_KEYWORD;
    } else {
        token.type = TOKEN_IDENTIFIER;
    }

    token.numberValue = 0.0;  // not used for identifiers

    return token;
}

// exo8: Recognize numbers
Token recognizeNumber(FILE* fp, char firstChar, int line){
    size_t capacity = 32;
    size_t length = 0;
    char* buffer = malloc(capacity);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    buffer[length++] = firstChar;

    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (isdigit(c) || c == '.' || c == 'e' || c == 'E' || c == '+' || c == '-') {
            if (length + 1 >= capacity) {
                capacity *= 2;
                buffer = realloc(buffer, capacity);
                if (!buffer) exit(1);
            }
            buffer[length++] = c;
        } else {
            ungetc(c, fp);
            break;
        }
    }
    buffer[length] = '\0';

    char* endptr;
    double value = strtod(buffer, &endptr);

    if (endptr == buffer) {
        free(buffer);
        Token t = { .type = TOKEN_UNKNOWN, .lexeme = NULL, .line = line };
        return t;
    }

    while (endptr < buffer + length) {
        ungetc(*(endptr++), fp);
    }

    size_t valid_len = endptr - buffer;
    buffer[valid_len] = '\0';
    buffer = realloc(buffer, valid_len + 1);  

    Token token = {
        .type = TOKEN_NUMBER,
        .lexeme = buffer,
        .numberValue = value,
        .line = line
    };

    return token;
}

// exo9: Recognize operators and delimiters
Token recognizeOperatorOrDelimiter(FILE* fp, char firstChar, int line){
    if (isOperatorChar(firstChar)) {
        size_t capacity = 8; 
        char* lexeme = malloc(capacity);
        lexeme[0] = firstChar;
        size_t length = 1;

        int c;
        while (isOperatorChar(c = fgetc(fp))) {
            if (length + 1 >= capacity) {
                capacity *= 2;
                lexeme = realloc(lexeme, capacity);
            }
            lexeme[length++] = c;
        }
        if (c != EOF) ungetc(c, fp); 

        lexeme[length] = '\0';
        return (Token){TOKEN_OPERATOR, lexeme, 0.0, line};
    }
    
    char* symbols = "(){}[];,";
    for (int i = 0; symbols[i] != '\0'; i++) {
        if (firstChar == symbols[i]) {
            char* lexeme = strdup(" ");
            lexeme[0] = firstChar;
            return (Token){TOKEN_SYMBOL, lexeme, 0.0, line};
        }
    }

    char* lexeme = strdup(" ");
    lexeme[0] = firstChar;
    return (Token){TOKEN_UNKNOWN, lexeme, 0.0, line};
}

// exo10: Recognize strings and char literals
Token recognizeStringOrChar(FILE* fp, char quote, int line){
    size_t capacity = 64;
    size_t length = 0;
    char* buffer = malloc(capacity);

    int c;
    while ((c = fgetc(fp)) != EOF && c != quote) {
        if (c == '\n') {
            fprintf(stderr, "Lexer Error: Unterminated string on line %d.\n", line);
            free(buffer);
            return (Token){TOKEN_UNKNOWN, NULL, 0.0, line};
        }
        if (c == '\\') {
            c = fgetc(fp); 
            if (c == EOF) break;
        }
        if (length + 1 >= capacity) {
            capacity *= 2;
            buffer = realloc(buffer, capacity);
        }
        buffer[length++] = c;
    }
    if (c == EOF) {
        fprintf(stderr, "Lexer Error: Unterminated string (EOF) on line %d.\n", line);
        free(buffer);
        return (Token){TOKEN_UNKNOWN, NULL, 0.0, line};
    }
    buffer[length] = '\0';
    return (Token){TOKEN_STRING, buffer, 0.0, line};
}

static int currentLine = 1;
//exo11
Token getNextToken(FILE* file){
  int c = skipWhitespaceAndComments(file, &currentLine);
    int tokenLine = currentLine;
    if (c == EOF) {
        return (Token){TOKEN_EOF, strdup("EOF"), 0.0, tokenLine};
    }

    if (isIdentifierStart(c)) {
        return recognizeIdentifierOrKeyword(file, c, tokenLine);
    }

    if (isdigit(c)) {
        return recognizeNumber(file, c, tokenLine);
    }
    if (c == '.') {
        int next = fgetc(file);
        ungetc(next, file); 
        if (isdigit(next)) {
            return recognizeNumber(file, c, tokenLine);
        }
    }
    if (c == '"' || c == '\'') {
        return recognizeStringOrChar(file, c, tokenLine);
    }

    return recognizeOperatorOrDelimiter(file, c, tokenLine);
}

//exo12
int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'\n", argv[1]);
        return 1;
    }

    printf("--- Lexing file: %s ---\n", argv[1]);

    Token token;
    do {
        token = getNextToken(file);
        printToken(&token);

        if (token.lexeme) {
            free(token.lexeme);
        }

    } while (token.type != TOKEN_EOF);

    printf("--- End of file. ---\n");

    fclose(file);
    return 0;
}

