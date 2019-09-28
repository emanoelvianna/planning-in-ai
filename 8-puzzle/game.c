void showBoard(State *const state, int line, int column) {
    int i, j;
    for (i = 0; i < line; i++) {
        for (j = 0; j < column; j++) {
            printf(" %2d", state->board[i][j]);
        }
        printf("\n");
    }
}