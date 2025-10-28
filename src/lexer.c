#include <stdio.h>
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
    todo(__func__);
}

// exo9: Recognize operators and delimiters
Token recognizeOperatorOrDelimiter(FILE* fp, char firstChar, int line){
    todo(__func__);
}

// exo10: Recognize strings and char literals
Token recognizeStringOrChar(FILE* fp, char quote, int line){
    todo(__func__);
}

//exo11
int getNextToken(FILE* file){
  todo(__func__);
}

//exo12
int main(){
  todo(__func__);
}

