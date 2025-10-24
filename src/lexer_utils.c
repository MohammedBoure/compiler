#include <stdio.h>
#include <stdlib.h>


void todo(const char* caller_name){
    // Helper function for functions that arent implemented yet
    // print the caller name and exit
    // always pass __func__ to it
    fprintf(stderr,"Function: '%s' is not implimented yet, Exiting..\n",caller_name);
    exit(74);
}

// a type for unknown or non implemented types
typedef void*  sometype;


//exo2
struct Token {
    sometype lexeme;
    sometype type;
    sometype value;
    sometype line;
};
typedef struct Token Token;


//exo3
int isKeyword(const char word){
    todo(__func__);
}

//exo4
int isIdentifierStart(char c){
    todo(__func__);
}

//exo4
int isIdentifierChar(char c){
    todo(__func__);
}

//exo5
int isOperatorChat(char c){
    todo(__func__);
}


