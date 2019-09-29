int isGoal(State const *testState, State const *goalState, int line, int column) {
    while (line--) {
        while (column--) {
            if (testState->board[line][column] != goalState->board[line][column])
                return 0;
        }
    }
    return 1;
}

void showBoard(State *const state, int line, int column) {
    int i, j;
    for (i = 0; i < line; i++) {
        for (j = 0; j < column; j++) {
            printf(" %2d", state->board[i][j]);
        }
        printf("\n");
    }
}

State *moveTile(State *state, Movement move) {
    State *newState = malloc(sizeof(State));
    int i, j;
    int line, column;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (state->board[i][j] == 0) {
                line = i;
                column = j;
            }
            newState->board[i][j] = state->board[i][j];
        }
    }
    if (move == UP && line - 1 >= 0) { // TODO: Nem tudo pode ser fixo!
        int temp = newState->board[line - 1][column];
        newState->board[line - 1][column] = 0;
        newState->board[line][column] = temp;
        newState->action = UP;
        return newState;
    } else if (move == DOWN && line + 1 < 3) {
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
    } else if (move == RIGHT && column + 1 < 3) {
        int temp = newState->board[line][column + 1];
        newState->board[line][column + 1] = 0;
        newState->board[line][column] = temp;
        newState->action = RIGHT;
        return newState;
    }
    free(newState);
    return NULL;
}

void defineDefaultGoal(State *const goal, int line, int column) {
    int **state = malloc(line * sizeof(int *));
    for (int i = 0; i < line; ++i)
        state[i] = malloc(column * sizeof(int));
    state[0][0] = 1;
    state[0][1] = 2;
    state[0][2] = 3;
    state[1][0] = 4;
    state[1][1] = 5;
    state[1][2] = 6;
    state[2][0] = 7;
    state[2][1] = 8;
    state[2][2] = 0;

    goal->board = state;
}