int isGoal(State const *testState, State const *goalState, int line, int column) {
    char row = line, col;
    while (row--) {
        col = column;
        while (col--) {
            if (testState->board[row][col] != goalState->board[row][col])
                return 0;
        }
    }
    return 1;
}

void showBoard(State *state, int line, int column) {
    printf("----------\n");
    int i, j;
    for (i = 0; i < line; i++) {
        for (j = 0; j < column; j++) {
            printf(" %2d", state->board[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
}

State *moveTile(State *state, Movement move, int sizeOfOriginalLine, int sizeOfOriginalColumn) {
    int i, j;
    int helperLine = sizeOfOriginalLine;
    int helperColumn = sizeOfOriginalColumn;
    int **m = malloc(helperLine * sizeof(int *));
    for (i = 0; i < helperLine; ++i)
        m[i] = malloc(helperColumn * sizeof(int));
    State *newState = malloc(sizeof(State));
    newState->board = m;
    for (i = 0; i < helperLine; ++i) {
        for (j = 0; j < helperColumn; ++j) {
            if (state->board[i][j] == 0) {
                helperLine = i;
                helperColumn = j;
            }
            newState->board[i][j] = state->board[i][j];
        }
    }

    if (move == UP && helperLine - 1 >= 0) {
        int temp = newState->board[helperLine - 1][helperColumn];
        newState->board[helperLine - 1][helperColumn] = 0;
        newState->board[helperLine][helperColumn] = temp;
        newState->action = UP;
        return newState;
    } else if (move == DOWN && helperLine + 1 < sizeOfOriginalLine) {
        int temp = newState->board[helperLine + 1][helperColumn];
        newState->board[helperLine + 1][helperColumn] = 0;
        newState->board[helperLine][helperColumn] = temp;
        newState->action = DOWN;
        return newState;
    } else if (move == LEFT && helperColumn - 1 >= 0) {
        int temp = newState->board[helperLine][helperColumn - 1];
        newState->board[helperLine][helperColumn - 1] = 0;
        newState->board[helperLine][helperColumn] = temp;
        newState->action = LEFT;
        return newState;
    } else if (move == RIGHT && helperColumn + 1 < sizeOfOriginalColumn) {
        int temp = newState->board[helperLine][helperColumn + 1];
        newState->board[helperLine][helperColumn + 1] = 0;
        newState->board[helperLine][helperColumn] = temp;
        newState->action = RIGHT;
        return newState;
    }

    free(newState);
    return NULL;
}