#include <stdio.h>


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
    if (file == NULL){
        fprintf(stderr,"Error opening file: '%s'\n",file_name);
        return -1;
    }

    int number_lines = 0;
    int c;
    while ((c = fgetc(file)) != EOF){
        if (c == '\n') number_lines++;
    }

    fclose(file);
    return number_lines;
}


int main(){
    const char* file_name= "test.txt";
    int n = count_lines_from_file(file_name);

    if (n < 0) return n; // exit on error
    printf("file:'%s' has %d line\n",file_name,n);
    return 0;
}
