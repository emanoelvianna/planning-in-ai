int isGoal(State const *testState, State const *goalState, int line, int column) {
    char row = 3, col;
    while (row--) {
        col = 3;
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

State *moveTile(State *state, Movement move, int line, int column) {
    int i, j;
    int **m = malloc(line * sizeof(int *));
    for (i = 0; i < line; ++i)
        m[i] = malloc(column * sizeof(int));
    State *newState = malloc(sizeof(State));
    newState->board = m;
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
    state[0][0] = 0;
    state[0][1] = 1;
    state[0][2] = 2;
    state[1][0] = 3;
    state[1][1] = 4;
    state[1][2] = 5;
    state[2][0] = 6;
    state[2][1] = 7;
    state[2][2] = 8;

    goal->board = state;
}