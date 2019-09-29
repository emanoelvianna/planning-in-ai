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