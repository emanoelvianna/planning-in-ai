#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "game.c"
#include "service.c"
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

void usage(char *exec) {
    // TODO: Informar ao usuário como utilizar o programa
}

int main(int argc, char *argv[]) {
    int inputForInitial[9] = {0, 6, 1,
                              7, 4, 2,
                              3, 8, 5};

    int defaultInputGoal[9] = {0, 1, 2,
                               3, 4, 5,
                               6, 7, 8};

    int sizeOfInput = 9;
    int line = 3;
    int column = 3;
    State initial;
    State goal;

    if (argc < 2) {
        usage(argv[0]);
    } else {
        processInputData(&goal, defaultInputGoal, sizeOfInput, line, column);
        // TODO: Obter os dados como parametro!

        int count = 0;
        for (int i = 0; i < argc; i++) {
            if (i > 1) {
                if (!strcmp(argv[i], ",")) {
                    int helper = strtol(argv[i], NULL, 10);
                    inputForInitial[count] = helper;
                    count++;
                } else if (strcmp(argv[i], ",")) {
                    printf("opa\n");
                }
            }
        }

        if (!strcmp(argv[1], "-bfs")) {
            processInputData(&initial, inputForInitial, sizeOfInput, line, column);
            bfsGraph(&initial, &goal, line, column);
        } else if (!strcmp(argv[1], "-idfs")) {
            processInputData(&initial, inputForInitial, sizeOfInput, line, column);
            showBoard(&initial, line, column);
            iterativeDeepening(&initial, &goal, line, column);
        } else if (!strcmp(argv[1], "-astar")) {
            processInputData(&initial, inputForInitial, sizeOfInput, line, column);
            AStar(&initial, &goal, line, column);
        } else if (!strcmp(argv[1], "-idastar")) {
            processInputData(&initial, inputForInitial, sizeOfInput, line, column);
            iterativeDeepeningAStar(&initial, &goal, line, column);
        } else if (!strcmp(argv[1], "-gbfs")) {
            processInputData(&initial, inputForInitial, sizeOfInput, line, column);
            greedySearch(&initial, &goal, line, column);
        }
    }
    return 0;
}

