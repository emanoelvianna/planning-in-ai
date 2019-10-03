int getTotalCost(Node *const node) {
    return node->depth + node->heuristic;
}

int getManhattanHeuristic(State *const current, State *const goal, int line, int column) {
    int x0, y0; //used for indexing each symbol in `curr`
    int x1, y1; //correspoinding row and column of symbol from curr[y0, x0] at `goal`
    int dx, dy; //change in x0 and x1, and y0 and y1, respectively
    int sum = 0;

    //for each symbol in `curr`
    for (y0 = 0; y0 < 3; ++y0) {
        for (x0 = 0; x0 < 3; ++x0) {
            //find the coordinates of the same symbol in `goal`
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

void pushNode(ListNode **const start, Node *node) {
    ListNode *newNode;
    newNode = (ListNode *) malloc(sizeof(ListNode));
    if ((*start) == NULL) {
        newNode->currentNode = node;
        (*start) = newNode;
    } else {
        newNode->currentNode = node;
        newNode->nextNode = (*start);
        (*start) = newNode;
    }
}

int popNode(ListNode **const start) {
    ListNode *ptr;
    if (start == NULL)
        return 0;
    else {
        ptr = (*start);
        (*start) = (*start)->nextNode;
        free(ptr);
        return 1;
    }
}

void concatenateListOfNodes(ListNode **const a, ListNode *b) {
    if ((*a) == NULL)
        (*a) = b;
    else if ((*a)->nextNode == NULL)
        (*a)->nextNode = b;
    else
        concatenateListOfNodes(&(*a)->nextNode, b);
}

ListNode *getChildren(State *goal, Node *parent, int line, int column) {
    ListNode *children = NULL;
    State *valid = NULL;
    Node *child = NULL;

    if ((valid = moveTile(parent->state, UP, line, column))) {
        child = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if ((valid = moveTile(parent->state, LEFT, line, column))) {
        child = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if ((valid = moveTile(parent->state, RIGHT, line, column))) {
        child = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    if ((valid = moveTile(parent->state, DOWN, line, column))) {
        child = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&children, child);
    }
    return children;
}

void bubble_sort(ListNode **const start) {
    int swapped;
    ListNode *helper1;
    ListNode *helper2 = NULL;
    if ((*start) == NULL)
        return;
    do {
        swapped = 0;
        helper1 = (*start);
        while (helper1->nextNode != helper2) {
            if (getTotalCost(helper1->currentNode) > getTotalCost(helper1->nextNode->currentNode)) {
                Node *helper = helper1->currentNode;
                helper1->currentNode = helper1->nextNode->currentNode;
                helper1->nextNode->currentNode = helper;
                swapped = 1;
            }
            helper1 = helper1->nextNode;
        }
        helper2 = helper1;
    } while (swapped);
}

void quick_sort(int *a, int left, int right) {
    int i, j, x, y;
    i = left;
    j = right;
    x = a[(left + right) / 2];
    while (i <= j) {
        while (a[i] < x && i < right) { i++; }
        while (a[j] > x && j > left) { j--; }
        if (i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if (j > left) {
        quick_sort(a, left, j);
    }
    if (i < right) {
        quick_sort(a, i, right);
    }
}

void printListOfNodes(ListNode **const start, int line, int column) {
    ListNode *ptr;
    if (*start == NULL) {
        return;
    }
    ptr = *start;
    while (ptr != NULL) {
        printf("Depth = %d\n", ptr->currentNode->depth);
        printf("Heuristic = %d\n", ptr->currentNode->heuristic);
        showBoard(ptr->currentNode->state, line, column);
        ptr = ptr->nextNode;
    }
}

void printNodeStatus(Node *node, int line, int column) {
    printf("Depth = %d\n", node->depth);
    printf("Heuristic = %d\n", node->heuristic);
    showBoard(node->state, line, column);
}

void printSolutionPath(Node *node, int line, int column) {
    char *move[4] = {"UP", "DOWN", "LEFT", "RIGHT"};
    Node *path;
    path = node;
    while (path->parent != NULL) {
        printf("Move %s\n", move[path->state->action]);
        path = path->parent;
    }
}