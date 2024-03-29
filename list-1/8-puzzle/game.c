int isGoal(State const *testState, State const *goalState, int line, int column, int isSixteen) {
    char col;
    char row = isSixteen == 0 ? 3 : 4;
    while (row--) {
        col = isSixteen == 0 ? 3 : 4;
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

State *moveTile(State *state, Movement move, int line, int column, int isSixteen) {
    int i, j;
    int helper = isSixteen == 0 ? 3 : 4;
    int **m = malloc(line * sizeof(int *));
    for (i = 0; i < line; ++i)
        m[i] = malloc(column * sizeof(int));
    State *newState = malloc(sizeof(State));
    newState->board = m;
    for (i = 0; i < helper; ++i) {
        for (j = 0; j < helper; ++j) {
            if (state->board[i][j] == 0) {
                line = i;
                column = j;
            }
            newState->board[i][j] = state->board[i][j];
        }
    }



    if (move == UP && line - 1 >= 0) {
        int temp = newState->board[line - 1][column];
        newState->board[line - 1][column] = 0;
        newState->board[line][column] = temp;
        newState->action = UP;
        return newState;
    } else if (move == DOWN && line + 1 < helper) {
        int temp = newState->board[line + 1][column];
        newState->board[line + 1][column] = 0;
        newState->board[line][column] = temp;
        newState->action = DOWN;
        return newState;
    } else if (move == LEFT && column - 1 >= 0) {
        int temp = newState->board[line][column - 1];
        newState->board[line][column - 1] = 0;
        newState->board[line][column] = temp;
        newState->action = LEFT;
        return newState;
    } else if (move == RIGHT && column + 1 < helper) {
        int temp = newState->board[line][column + 1];
        newState->board[line][column + 1] = 0;
        newState->board[line][column] = temp;
        newState->action = RIGHT;
        return newState;
    }

    free(newState);
    return NULL;
}