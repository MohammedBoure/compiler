#include <stdio.h>
#include "lexer_utils.c"


/*
 * Function: count_lines_from_file
 * -------------------------------
 * Counts the number of lines in a text file.
 *
 * file_name: a string representing the path to the file to be read.
 *
 * returns: the number of lines in the file if successful,
 *          or -1 if the file could not be opened.
 */
int count_lines_from_file(const char* file_name){
    FILE* file = fopen(file_name, "r");
    if(file == NULL){
        fprintf(stderr,"Error opening file");
        return -1;
    }

    int number_lines = 0;
    int c;
    while ((c = fgetc(file)) != EOF){
        if(c == '\n') number_lines++;
    }

    fclose(file);
    return number_lines;
}


int main(){
    int n = count_lines_from_file("test.txt");
    printf("%d",n);
}
