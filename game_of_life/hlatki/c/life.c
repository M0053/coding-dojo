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
    int generation;
    char **grid;
};

struct life readGameFile();
void printState(struct life *game);
struct life newLife(int rows, int cols, int generation);
void freeLife(struct life *game);

int main() {
    struct life game = readGameFile();
    printState(&game);
    freeLife(&game);
}

struct life readGameFile() {
    FILE *inFile;
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    struct life game;
    int rows;
    int cols;
    int generation;

    char *token;

    inFile = fopen("lifefile", "r");

    /* Generation */
    fgets(line,MAX_LINE_LENGTH,inFile);     
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    generation = atoi(token);
        
    /* get # of rows and columns */
    fgets(line,MAX_LINE_LENGTH,inFile);
    token = strtok(line, " ");
    rows = atoi(token);
    token = strtok(NULL, " ");
    cols = atoi(token);

    game = newLife(rows, cols, generation);

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

void printState(struct life *gamePtr) {
    printf("Generation %d:\n", gamePtr->generation); 
    for (int i = 0; i < gamePtr->numRows; i++) {
        for (int j = 0; j < gamePtr->numCols; j++) {
            printf("%d ", gamePtr->grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


struct life newLife(int rows, int cols, int generation) {
    struct life game;
    game.generation = generation;
    game.numRows = rows;
    game.numCols = cols;

    game.grid = (char**)malloc(game.numRows * sizeof(char*));
    for (int i = 0; i < game.numRows; i++) {
        game.grid[i] = (char*)malloc(game.numCols * sizeof(char));
    }

    return game;
}


void freeLife(struct life *game) {
    for (int i = 0; i < game->numRows; i++) {
        free(game->grid[i]);
    }
    free(game->grid);
}
