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
const int NUM_LIVE_NEIGHBORS_FOR_NEW_LIFE = 3;
const int DEATH_BY_LONLINESS = 2;
const int DEATH_BY_OVERCROWDING = 3;

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
struct life nextGen(struct life *game);
int numberOfLivingNeighbors(struct life *g, int row, int col);

int main() {

    struct life game = readGameFile();
    printState(&game);
    struct life nGen = nextGen(&game);
    printState(&nGen);
    freeLife(&game);
    freeLife(&nGen);
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

struct life nextGen(struct life *game) {
    struct life newGen = newLife(game->numRows, game->numCols, ++game->generation);
   
    /* iterate over current generation */
    for (int i = 0; i < game->numRows; i++) {
        for (int j = 0; j < game->numCols; j++) {
            int alive = game->grid[i][j];
            int nxtGen = game->grid[i][j];
            int numLiveNeighbors = numberOfLivingNeighbors(game, i, j);
            if (alive) {
                if ( (numLiveNeighbors < DEATH_BY_LONLINESS) ||  (numLiveNeighbors > DEATH_BY_OVERCROWDING) )  {
                    nxtGen = 0;
                } else {
                    nxtGen = 1; 
                }
            } else { //cell is dead
                if (numLiveNeighbors ==  NUM_LIVE_NEIGHBORS_FOR_NEW_LIFE) {
                    nxtGen = 1;
                }
            }
            newGen.grid[i][j] = nxtGen;
        }
    }
    return newGen;
}

/* note that our world is *not* a torus */
int numberOfLivingNeighbors(struct life *g, int row, int col) {
    int sum = 0;
    int maxRow = row + 1;
    int minRow = row - 1;
    int maxCol = col + 1;
    int minCol = col - 1;

    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
            /*  check that neighbor isn't out of bounds, or isn't the cell whose neighbors are being tallied */
            if ( ((i >= 0) && (i < g->numRows)) && ((j >= 0) && (j < g->numCols)) && ((i != row) || (j != col)) )
                sum += g->grid[i][j];
        }
    }
    return sum; 
}
