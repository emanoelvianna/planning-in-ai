int getTotalCost(Node *const node) {
    return node->depth + node->heuristic;
}

int getManhattanHeuristic(State *current, State *goal, int line, int column) {
    int x0, y0;
    int x1, y1;
    int dx, dy;
    int sum = 0;

    for (y0 = 0; y0 < line; ++y0) {
        for (x0 = 0; x0 < column; ++x0) {
            for (y1 = 0; y1 < line; ++y1) {
                for (x1 = 0; x1 < column; ++x1) {
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
        newNode->neighbors = NULL;
    }
    return newNode;
}

void pushNode(ListNode **const listNode, Node *node) {
    ListNode *newNode;
    newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->currentNode = node;
    if ((*listNode) == NULL) {
        newNode->previousNode = NULL;
        newNode->nextNode = NULL;
    } else {
        newNode->nextNode = (*listNode);
        newNode->previousNode = NULL;
        (*listNode)->previousNode = newNode;
    }
    (*listNode) = newNode;
}

int popNode(ListNode **const start) {
    ListNode *ptr;
    if (start == NULL)
        return 0;
    else {
        ptr = (*start);
        (*start) = (*start)->nextNode;
        if ((*start))
            (*start)->previousNode = NULL;
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

int isEqualState(State *a, State *b, int line, int column) {
    while (line--) {
        while (column--) {
            if (a->board[line][column] != b->board[line][column])
                return 0;
        }
    }
    return 1;
}

void removeDuplicatesNode(ListNode *a, ListNode **const b, int line, int column) {
    ListNode *helper1 = a;
    ListNode *helper2 = (*b);
    if (helper1 == NULL)
        return;
    while (helper1->nextNode != NULL) {
        while (helper2->nextNode != NULL) {
            if (isEqualState(helper1->currentNode->state, helper2->currentNode->state, line, column)) {
                ListNode *helper = helper2;
                helper2->previousNode->nextNode = helper2->nextNode;
                helper2->nextNode->previousNode = helper2->previousNode;
                helper2 = helper2->nextNode;
                free(helper);
                printf("Eh nodo repetido!");
            } else {
                helper2 = helper2->nextNode;
            }
        }
        helper1 = helper1->nextNode;
    }
}

ListNode *getNeighbors(Node *parent, State *goal, int line, int column) {
    ListNode *neighbors = NULL;
    State *valid = NULL;
    Node *neighbor = NULL;

    if (parent->state->action != DOWN && (valid = moveTile(parent->state, UP, line, column))) {
        neighbor = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&neighbors, neighbor);
    }
    if (parent->state->action != RIGHT && (valid = moveTile(parent->state, LEFT, line, column))) {
        neighbor = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&neighbors, neighbor);
    }
    if (parent->state->action != LEFT && (valid = moveTile(parent->state, RIGHT, line, column))) {
        neighbor = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&neighbors, neighbor);
    }
    if (parent->state->action != UP && (valid = moveTile(parent->state, DOWN, line, column))) {
        neighbor = createNode(valid, parent, parent->depth + 1, getManhattanHeuristic(valid, goal, line, column));
        pushNode(&neighbors, neighbor);
    }
    return neighbors;
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
    printf("Solution length = %d\n", node->depth);
    // printf("Heuristic = %d\n", node->heuristic);
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