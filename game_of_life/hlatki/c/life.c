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
#include <assert.h>

const int MAX_LINE_LENGTH = 100;

struct life {
    int numRows;
    int numCols;
    char **grid;
};

struct life readGameFile();
void printState(struct life game);

int main() {
    struct life game = readGameFile();
    printState(game);
    //clean up game 
    for (int i = 0; i < game.numRows; i++) {
        free(game.grid[i]);
    }
    free(game.grid);
    return 0;
}

struct life readGameFile() {
    FILE *inFile;
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    struct life game;
    char *token;

    inFile = fopen("lifefile", "r");

    fgets(line,MAX_LINE_LENGTH,inFile); /* Generation */
    /* get # of rows and columns */
    fgets(line,MAX_LINE_LENGTH,inFile);
    token = strtok(line, " ");
    game.numRows = atoi(token);
    token = strtok(NULL, " ");
    game.numCols = atoi(token);

    game.grid = (char**)malloc(game.numRows * sizeof(char*));
    for (int i = 0; i < game.numRows; i++) {
        game.grid[i] = (char*)malloc(game.numCols * sizeof(char));
    }

    while(fgets(line,MAX_LINE_LENGTH,inFile)) {
        for (int i=0; i < strlen(line) - 1; i++) {
            if (line[i] == '*') {
                game.grid[lineCount][i] = 1;
            } else if (line[i] == '.') {
                game.grid[lineCount][i] = 0;
            } else {
                printf("oops, invalid input\n");
            }
        }
        lineCount++;
    }
    
    fclose(inFile);
    return game;
}

void printState(struct life game) {
    for (int i = 0; i < game.numRows; i++) {
        for (int j = 0; j < game.numCols; j++) {
            printf("%d ", game.grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
