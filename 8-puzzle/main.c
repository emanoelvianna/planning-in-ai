#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model.h"
#include "game.c"
#include "service.c"
#include "algorithms.c"

void processInputData(State *const state, int input[], int line, int column) {
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

void usage() {
    printf("use: -<algorithm> <input>\n");
}

int main(int argc, char *argv[]) {
    int defaultInputForInitial[9] = {5, 4, 6,
                                     3, 2, 7,
                                     0, 1, 8};

    int goalWithNine[9] = {0, 1, 2,
                           3, 4, 5,
                           6, 7, 8};

    int goalWithSixteen[16] = {0, 1, 2, 3,
                               4, 5, 6, 7,
                               8, 9, 10, 11,
                               12, 13, 14, 15};

    State initial;
    State goal;

    if (argc < 2) {
        usage();
    } else {
        if (!strcmp(argv[1], "-bfs")) {
            int position = 0;
            int count = 2;
            while (count != argc) {
                int helper = strtol(argv[count], NULL, 10);
                defaultInputForInitial[position] = helper;
                if ((strrchr(argv[count], ',') != NULL) || count + 1 == argc) {
                    processInputData(&initial, defaultInputForInitial, 3, 3);
                    processInputData(&goal, goalWithNine, 3, 3);
                    bfsGraph(&initial, &goal, 3, 3);
                    position = 0;
                } else {
                    position++;
                }
                count++;
            }
        } else if (!strcmp(argv[1], "-idfs")) {
            int position = 0;
            int count = 2;
            while (count != argc) {
                int helper = strtol(argv[count], NULL, 10);
                defaultInputForInitial[position] = helper;
                if ((strrchr(argv[count], ',') != NULL) || count + 1 == argc) {
                    processInputData(&initial, defaultInputForInitial, 3, 3);
                    processInputData(&goal, goalWithNine, 3, 3);
                    iterativeDeepening(&initial, &goal, 3, 3);
                    position = 0;
                } else {
                    position++;
                }
                count++;
            }
        } else if (!strcmp(argv[1], "-astar")) {
            int arrayHelper[15];
            int position = 0;
            int count = 2;
            while (count != argc) {
                int helper = strtol(argv[count], NULL, 10);
                arrayHelper[position] = helper;
                if (position <= 9)
                    defaultInputForInitial[position] = helper;
                if ((strrchr(argv[count], ',') != NULL) || count + 1 == argc) {
                    if (position == 15) {  // specific to size 15
                        processInputData(&initial, arrayHelper, 4, 4);
                        processInputData(&goal, goalWithSixteen, 4, 4);
                        AStar(&initial, &goal, 4, 4, 1);
                    } else {
                        processInputData(&initial, defaultInputForInitial, 3, 3);
                        processInputData(&goal, goalWithNine, 3, 3);
                        AStar(&initial, &goal, 3, 3, 0);
                    }
                    position = 0;
                } else {
                    position++;
                }
                count++;
            }
        } else if (!strcmp(argv[1], "-idastar")) {
            int position = 0;
            int count = 2;
            while (count != argc) {
                int helper = strtol(argv[count], NULL, 10);
                defaultInputForInitial[position] = helper;
                if ((strrchr(argv[count], ',') != NULL) || count + 1 == argc) {
                    processInputData(&initial, defaultInputForInitial, 3, 3);
                    processInputData(&goal, goalWithNine, 3, 3);
                    iterativeDeepeningAStar(&initial, &goal, 3, 3);
                    position = 0;
                } else {
                    position++;
                }
                count++;
            }
        } else if (!strcmp(argv[1], "-gbfs")) {
            int position = 0;
            int count = 2;
            while (count != argc) {
                int helper = strtol(argv[count], NULL, 10);
                defaultInputForInitial[position] = helper;
                if ((strrchr(argv[count], ',') != NULL) || count + 1 == argc) {
                    processInputData(&initial, defaultInputForInitial, 3, 3);
                    processInputData(&goal, goalWithNine, 3, 3);
                    greedySearch(&initial, &goal, 3, 3);
                    position = 0;
                } else {
                    position++;
                }
                count++;
            }
        }
    }
    return 0;
}

