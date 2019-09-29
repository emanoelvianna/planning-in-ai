int manhattanHeuristic(State *const current, State *const goal, int line, int column) {
    int sum = 0;
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            if ((current->board[i][j] != goal->board[i][j]) && (current->board[i][j] != 0)) {
                sum = sum + 1;
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

void pushNode(ListNode **const list, Node *node) {

}

ListNode *getChildren(State *current, State *goal, Node *parent, int line, int column) {
    ListNode *children = NULL;
    State *valid = NULL;
    Node *child = NULL;

    if ((valid = moveTile(current, UP))) {
        child = createNode(valid, parent, parent->depth + 1, manhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if ((valid = moveTile(current, DOWN))) {
        child = createNode(valid, parent, parent->depth + 1, manhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if (valid = moveTile(current, LEFT)) {
        child = createNode(valid, parent, parent->depth + 1, manhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if (valid = moveTile(current, RIGHT)) {
        child = createNode(valid, parent, parent->depth + 1, manhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }

    return children;
}

void AStar(State *const initial, State *const goal, int line, int column) {
    ListNode *closed = NULL;
    ListNode *open = NULL;

    int g = 0;
    int h = manhattanHeuristic(initial, goal, line, column);
    int f = g + h;
    Node *root = createNode(initial, NULL, g, h);
    root->children = getChildren(initial, goal, root, line, column);

    // TODO: Explorar cada instancia ainda aberta e escolher a  menos custosa
}