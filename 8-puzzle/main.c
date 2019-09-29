#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "game.c"
#include "algorithms.c"

void defineDefaultGoal(State *const state, int line, int column) {
    int **goal = malloc(line * sizeof(int *));
    for (int i = 0; i < line; ++i)
        goal[i] = malloc(column * sizeof(int));
    goal[0][0] = 0;
    goal[0][1] = 1;
    goal[0][2] = 2;
    goal[1][0] = 3;
    goal[1][1] = 4;
    goal[1][2] = 5;
    goal[2][0] = 6;
    goal[2][1] = 7;
    goal[2][2] = 8;

    state->board = goal;
}

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
    int input[9] = {7, 2, 4,
                    5, 0, 6,
                    8, 3, 1};
    int sizeOfInput = 9;
    int line = 3;
    int column = 3;
    State initial;
    State goal;

    processInputData(&initial, input, sizeOfInput, line, column);
    defineDefaultGoal(&goal, line, column);
    showBoard(&initial, line, column);

    AStar(&initial, &goal);

    return 0;
}

