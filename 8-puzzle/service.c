int getTotalCost(Node *const node) {
    return node->depth + node->heuristic;
}

int getManhattanHeuristic(State *const current, State *const goal, int line, int column) {
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
    if ((valid = moveTile(parent->state, DOWN, line, column))) {
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
    return children;
}

void sortByCost(ListNode **const start) {
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