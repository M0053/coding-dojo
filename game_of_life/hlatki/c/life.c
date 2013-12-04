/*
 * Implementation of Conway's Game of Life for the December Coding Dojo
 * (http://codingdojo.org/cgi-bin/wiki.pl?KataGameOfLife)
 * Sample input:

Generation 1:
4 8
........
....*...
...**...
........

 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_LINE_LENGTH = 100;

char **readGameFile(int *rows, int *cols);
void printBoard(char **board);

int main() {
    int numRows;
    int numCols;
    char **board = readGameFile(&numRows, &numCols);

    for (int i=0; i<numRows; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}

char **readGameFile(int *rows, int *cols) {
    FILE *inFile;
    char line[MAX_LINE_LENGTH];
    char **board;
    char *token;

    inFile = fopen("lifefile", "r");

    fgets(line,MAX_LINE_LENGTH,inFile); /* Generation */
    /* get # of rows and columns */
    fgets(line,MAX_LINE_LENGTH,inFile);
    token = strtok(line, " ");
    *rows = atoi(token);
    token = strtok(NULL, " ");
    *cols = atoi(token);

    board = (char**)malloc(*rows * sizeof(char*));
    for (int i=0; i<*rows; i++) {
        board[i] = (char*)malloc(*cols * sizeof(char));
    }

    while(fgets(line,MAX_LINE_LENGTH,inFile)) {
        for (int i=0; i < strlen(line) - 1; i++) {
            if (line[i] == '*') {
                printf("1 ");
            } else if (line[i] == '.') {
                printf("0 ");

            } else {
                printf("oops, invalid input\n");
            }
        }
    }
    
    fclose(inFile);
    return board;
}


