#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "game.c"
#include "algorithms.c"

void processInputData(State *const state, int input[], int sizeOfInput, int line, int column) {
    state->action = NOT_APPLICABLE;
    int i, j;
    // allocating space to matrix
    int **m = malloc(line * sizeof(int *));
    for (int i = 0; i < line; ++i)
        m[i] = malloc(column * sizeof(int));
    // filling with input data
    int currentIndexInput = 0;
    for (i = 0; i < line; i++) {
        for (j = 0; j < column; j++) {
            m[i][j] = input[currentIndexInput];
            currentIndexInput++;
        }
    }
    state->board = m;
}

int main() {
    int input[9] = {1, 2, 3,
                    0, 4, 6,
                    7, 5, 8};
    int sizeOfInput = 9;
    int line = 3;
    int column = 3;
    State initial;
    State goal;

    processInputData(&initial, input, sizeOfInput, line, column);
    defineDefaultGoal(&goal, line, column);
    AStar(&initial, &goal, line, column);

    return 0;
}

