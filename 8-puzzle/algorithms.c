int manhattanHeuristic(State *const current, State *const goal) {
    int x0, y0; //used for indexing each symbol in `curr`
    int x1, y1; //correspoinding row and column of symbol from curr[y0, x0] at `goal`
    int dx, dy; //change in x0 and x1, and y0 and y1, respectively
    int sum = 0;
    //for each symbol in current
    for (y0 = 0; y0 < 3; ++y0) {
        for (x0 = 0; x0 < 3; ++x0) {
            //find the coordinates of the same symbol in goal
            for (y1 = 0; y1 < 3; ++y1) {
                for (x1 = 0; x1 < 3; ++x1) {
                    if (current->board[y0][x0] == goal->board[y1][x1]) {
                        dx = (x0 - x1 < 0) ? x1 - x0 : x0 - x1;
                        dy = (y0 - y1 < 0) ? y1 - y0 : y0 - y1;
                        sum += dx + dy;
                    }
                }
            }
        }
    }

    return sum;
}

Node *createNode(State *state, Node *parent, unsigned int depth, unsigned int heuristic) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode) {
        newNode->depth = depth;
        newNode->heuristic = heuristic;
        newNode->state = state;
        newNode->parent = parent;
        newNode->children = NULL;
    }
    return newNode;
}

ListNode *getChildren(State *current, Node *node) {
    ListNode *children = NULL;
    State *valid = NULL;

    if ((valid = moveTile(current, UP))) {
        children->currentNode = valid;
    }
    if ((valid = moveTile(current, DOWN))) {
        children->currentNode = valid;
    }
    if (valid = moveTile(current, LEFT)) {
        children->currentNode = valid;
    }
    if (valid = moveTile(current, RIGHT)) {
        children->currentNode = valid;
    }

    return children;
}

void AStar(State *const initial, State *const goal) {
    ListNode *closed = NULL;
    ListNode *open = NULL;

    int g = 0;
    int h = manhattanHeuristic(initial, goal);
    int f = g + h;
    Node *root = createNode(initial, NULL, g, h);
    root->children = getChildren(initial, root);

}